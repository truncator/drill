#include "scene.hpp"

#include "graphics/shader.hpp"
#include "graphics/spritebatch.hpp"

Scene::Scene() :
	m_camera(glm::vec3(0.0f, 10.0f, -100.0f)),
	m_map(3, 20),
	m_drill(glm::vec2(0.0f, -1.0f))
{
	m_drill.Activate();
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

	int item_count = (int)Item::Type::ItemCount;
	for (int i = 0; i < item_count; i++)
	{
		Inventory::ItemIterator item = m_inventory.GetItem((Item::Type)i);
		Item::Type type = item->first;
		int count = item->second;
		printf("%s: %i\n", Item::GetName(type).c_str(), count);
	}
}

void Scene::Draw(SpriteBatch& sprite_batch)
{
	//
	// Map
	//

	m_map.CalculateVisibleChunks(m_camera.GetPosition());

	std::vector<Chunk>& chunks = m_map.GetChunks();

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

	sprite_batch.DrawQuad(rig_position, m_drill.GetRigSize(), 0.0f, glm::vec3(0.8f, 0.8f, 0.8f));
	sprite_batch.DrawQuad(rig_position + glm::vec2(1.0f, 1.0f), glm::vec2(1.0f, 1.0f), 0.0f, glm::vec3(0.8f, 0.8f, 0.8f));

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
		sprite_batch.DrawQuad(outline, glm::vec2(scaled_width + outline_width * 2, 1), 0.0f, glm::vec3(0.3f, 0.3f, 0.3f));

		// Bit.
		sprite_batch.DrawQuad(bit, glm::vec2(scaled_width, 1.0f), 0.0f, glm::vec3(0.8f, 0.8f, 0.8f));
	}

	// Drill bit.
	sprite_batch.DrawQuad(bit_position, glm::vec2(bit_width, 1.0f), 0.0f, glm::vec3(0.8f, 0.3f, 0.3f));

	sprite_batch.End();
}
