#pragma once

#include "Game.h"

class LibraryItem
{
	public:
		LibraryItem(const std::string&, Game*, const std::string&);
		~LibraryItem();
		const std::string& GetPurchased() const;
		const Game *game;
	private:
		const std::string purchased;
		const std::string playtime;  // TODO: replace with custom Date class, currently YYYY-MM-DD
};
