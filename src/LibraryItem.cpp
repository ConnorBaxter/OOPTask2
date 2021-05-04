#include "LibraryItem.h"

LibraryItem::LibraryItem(const std::string& purchased, Game* game, const std::string& playtime)
	: purchased(purchased), game(game), playtime(playtime)
{
}

LibraryItem::~LibraryItem()
{
}
const std::string& LibraryItem::GetPurchased() const
{
	return purchased;
}
