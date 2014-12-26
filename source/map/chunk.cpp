#include "chunk.hpp"

Chunk::Chunk(glm::vec3 position, int width, int height, float tile_size, const std::vector<Tile>& tiles) :
	m_tiles(width * height, Tile()),
	m_width(width),
	m_height(height),
	m_tile_size(tile_size),
	m_bounding_box(position, glm::vec3(width, height, 0)),
	m_visible(false)
{
	m_mesh.Finalize();

	for (int i = 0; i < tiles.size(); i++)
	{
		m_tiles[i] = tiles[i];
	}

	RebuildMesh();
}

void Chunk::RebuildMesh()
{
	m_mesh.Clear();

	for (int y = 0; y < m_height; y++)
	{
		for (int x = 0; x < m_width; x++)
		{
			glm::vec3 position = glm::vec3(x * m_tile_size, y * m_tile_size, 0);
			glm::vec3 color = m_tiles[y * m_width + x].GetColor();
			float metallic = m_tiles[y * m_width + x].GetMetallic();

			Mesh::Vertex top_left     = Mesh::Vertex(position + glm::vec3(0.0f,  0.0f, 0.0f) * m_tile_size, color, metallic);
			Mesh::Vertex bottom_left  = Mesh::Vertex(position + glm::vec3(0.0f, -1.0f, 0.0f) * m_tile_size, color, metallic);
			Mesh::Vertex bottom_right = Mesh::Vertex(position + glm::vec3(1.0f, -1.0f, 0.0f) * m_tile_size, color, metallic);
			Mesh::Vertex top_right    = Mesh::Vertex(position + glm::vec3(1.0f,  0.0f, 0.0f) * m_tile_size, color, metallic);

			m_mesh.AddVertex(bottom_left);
			m_mesh.AddVertex(bottom_right);
			m_mesh.AddVertex(top_right);

			m_mesh.AddVertex(bottom_left);
			m_mesh.AddVertex(top_right);
			m_mesh.AddVertex(top_left);
		}
	}

	m_mesh.Rebuild();
}

bool Chunk::IsDirty()
{
	bool dirty = false;

	for (int y = 0; y < m_height; y++)
	{
		for (int x = 0; x < m_width; x++)
		{
			if (m_tiles[y * m_width + x].IsDirty())
			{
				m_tiles[y * m_width + x].CleanDirty();
				dirty = true;
			}
		}
	}

	return dirty;
}

void Chunk::SetVisible(bool visible)
{
	m_visible = visible;
}

bool Chunk::IsVisible() const
{
	return m_visible;
}

Mesh& Chunk::GetMesh()
{
	return m_mesh;
}

const BoundingBox& Chunk::GetBoundingBox() const
{
	return m_bounding_box;
}

Tile& Chunk::GetTile(int x, int y)
{
	assert(x >= 0 && x < m_width);
	assert(y >= 0 && y < m_height);

	return m_tiles[y * m_width + x];
}
