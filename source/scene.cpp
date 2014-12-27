#include "scene.hpp"

#include "graphics/shader.hpp"
#include "graphics/spritebatch.hpp"
#include "graphics/text.hpp"

Scene::Scene() :
	m_camera(glm::vec3(0.0f, 10.0f, -150.0f)),
	m_map(5, 20),
	m_drill(glm::vec2(0.0f, -1.0f)),
	m_lights(128, Light())
{
	m_drill.Activate();

	Light rig_light = Light(glm::vec2(m_drill.GetRigPosition().x, m_drill.GetRigPosition().y), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 10.0f);
	Light bit_light = Light(glm::vec2(m_drill.GetBitPosition().x, m_drill.GetBitPosition().y), glm::vec3(1.0f, 0.8f, 0.8f), 1.0f, 30.0f);
	bit_light.SetStatic(false);

	m_lights[0] = rig_light;
	m_drill.AttachLight(&m_lights[0], glm::vec2(1.0f, 0.0f));

	m_lights[1] = bit_light;
	m_drill.AttachLight(&m_lights[1], glm::vec2(m_drill.GetBitWidth() / 2.0f));

	m_drill.InitializeLights(m_drill.GetBitPosition());

	/*
	int light_index = 2;

	std::vector<Chunk>& chunks = m_map.GetChunks();
	for (Chunk& chunk : chunks)
	{
		for (int y = 0; y < 32; y++)
		{
			for (int x = 0; x < 32; x++)
			{
				if (chunk.GetTile(x, y).GetType() == Tile::Type::Gold)
				{
					if (light_index >= 100)
						continue;

					glm::vec2 chunk_origin = glm::vec2(chunk.GetBoundingBox().m_top_left.x, chunk.GetBoundingBox().m_top_left.y);
					//m_lights[light_index] = Light(chunk_origin + glm::vec2(x, 32 - y), glm::vec3(1.0f, 1.0f, 1.0f), 0.1f, 1.0f);
					light_index++;
				}
			}
		}
	}
	*/
}

Camera& Scene::GetCamera()
{
	return m_camera;
}

void Scene::Update(double dt)
{
	glm::vec2 bit_position = m_drill.GetBitPosition();
	m_camera.MoveTo(glm::vec3(bit_position.x, bit_position.y, m_camera.GetPosition().z));

	// Update the drill with its current tile.
	Tile& tile = m_map.GetTile(bit_position);
	m_drill.Update(tile, dt);

	if (tile.IsDirty())
	{
		Item::Type type = Item::GetTypeFromTile(tile.GetType());
		m_inventory.AddItem(type, 1);
	}

	// Update the camera's position.
	m_camera.Update(dt);

	// Rebuild dirty chunk meshes.
	std::vector<Chunk>& chunks = m_map.GetChunks();
	for (Chunk& chunk : chunks)
	{
		if (chunk.IsDirty())
			chunk.RebuildMesh();
	}

	m_drill.UpdateLights(m_drill.GetBitPosition());

	Shader::Bind("base");
	PassLightUniforms();

	int item_count = (int)Item::Type::ItemCount;
	for (int i = 0; i < item_count; i++)
	{
		Inventory::ItemIterator item = m_inventory.GetItem((Item::Type)i);
		Item::Type type = item->first;
		int count = item->second;
		//printf("%s: %i\n", Item::GetName(type).c_str(), count);
	}
}

void Scene::Draw(SpriteBatch& sprite_batch, const glm::vec4& viewport_bounds)
{
	//
	// Map
	//

	Shader::SetUniformVec2("light_position", m_drill.GetBitPosition() + glm::vec2(m_drill.GetBitWidth() / 2.0f));
	Shader::SetUniformMatrix("model", glm::mat4());

	m_map.CalculateVisibleChunks(viewport_bounds);
	std::vector<Chunk>& chunks = m_map.GetChunks();

	sprite_batch.Begin();
	Shader::Bind("sky");
	glm::vec2 position = glm::vec2(viewport_bounds.x, viewport_bounds.w);
	glm::vec2 size = glm::vec2(viewport_bounds.y - viewport_bounds.x, viewport_bounds.w - viewport_bounds.z) * 2.0f;
	sprite_batch.DrawQuad(position - size / 2.0f, size, 0.0f, glm::vec3(1.0f, 1.0f, 1.0f), glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
	sprite_batch.End();

	Shader::Bind("base");

	for (Chunk& chunk : chunks)
	{
		if (!chunk.IsVisible())
			continue;

		const BoundingBox& bounding_box = chunk.GetBoundingBox();
		glm::vec3 position = bounding_box.m_top_left - bounding_box.m_size / 2.0f;

		glm::mat4 model_matrix = glm::translate(glm::mat4(), position);
		Shader::SetUniformMatrix("model", model_matrix);

		chunk.GetMesh().Draw();
	}

	Shader::SetUniformMatrix("model", glm::mat4());

	//
	// Drill
	//

	sprite_batch.Begin();
	Shader::SetUniformMatrix("model", glm::mat4());

	glm::vec2 rig_position = m_drill.GetRigPosition();
	glm::vec2 bit_position = m_drill.GetBitPosition();
	int bit_length = glm::abs(bit_position.y - rig_position.y);
	int bit_width = m_drill.GetBitWidth();

	sprite_batch.DrawQuad(rig_position, m_drill.GetRigSize(), 0.0f, glm::vec3(0.8f, 0.8f, 0.8f), glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
	sprite_batch.DrawQuad(rig_position + glm::vec2(1.0f, 1.0f), glm::vec2(1.0f, 1.0f), 0.0f, glm::vec3(0.8f, 0.8f, 0.8f), glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));

	// Draw the full length of the drill bit.
	for (int i = 0; i < bit_length; i++)
	{
		glm::vec2 top_left = glm::vec2(bit_position.x, rig_position.y - i);
		float scaled_width = bit_width * 0.2f;
		float outline_width = 0.1f;
		float tile_size = 1.0f;

		glm::vec2 bit = top_left + glm::vec2(tile_size / 2, 0.0f) - glm::vec2(scaled_width / 2, 0.0f);
		glm::vec2 outline = bit - glm::vec2(outline_width, 0.0f);

		// Outline.
		sprite_batch.DrawQuad(outline, glm::vec2(scaled_width + outline_width * 2, 1), 0.0f, glm::vec3(0.3f, 0.3f, 0.3f), glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));

		// Bit.
		sprite_batch.DrawQuad(bit, glm::vec2(scaled_width, 1.0f), 0.0f, glm::vec3(0.8f, 0.8f, 0.8f), glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
	}

	// Drill bit.
	sprite_batch.DrawQuad(bit_position, glm::vec2(bit_width, 1.0f), 0.0f, glm::vec3(0.8f, 0.3f, 0.3f), glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));

	sprite_batch.End();
}

void Scene::PassLightUniforms()
{
	int size = m_lights.size();
	int active_lights = 0;

	for (int i = 0; i < size; i++)
	{
		if (!m_lights[i].IsActive())
			continue;

		std::string base = std::string("lights[") + std::to_string(i) + "].";

		Shader::SetUniformVec2(base + "position", m_lights[i].GetPosition());
		Shader::SetUniformVec3(base + "color", m_lights[i].GetColor());
		Shader::SetUniformFloat(base + "intensity", m_lights[i].GetIntensity());
		Shader::SetUniformFloat(base + "falloff", m_lights[i].GetFalloff());

		active_lights++;
	}

	Shader::SetUniformInt("active_lights", active_lights);
}
