#include "camera.hpp"

Camera::Camera(glm::vec3 position) :
	m_position(position),
	m_target(position),
	m_easing(0.25f)
{
}

void Camera::Update(double dt)
{
	glm::vec3 dp = m_target - m_position;
	m_position += dp * (1.0f + 1.0f / m_easing) * (float)dt;

	/*
	// Low FPS mode.
	glm::vec3 dp = m_target - m_position;
	m_position += dp;
	*/
}

void Camera::Move(glm::vec3 dp)
{
	m_position += dp;
}

void Camera::MoveTo(glm::vec3 position)
{
	m_target = position;
}

const glm::vec3& Camera::GetPosition() const
{
	return m_position;
}
