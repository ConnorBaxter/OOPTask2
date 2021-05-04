#pragma once

#include <string>
#include "Player.h"

class Account
{
	public:
		Account(const std::string&, const std::string&, const std::string&);
		~Account();
		const std::string& GetEmail() const;
		const std::string& GetPassword() const;
		User* users[4] = { }; // TODO: replace with custom List<T> class
	private:
		std::string email;
		std::string password;
		std::string created;  // TODO: replace with custom Date class, currently YYYY-MM-DD
};
