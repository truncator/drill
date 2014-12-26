#include "renderer.hpp"

#include "precompiled.hpp"
#include "camera.hpp"
#include "shader.hpp"

Renderer::Renderer(Camera* camera) :
	m_sprite_batch(1000),
	m_camera(camera)
{
	assert(m_camera != nullptr);

	glClearColor(0.3f, 0.5f, 0.6f, 1.0f);
}

void Renderer::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Prepare()
{
	Clear();

	glm::vec4 viewport = CalculateViewportBounds();
	glm::mat4 view_projection = glm::ortho<float>(viewport.x, viewport.y, viewport.z, viewport.w, 0.0f, 1.0f); 

	Shader::Bind("sky");
	Shader::SetUniformMatrix("view_projection", view_projection);

	Shader::Bind("base");
	Shader::SetUniformMatrix("view_projection", view_projection);
}

void Renderer::Cleanup()
{
	Shader::Unbind("sky");
	Shader::Unbind("base");
}

glm::vec4 Renderer::CalculateViewportBounds() const
{
	glm::vec3 position = m_camera->GetPosition();

	float viewport_width = -position.z;
	float viewport_height = viewport_width * (9.0f / 16.0f);

	float left = position.x - viewport_width / 2;
	float bottom = position.y - viewport_height / 2;
	float right = left + viewport_width;
	float top = bottom + viewport_height;

	return glm::vec4(left, right, bottom, top);
}

SpriteBatch& Renderer::GetSpriteBatch()
{
	return m_sprite_batch;
}
