#pragma once

//
// Light
//

class Light
{
public:
	Light();
	Light(glm::vec2 position, glm::vec3 color, float intensity, float falloff);

	// Set accessors.
	void SetPosition(const glm::vec2& position);
	void SetOffset(const glm::vec2& offset);
	void SetStatic(bool _static);
	void SetActive(bool active);

	// Get accessors.
	const glm::vec2& GetPosition() const;
	const glm::vec3& GetColor() const;
	float GetIntensity() const;
	float GetFalloff() const;
	const glm::vec2& GetOffset() const;
	bool IsStatic() const;
	bool IsActive() const;

private:
	glm::vec2 m_position;
	glm::vec3 m_color;
	float m_intensity;
	float m_falloff;

	// Used to offset the light from an entity's position.
	glm::vec2 m_offset;
	bool m_static;

	bool m_active;
};
