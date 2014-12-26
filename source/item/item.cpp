#include "item.hpp"

Item::Item(Item::Type type) :
	m_type(type)
{
}

Item::Type Item::GetType() const
{
	return m_type;
}

std::string Item::GetName(Item::Type type)
{
	switch (type)
	{
		case Item::Type::Grass:
			return "Grass";
		case Item::Type::Limestone:
			return "Limestone";
		case Item::Type::Iron:
			return "Iron";
		case Item::Type::Silver:
			return "Silver";
		case Item::Type::Gold:
			return "Gold";
		default:
			return "null";
	};
}

Item::Type Item::GetTypeFromTile(Tile::Type type)
{
	switch (type)
	{
		case Tile::Type::Grass:
			return Item::Type::Grass;
		case Tile::Type::Limestone:
			return Item::Type::Limestone;
		case Tile::Type::Iron:
			return Item::Type::Iron;
		case Tile::Type::Silver:
			return Item::Type::Silver;
		case Tile::Type::Gold:
			return Item::Type::Gold;
		default:
			return Item::Type::None;
	};
}
