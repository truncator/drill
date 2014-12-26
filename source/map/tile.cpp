#include "tile.hpp"

Tile::Tile() :
	Tile(Tile::Type::None)
{
}

Tile::Tile(Tile::Type type) :
	m_type(type),
	m_color(GetInitialColor()),
	m_solid(true),
	m_dirty(false),
	m_health(GetInitialHealth())
{
}

void Tile::Damage(int damage)
{
	assert(damage >= 0);

	if (IsDead())
		return;

	m_health -= damage;

	if (IsDead())
	{
		MakeDirty();
		SetSolid(false);
	}
}

bool Tile::IsDead() const
{
	return m_health <= 0 || !m_solid;
}

void Tile::MakeDirty()
{
	m_dirty = true;
}

void Tile::CleanDirty()
{
	m_dirty = false;
}

bool Tile::IsDirty() const
{
	return m_dirty;
}

void Tile::SetType(Tile::Type type)
{
	m_type = type;

	// Reassign the color.
	m_color = GetInitialColor();
}

void Tile::SetSolid(bool solid)
{
	m_solid = solid;

	// Reassign the color.
	m_color = GetInitialColor();
}

Tile::Type Tile::GetType() const
{
	return m_type;
}

const glm::vec3& Tile::GetColor() const
{
	return m_color;
}

int Tile::GetHealth() const
{
	return m_health;
}

int Tile::GetInitialHealth() const
{
	if (!m_solid)
		return 0;

	switch(m_type)
	{
		case Tile::Type::Grass:
			return 1;
		case Tile::Type::Limestone:
			return 2;
		case Tile::Type::Iron:
			return 3;
		case Tile::Type::Silver:
			return 3;
		case Tile::Type::Gold:
			return 3;
		default:
			return 1;
	}
}

glm::vec3 Tile::GetInitialColor() const
{
	glm::vec3 variation = glm::vec3(Random::Float(-1.0f, 1.0f) * 0.025f);

	if (m_solid)
	{
		switch(m_type)
		{
			case Tile::Type::Grass:
				return glm::vec3(0.5f, 0.55f, 0.3f) + variation;
			case Tile::Type::Limestone:
				return glm::vec3(0.5f, 0.5f, 0.5f) + variation;
			case Tile::Type::Iron:
				return glm::vec3(0.7f, 0.6f, 0.5f) + variation;
			case Tile::Type::Silver:
				return glm::vec3(0.7f, 0.7f, 0.7f) + variation;
			case Tile::Type::Gold:
				return glm::vec3(0.8f, 0.65f, 0.4f) + variation;
			default:
				return glm::vec3(1.0f, 0.0f, 1.0f) + variation;
		};
	}
	else
	{
		switch(m_type)
		{
			case Tile::Type::Grass:
				return glm::vec3(0.3f, 0.35f, 0.15f) + variation;
			case Tile::Type::Limestone:
				return glm::vec3(0.3f, 0.3f, 0.3f) + variation;
			case Tile::Type::Iron:
				return glm::vec3(0.36f, 0.32f, 0.28f) + variation;
			case Tile::Type::Silver:
				return glm::vec3(0.5f, 0.5f, 0.5f) + variation;
			case Tile::Type::Gold:
				return glm::vec3(0.51f, 0.45f, 0.3f) + variation;
			default:
				return glm::vec3(1.0f, 0.0f, 1.0f) + variation;
		};
	}
}
