#include "map.hpp"

Map::Map(int width, int height) :
	m_chunks(width * height, Chunk(glm::vec3(), 0, 0, 0.0f, std::vector<Tile>(0, Tile()))),
	m_width(width),
	m_height(height)
{
	int chunk_width = 32;
	int chunk_height = 32;
	float tile_size = 1.0f;

	std::vector<Tile> tiles = GenerateMap(width * chunk_width, height * chunk_height);

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			float offset_x = -chunk_width / 2 * (width - 1);
			float offset_y = -(float)chunk_height / 2;

			std::vector<Tile> sub_tiles = std::vector<Tile>(chunk_width * chunk_height, Tile());
			int chunk_x = x * chunk_width;
			int chunk_y = y * chunk_height;

			for (int yy = 0; yy < chunk_height; yy++)
			{
				for (int xx = 0; xx < chunk_width; xx++)
				{
					int xi = chunk_x + xx;
					int yi = chunk_y + chunk_height - yy - 1;

					sub_tiles[yy * chunk_width + xx] = tiles[yi * width * chunk_width + xi];
				}
			}

			glm::vec3 position = glm::vec3(x * tile_size * chunk_width + offset_x, -y * tile_size * chunk_height + offset_y, 0.0f);
			m_chunks[y * width + x] = Chunk(position, chunk_width, chunk_height, tile_size, sub_tiles);
		}
	}
}

std::vector<Tile> Map::GenerateMap(int width, int height)
{
	std::vector<Tile> tiles = std::vector<Tile>(width * height, Tile::Type::None);

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			Tile::Type type = Tile::Type::Limestone;

			if (y < 5 + Random::Int(-1, 1))
				type = Tile::Type::Grass;

			tiles[y * width + x] = Tile(type);
		}
	}

	const int ORE_DEPOSITS = 200;
	const int MIN_HEIGHT = 8;

	for (int i = 0; i < ORE_DEPOSITS; i++)
	{
		Tile::Type type = Tile::Type::None;
		int random_type = Random::Int(0, 2);

		if (random_type == 0)
			type = Tile::Type::Iron;
		else if (random_type == 1)
			type = Tile::Type::Silver;
		else if (random_type == 2)
			type = Tile::Type::Gold;

		const int STEPS = 20;
		glm::vec2 position = glm::vec2(Random::Int(0, width - 1), Random::Int(MIN_HEIGHT, height - 1));
		int last_direction = -1;

		for (int j = 0; j < STEPS; j++)
		{
			tiles[position.y * width + position.x].SetType(type);
			Random::Step(position, glm::vec2(0, 0), glm::vec2(width, height), last_direction);
		}
	}

	const int CAVES = 350;

	for (int i = 0; i < CAVES; i++)
	{
		const int STEPS = 100;
		glm::vec2 position = glm::vec2(Random::Int(0, width - 1), Random::Int(0, height - 1));
		int last_direction = -1;

		for (int j = 0; j < STEPS; j++)
		{
			// Clear the current tile.
			tiles[position.y * width + position.x].SetSolid(false);

			// Step.
			Random::Step(position, glm::vec2(0, 0), glm::vec2(width, height), last_direction);
		}
	}

	return tiles;
}

Chunk& Map::GetChunk(const glm::vec2& position)
{
	for (Chunk& chunk : m_chunks)
	{
		const BoundingBox& bounding_box = chunk.GetBoundingBox();

		if (bounding_box.PointInside(position))
		{
			glm::vec2 tile_coords = position - glm::vec2(bounding_box.m_top_left.x, bounding_box.m_top_left.y);
			return chunk;
		}
	}
}

Tile& Map::GetTile(const glm::vec2& position)
{
	for (Chunk& chunk : m_chunks)
	{
		const BoundingBox& bounding_box = chunk.GetBoundingBox();

		glm::vec2 adjusted_position = position + glm::vec2(bounding_box.m_size.x, bounding_box.m_size.y + 1.0f) / 2.0f;

		if (bounding_box.PointInside(adjusted_position))
		{
			glm::vec2 tile_coords = position - glm::vec2(bounding_box.m_top_left.x, bounding_box.m_top_left.y) + glm::vec2(bounding_box.m_size.x, bounding_box.m_size.y) / 2.0f;
			return chunk.GetTile(tile_coords.x, tile_coords.y);
		}
	}
}

void Map::CalculateVisibleChunks(const glm::vec4& viewport_bounds)
{
	for (Chunk& chunk : m_chunks)
	{
		const BoundingBox& bounding_box = chunk.GetBoundingBox();
		glm::vec3 size = bounding_box.m_size;
		glm::vec3 top_left = bounding_box.m_top_left - size / 2.0f;

		if (top_left.y + size.y < viewport_bounds.z || top_left.y - size.y / 2.0f > viewport_bounds.w ||
				top_left.x > viewport_bounds.y || top_left.x + size.x < viewport_bounds.x)
		{
			chunk.SetVisible(false);
			continue;
		}

		chunk.SetVisible(true);
	}
}

std::vector<Chunk>& Map::GetChunks()
{
	return m_chunks;
}
