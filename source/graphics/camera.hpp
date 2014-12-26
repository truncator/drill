#pragma once

#include "precompiled.hpp"

//
// Camera
//

class Camera
{
public:
	Camera(glm::vec3 position);

	void Update(double dt);

	void Move(glm::vec3 dp);
	void MoveTo(glm::vec3 position);

	// Get accessors.
	const glm::vec3& GetPosition() const;

private:
	glm::vec3 m_position;
	glm::vec3 m_target;
	float m_easing;
};
