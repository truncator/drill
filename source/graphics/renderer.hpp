#pragma once

#include "spritebatch.hpp"

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

	SpriteBatch& GetSpriteBatch();

private:
	SpriteBatch m_sprite_batch;
	Camera* m_camera;
};
