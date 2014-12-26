#pragma once

#include "precompiled.hpp"

// Forward declarations.
class Tile;

//
// Drill
//

class Drill
{
public:
	Drill(glm::vec2 position);

	void Update(Tile& tile, double dt);

	void Activate();
	void Deactivate();
	void Pulse(Tile& tile);

	// Get accessors.
	const glm::vec2& GetRigPosition() const;
	const glm::vec2& GetRigSize() const;
	const glm::vec2& GetBitPosition() const;
	const int GetBitWidth() const;

private:
	glm::vec2 m_rig_position;
	glm::vec2 m_rig_size;

	glm::vec2 m_bit_position;
	int m_bit_width;

	bool m_active;
	float m_cooldown;
	float m_timer;
};
