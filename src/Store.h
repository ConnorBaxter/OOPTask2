#pragma once

#include "Game.h"

class Store
{
	public:
		Store();
		~Store();
		Game* games[20] = { }; // TODO: should be a dynamic collection
	private:
};
