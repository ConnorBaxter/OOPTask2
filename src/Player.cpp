#include "Player.h"

Player::Player(const std::string& username, const std::string& password, const std::string& created, const std::string& credit, const std::string& isAdmin)
	: User(username, password, created, credit, isAdmin)
{
}

Player::~Player()
{
	for (int i = 0; i < 2; ++i)
	{
		delete library[i];
	}
}
