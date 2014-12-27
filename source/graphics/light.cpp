#include "light.hpp"

Light::Light() :
	m_position(0.0f, 0.0f),
	m_color(0.0f, 0.0f, 0.0f),
	m_intensity(0.0f),
	m_falloff(0.0f),
	m_static(true),
	m_active(false)
{
}

Light::Light(glm::vec2 position, glm::vec3 color, float intensity, float falloff) :
	m_position(position),
	m_color(color),
	m_intensity(intensity),
	m_falloff(falloff),
	m_offset(0.0f, 0.0f),
	m_static(true),
	m_active(true)
{
}

void Light::SetPosition(const glm::vec2& position)
{
	m_position = position;
}

void Light::SetOffset(const glm::vec2& offset)
{
	m_offset = offset;
}

void Light::SetStatic(bool _static)
{
	m_static = _static;
}

void Light::SetActive(bool active)
{
	m_active = active;
}

const glm::vec2& Light::GetPosition() const
{
	return m_position;
}

const glm::vec3& Light::GetColor() const
{
	return m_color;
}

float Light::GetIntensity() const
{
	return m_intensity;
}

float Light::GetFalloff() const
{
	return m_falloff;
}

const glm::vec2& Light::GetOffset() const
{
	return m_offset;
}

bool Light::IsStatic() const
{
	return m_static;
}

bool Light::IsActive() const
{
	return m_active;
}
