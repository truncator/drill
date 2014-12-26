#pragma once

#include "precompiled.hpp"
#include "tile.hpp"
#include "../graphics/mesh.hpp"

class Chunk
{
public:
	Chunk(glm::vec3 position, int width, int height, float tile_size, const std::vector<Tile>& tiles);

	void RebuildMesh();

	bool IsDirty();

	void SetVisible(bool visible);
	bool IsVisible() const;

	// Get accessors.
	Mesh& GetMesh();
	const BoundingBox& GetBoundingBox() const;
	Tile& GetTile(int x, int y);

private:
	std::vector<Tile> m_tiles;
	int m_width;
	int m_height;
	float m_tile_size;

	Mesh m_mesh;
	BoundingBox m_bounding_box;
	bool m_visible;
};
