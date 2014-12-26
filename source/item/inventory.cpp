#include "inventory.hpp"

Inventory::Inventory()
{
	for (int i = 0; i < Item::Type::ItemCount; i++)
	{
		m_items.emplace((Item::Type)i, 0);
	}
}

void Inventory::AddItem(Item::Type type, int amount)
{
	auto it = m_items.find(type);
	assert(it != m_items.end());

	assert(amount > 0);
	it->second += amount;
}

Inventory::ItemIterator Inventory::GetItem(Item::Type type) const
{
	auto it = m_items.find(type);
	assert(it != m_items.end());

	return it;
}
