#pragma once

#include "precompiled.hpp"
#include "item.hpp"

//
// Inventory
//

class Inventory
{
public:
	// Type declarations.
	typedef std::unordered_map<Item::Type, int> ItemList;
	typedef ItemList::const_iterator ItemIterator;

public:
	Inventory();

	void AddItem(Item::Type type, int amount);

	ItemIterator GetItem(Item::Type type) const;

private:
	ItemList m_items;
};
