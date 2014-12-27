#pragma once

#include "graphics/camera.hpp"
#include "map/map.hpp"
#include "drill/drill.hpp"
#include "item/inventory.hpp"
#include "graphics/light.hpp"

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
	void Draw(SpriteBatch& sprite_batch, const glm::vec4& viewport_bounds);

	void PassLightUniforms();

	// Get accessors.
	Camera& GetCamera();

private:

private:
	Camera m_camera;
	Map m_map;

	Drill m_drill;
	Inventory m_inventory;

	std::vector<Light> m_lights;
};
