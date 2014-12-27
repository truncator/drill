#pragma once

#include "precompiled.hpp"

// Forward declarations.
class Light;

//
// Light Source
//     Interface for attaching lights to an object.
//

class LightSource
{
public:
	// Attach a light to the light source with a position offset.
	void AttachLight(Light* light, const glm::vec2& offset);

	// Move lights to their positions, ignoring static flags.
	void InitializeLights(const glm::vec2& position);

	// Update non-static light positions.
	void UpdateLights(const glm::vec2& position);

protected:
	LightSource() { }
	LightSource& operator=(const LightSource& light_source) { }

private:
	// Pointers to lights for modifiying. These are not owned by the object,
	// but are owned by the scene.
	std::vector<Light*> m_lights;
};
