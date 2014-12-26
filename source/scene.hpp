#pragma once

#include "graphics/camera.hpp"
#include "map/map.hpp"
#include "drill/drill.hpp"

// Forward declarations.
class SpriteBatch;

//
// Scene
//

class Scene
{
public:
	Scene();

	void Update(double dt);

	void Draw(SpriteBatch& sprite_batch);

	// Get accessors.
	Camera& GetCamera();

private:

private:
	Camera m_camera;
	Map m_map;

	Drill m_drill;
};
