#include "Admin.h"

Admin::Admin(const std::string& username, const std::string& password, const std::string& created, const std::string& credit, const std::string& isAdmin)
	: Player(username, password, created, credit, isAdmin)
{
}

Admin::~Admin()
{
}
