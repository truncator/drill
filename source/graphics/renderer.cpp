#include "renderer.hpp"

#include "precompiled.hpp"
#include "camera.hpp"
#include "shader.hpp"
#include "texture.hpp"

Renderer::Renderer(Camera* camera) :
	m_sprite_batch(1000),
	m_camera(camera)
{
	assert(m_camera != nullptr);

	glClearColor(0.3f, 0.5f, 0.6f, 1.0f);
	glViewport(0, 0, 1280, 720);
}

void Renderer::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Prepare()
{
	glm::vec4 viewport = CalculateViewportBounds();
	glm::mat4 projection = glm::ortho<float>(viewport.x, viewport.y, viewport.z, viewport.w, 0.0f, 1.0f); 

	Shader::Bind("sky");
	Shader::SetUniformMatrix("projection", projection);

	Shader::Bind("base");
	Shader::SetUniformMatrix("projection", projection);

	Texture::Bind("texture");
}

void Renderer::PrepareScreenspace()
{
	// Winding must be reversed going from world to screenspace coordinates.
	glFrontFace(GL_CW);

	glm::mat4 projection = glm::ortho<float>(0.0f, 1280.0f, 720.0f, 0.0f, 0.0f, 1.0f);

	Shader::Bind("base_textured");
	Shader::SetUniformMatrix("projection", projection);
	Shader::SetUniformMatrix("model", glm::mat4());

	Texture::Bind("texture");
}

void Renderer::Cleanup()
{
	Texture::Unbind();
	Shader::Unbind("base");

	// Restore original winding.
	glFrontFace(GL_CCW);
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
