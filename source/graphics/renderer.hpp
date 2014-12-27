#pragma once

#include "spritebatch.hpp"
#include "light.hpp"

// Forward declarations.
class Camera;

//
// Renderer
//

class Renderer
{
public:
	Renderer(Camera* camera);

	// Clear the buffers.
	void Clear();

	// Set up state.
	void Prepare();
	void Cleanup();

	// Calculate the viewport bounds in world space.
	glm::vec4 CalculateViewportBounds() const;

	void PassLightUniforms(const std::vector<Light>& lights);

	SpriteBatch& GetSpriteBatch();

private:
	SpriteBatch m_sprite_batch;
	Camera* m_camera;
};
