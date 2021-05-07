#include "User.h"
#include <string>

User::User(const std::string& username, const std::string& password, const std::string& created, const std::string& credit, const std::string& isAdmin)
	: username(username), password(password), created(created), credit(credit), isAdmin(isAdmin)
{
}

User::~User()
{
}

const std::string& User::GetUsername() const
{
	return username;
}

const std::string& User::GetPassword() const
{
	return password;
}

const std::string& User::GetCredits() const
{
	return credit;
}

const std::string& User::SetOneCredit()
{
    int creditInt = stoi(credit);
    int increasedCreditInt = creditInt + 100;
	credit = std::to_string(increasedCreditInt);
	return credit;
}

const std::string& User::SetTenCredit()
{
    int creditInt = stoi(credit);
    int increasedCreditInt = creditInt + 1000;
	credit = std::to_string(increasedCreditInt);
	return credit;
}

const std::string& User::SetHundredCredit()
{
    int creditInt = stoi(credit);
    int increasedCreditInt = creditInt + 10000;
	credit = std::to_string(increasedCreditInt);
	return credit;
}

const std::string& User::CheckIfAmin()
{
	return isAdmin;
}
