#pragma once

#include "precompiled.hpp"
#include "../map/tile.hpp"

//
// Item
//

class Item
{
public:

	//
	// Item Type
	//

	enum Type
	{
		Grass,
		Limestone,

		Iron,
		Silver,
		Gold,

		ItemCount,
		None
	};

public:
	Item(Item::Type type);

	Item::Type GetType() const;

	static std::string GetName(Item::Type type);
	static Item::Type GetTypeFromTile(Tile::Type type);

private:
	Item::Type m_type;
};

//
// Hash
//

namespace std
{
	template<>
	struct hash<Item::Type>
	{
		std::size_t operator()(const Item& item) const
		{
			return (int)item.GetType();
		}
	};
}
