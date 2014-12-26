#include "drill.hpp"

#include "../map/tile.hpp"

Drill::Drill(glm::vec2 rig_position) :
	m_rig_position(rig_position),
	m_rig_size(glm::vec2(1, 2)),
	m_bit_position(m_rig_position + glm::vec2(1, -m_rig_size.y + 2)),
	m_bit_width(1),
	m_active(false),
	m_cooldown(0.1f),
	m_timer(m_cooldown)
{
}

void Drill::Update(Tile& tile, double dt)
{
	if (!m_active)
		return;

	m_timer -= (float)dt;

	if (m_timer <= 0.0f)
	{
		m_timer = m_cooldown;
		Pulse(tile);
	}
}

void Drill::Activate()
{
	m_active = true;
}

void Drill::Deactivate()
{
	m_active = false;
}

void Drill::Pulse(Tile& tile)
{
	tile.Damage(1);

	if (tile.IsDead())
		m_bit_position.y -= 1.0f;
}

const glm::vec2& Drill::GetRigPosition() const
{
	return m_rig_position;
}

const glm::vec2& Drill::GetRigSize() const
{
	return m_rig_size;
}

const glm::vec2& Drill::GetBitPosition() const
{
	return m_bit_position;
}

const int Drill::GetBitWidth() const
{
	return m_bit_width;
}
