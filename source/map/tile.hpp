#pragma once

//
// Tile
//

class Tile
{
public:

	//
	// Tile Type
	//

	enum Type
	{
		None,

		Grass,
		Limestone,

		Iron,
		Silver,
		Gold,

		TypeCount
	};

public:
	Tile();
	Tile(Tile::Type type);

	void Damage(int damage);
	bool IsDead() const;

	void MakeDirty();
	void CleanDirty();
	bool IsDirty() const;

	void SetType(Tile::Type type);
	void SetSolid(bool solid);

	// Get accessors.
	Tile::Type GetType() const;
	const glm::vec3& GetColor() const;
	int GetHealth() const;

private:
	int GetInitialHealth() const;
	glm::vec3 GetInitialColor() const;

private:
	Tile::Type m_type;
	glm::vec3 m_color;

	bool m_solid;
	bool m_dirty;
	int m_health;
};