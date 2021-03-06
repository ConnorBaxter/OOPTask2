#include "Application.h"

Application::Application() : currentAccount(nullptr), currentUser(nullptr)
{
}

Application::~Application()
{
	for (int i = 0; i < 1; ++i)
	{
		delete accounts[i];
	}
}

bool Application::IsUserLoggedIn() const
{
	return currentUser != nullptr;
}

bool Application::IsAccountLoggedIn() const
{
	return currentAccount != nullptr;
}

Account* Application::GetCurrentAccount() const
{
	return currentAccount;
}

User* Application::GetCurrentUser() const
{
	return currentUser;
}

Store& Application::GetStore()
{
	return store;
}

bool Application::LoginAccount(const std::string& email, const std::string& password, int userIndex)
{
	// TODO: This currently always logs you in as the first account
	currentAccount = accounts[userIndex];

	return true;
}

void Application::LogoutAccount()
{
	currentAccount = nullptr;
}

bool Application::LoginUser(const std::string& username, const std::string& password, int userIndex)
{
	//This wont work, compiles but returns null?
	//currentUser = currentAccount->users.getItemAtIndex[userIndex];
	
	// TODO: This currently always logs you in as the first user
	currentUser = currentAccount->users[userIndex];

	return true;
}

void Application::LogoutUser()
{
	currentUser = nullptr;
}
