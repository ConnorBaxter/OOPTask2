#pragma once

#include <string>

class User
{
	public:
		User(const std::string&, const std::string&, const std::string&, const std::string&, const std::string&);
		virtual ~User();
		const std::string& GetUsername() const;
		const std::string& GetPassword() const;
		const std::string& GetCredits() const;
		const std::string& SetOneCredit();
		const std::string& SetTenCredit();
		const std::string& SetHundredCredit();
		const std::string& CheckIfAmin();
	private:
		std::string username;
		std::string password;
		std::string created;// TODO: replace with custom Date class, currently YYYY-MM-DD
		std::string credit;
		std::string isAdmin;
};
