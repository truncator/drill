#pragma once

#include "precompiled.hpp"

//
// Mesh
//

class Mesh
{
public:

	//
	// Vertex
	//

	struct Vertex
	{
		glm::vec3 m_position;
		glm::vec3 m_color;
		glm::vec2 m_uv;
		float m_metallic;

		Vertex(glm::vec3 position, glm::vec3 color, glm::vec2 uv, float metallic) :
			m_position(position), m_color(color), m_uv(uv), m_metallic(metallic)
		{
		}
	};

public:
	Mesh();
	~Mesh();

	void AddVertex(Vertex vertex);
	void Finalize();
	void Clear();

	void Rebuild();

	void Draw();

private:
	bool m_initialized;

	GLuint m_vbo;
	GLuint m_vao;

	std::vector<Vertex> m_vertices;
};
