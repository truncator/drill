#include "mesh.hpp"

Mesh::Mesh() :
	m_initialized(false),
	m_vbo(0),
	m_vao(0),
	m_vertices(0, Mesh::Vertex(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0)))
{
}

Mesh::~Mesh()
{
	/*
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(1, &m_vbo);
	*/
}

void Mesh::AddVertex(Vertex vertex)
{
	m_vertices.push_back(vertex);
}

void Mesh::Finalize()
{
	std::vector<GLfloat> vertex_data;

	for (const Mesh::Vertex& vertex : m_vertices)
	{
		glm::vec3 position = vertex.m_position;
		glm::vec3 color = vertex.m_color;

		vertex_data.push_back(position.x);
		vertex_data.push_back(position.y);
		vertex_data.push_back(position.z);
		vertex_data.push_back(color.x);
		vertex_data.push_back(color.y);
		vertex_data.push_back(color.z);
	}

	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Mesh::Vertex), &vertex_data[0], GL_STREAM_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Mesh::Vertex), 0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(Mesh::Vertex), (GLvoid*)(3 * sizeof(GLfloat)));

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::Clear()
{
	m_vertices.clear();
}

void Mesh::Rebuild()
{
	std::vector<GLfloat> vertex_data;

	for (const Mesh::Vertex& vertex : m_vertices)
	{
		glm::vec3 position = vertex.m_position;
		glm::vec3 color = vertex.m_color;

		vertex_data.push_back(position.x);
		vertex_data.push_back(position.y);
		vertex_data.push_back(position.z);
		vertex_data.push_back(color.x);
		vertex_data.push_back(color.y);
		vertex_data.push_back(color.z);
	}

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Mesh::Vertex), 0, GL_STREAM_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, m_vertices.size() * sizeof(Mesh::Vertex), &vertex_data[0]);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::Draw()
{
	glBindVertexArray(m_vao);
	glDrawArrays(GL_TRIANGLES, 0, m_vertices.size());
	glBindVertexArray(0);
}
