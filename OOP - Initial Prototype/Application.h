#pragma once

#include "Account.h"
#include "User.h"
#include "Store.h"

class Application
{
	public:
		Application();
		~Application();

		bool IsAccountLoggedIn() const;
		bool IsUserLoggedIn() const;
		Account* GetCurrentAccount() const;
		User* GetCurrentUser() const;

		Store& GetStore();

		bool LoginAccount(const std::string& email, const std::string& password, int userIndex);
		bool LoginUser(const std::string& username, const std::string& password, int userIndex);
		void LogoutAccount();
		void LogoutUser();

		Account* accounts[1] = { }; // TODO: this needs changing to a dynamic collection
		Player* player[1] = { }; // TODO: this needs changing to a dynamic collection
	private:
		Store store;
		Account* currentAccount;
		User* currentUser;
};
