#pragma once

#include "precompiled.hpp"
#include "chunk.hpp"
#include "tile.hpp"

//
// Map
//     Manages map generation and state.
//

class Map
{
public:
	Map(int width, int height);

	std::vector<Tile> GenerateMap(int width, int height);

	Chunk& GetChunk(const glm::vec2& position);
	Tile& GetTile(const glm::vec2& position);

	void CalculateVisibleChunks(const glm::vec4& viewport_bounds);
	std::vector<Chunk>& GetChunks();

private:
	std::vector<Chunk> m_chunks;
	int m_width;
	int m_height;
};
