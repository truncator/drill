#include "spritebatch.hpp"

#include "mesh.hpp"

SpriteBatch::SpriteBatch(unsigned int size) :
	m_vbo(0),
	m_vao(0),
	m_drawing(false),
	m_batch_size(size),
	m_current_size(0),
	m_vertex_data(m_batch_size * 6 * sizeof(Mesh::Vertex), 0.0f),
	m_batch_count(0)
{
	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, m_batch_size * 6 * sizeof(Mesh::Vertex), 0, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Mesh::Vertex), 0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(Mesh::Vertex), (GLvoid*)(3 * sizeof(GLfloat)));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, false, sizeof(Mesh::Vertex), (GLvoid*)(6 * sizeof(GLfloat)));

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 1, GL_FLOAT, false, sizeof(Mesh::Vertex), (GLvoid*)(8 * sizeof(GLfloat)));

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

SpriteBatch::~SpriteBatch()
{
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(1, &m_vbo);
}

void SpriteBatch::Begin()
{
	assert(!m_drawing);
	m_drawing = true;
}

void SpriteBatch::End()
{
	assert(m_drawing);
	m_drawing = false;

	Flush();

	m_batch_count = 0;
}

void SpriteBatch::DrawQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec3& color, const glm::vec4& uv)
{
	assert(m_drawing);

	// Get the current index into the queued vertex data vector.
	int index = m_current_size * 6 * 9;

	// Construct a model matrix for the quad.
	glm::mat4 model_matrix = glm::translate(glm::mat4(), glm::vec3(position.x + size.x / 2, position.y + size.y / 2, 0.0f));
	model_matrix = glm::rotate(model_matrix, rotation, glm::vec3(0.0f, 0.0f, 1.0f));
	model_matrix = glm::translate(model_matrix, glm::vec3(-size.x / 2, -size.y / 2, 0.0f));
	model_matrix = glm::scale(model_matrix, glm::vec3(size.x, size.y, 0.0f));

	// Transform the quad.
	glm::vec3 bottom_left  = glm::vec3(model_matrix * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	glm::vec3 bottom_right = glm::vec3(model_matrix * glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	glm::vec3 top_right    = glm::vec3(model_matrix * glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
	glm::vec3 top_left     = glm::vec3(model_matrix * glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));

	// Fill the vertex data queue.

	// 0
	m_vertex_data[index + 0] = bottom_left.x;
	m_vertex_data[index + 1] = bottom_left.y;
	m_vertex_data[index + 2] = 0.0f;

	m_vertex_data[index + 3] = color.x;
	m_vertex_data[index + 4] = color.y;
	m_vertex_data[index + 5] = color.z;

	m_vertex_data[index + 6] = uv.x;
	m_vertex_data[index + 7] = uv.y;

	m_vertex_data[index + 8] = 0.0f;

	// 1
	m_vertex_data[index + 9] = bottom_right.x;
	m_vertex_data[index + 10] = bottom_right.y;
	m_vertex_data[index + 11] = 0.0f;

	m_vertex_data[index + 12] = color.x;
	m_vertex_data[index + 13] = color.y;
	m_vertex_data[index + 14] = color.z;

	m_vertex_data[index + 15] = uv.x + uv.z;
	m_vertex_data[index + 16] = uv.y;

	m_vertex_data[index + 17] = 0.0f;

	// 2
	m_vertex_data[index + 18] = top_right.x;
	m_vertex_data[index + 19] = top_right.y;
	m_vertex_data[index + 20] = 0.0f;

	m_vertex_data[index + 21] = color.x;
	m_vertex_data[index + 22] = color.y;
	m_vertex_data[index + 23] = color.z;

	m_vertex_data[index + 24] = uv.x + uv.z;
	m_vertex_data[index + 25] = uv.y + uv.w;

	m_vertex_data[index + 26] = 0.0f;

	// 0
	m_vertex_data[index + 27] = bottom_left.x;
	m_vertex_data[index + 28] = bottom_left.y;
	m_vertex_data[index + 29] = 0.0f;

	m_vertex_data[index + 30] = color.x;
	m_vertex_data[index + 31] = color.y;
	m_vertex_data[index + 32] = color.z;

	m_vertex_data[index + 33] = uv.x;
	m_vertex_data[index + 34] = uv.y;

	m_vertex_data[index + 35] = 0.0f;

	// 2
	m_vertex_data[index + 36] = top_right.x;
	m_vertex_data[index + 37] = top_right.y;
	m_vertex_data[index + 38] = 0.0f;

	m_vertex_data[index + 39] = color.x;
	m_vertex_data[index + 40] = color.y;
	m_vertex_data[index + 41] = color.z;

	m_vertex_data[index + 42] = uv.x + uv.z;
	m_vertex_data[index + 43] = uv.y + uv.w;

	m_vertex_data[index + 44] = 0.0f;

	// 3
	m_vertex_data[index + 45] = top_left.x;
	m_vertex_data[index + 46] = top_left.y;
	m_vertex_data[index + 47] = 0.0f;

	m_vertex_data[index + 48] = color.x;
	m_vertex_data[index + 49] = color.y;
	m_vertex_data[index + 50] = color.z;

	m_vertex_data[index + 51] = uv.x;
	m_vertex_data[index + 52] = uv.y + uv.w;

	m_vertex_data[index + 53] = 0.0f;

	// Move to the next index.
	m_current_size++;

	// Check if the batch is full.
	if (m_current_size >= m_batch_size)
		Flush();
}

void SpriteBatch::Flush()
{
	if (m_current_size == 0)
		return;

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

	// Buffer the queued vertex data.
	glBufferData(GL_ARRAY_BUFFER, m_batch_size * 6 * sizeof(Mesh::Vertex), 0, GL_DYNAMIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, m_current_size * 6 * sizeof(Mesh::Vertex), &m_vertex_data[0]);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Submit a draw call.
	glBindVertexArray(m_vao);
	glDrawArrays(GL_TRIANGLES, 0, m_current_size * 6);
	glBindVertexArray(0);

	// Reset batch state.
	m_current_size = 0;
	m_batch_count++;
}
