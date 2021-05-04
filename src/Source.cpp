#include <iostream>
#include <fstream>
#include <string>
#include "Application.h"
#include "Account.h"
#include "User.h"
#include "Player.h"
#include "Admin.h"
#include "Utils.h"
#include <limits>
#include "ListT.h"

using namespace std;

// TODO: Remove from global scope once menu system is integrated
Application app;
List<int> listGame;
List<string> listAccount;
List<string> listUser;
List<string> listLibrary;
char showLoginUserMenuAndGetUserChoice(Account *account);
int userPlayerIndex = 0;
void loginUserMenu();
void searchMenu();
void searchResultMenu();
void GetUserGames();
void removeUserMenu();
string searchPrice;
Player* u1;
string searchName;

void createHardcodedTestData()
{
    //read file 'data.txt'
    ifstream dataFile("data.txt");
	string gameCapitalString, indexOfGame, nameOfGame, description, price, age;

	//loop through each line in the file
	while(getline(dataFile, gameCapitalString)){
        if(gameCapitalString == "GAME"){
            getline(dataFile, indexOfGame);
            getline(dataFile, nameOfGame);
            getline(dataFile, description);
            getline(dataFile, price);
            getline(dataFile, age);

            int indexOfGameInt = stoi(indexOfGame);
            int ageInt = stoi(age);
            int priceInt = stoi(price);

            // Setup store with some games
            app.GetStore().games[indexOfGameInt] = new Game(nameOfGame, description, priceInt, ageInt);

            listGame.addAtEnd(indexOfGameInt);

        }
    }

    //read file 'data.txt'
    ifstream dataFileAccount("data.txt");
	string accountCapitalString, accountDate, accountName, accountPassword;
	int accountIndex;

	//loop through each line in the file
	while(getline(dataFileAccount, accountCapitalString)){
        if(accountCapitalString == "ACCOUNT"){
            accountIndex = listAccount.length();
            getline(dataFileAccount, accountDate);
            getline(dataFileAccount, accountName);
            getline(dataFileAccount, accountPassword);

            // Make an account and attach the users
            app.accounts[accountIndex] = new Account(accountName, accountPassword, accountDate);

            listAccount.addAtEnd(accountName);

        }
    }

    ifstream dataFileAccountPlayer("data.txt");
	string playerCapitalString, playerDate, playerName, playerPassword, playerCredits, playerLibraryItem;
    while(getline(dataFileAccountPlayer, playerCapitalString)){
        if(playerCapitalString == "ACCOUNT-PLAYER"){
            userPlayerIndex = listUser.length();
            getline(dataFileAccountPlayer, playerDate);
            getline(dataFileAccountPlayer, playerName);
            getline(dataFileAccountPlayer, playerPassword);
            getline(dataFileAccountPlayer, playerCredits);

            u1 = new Player(playerName, playerPassword, playerDate, playerCredits, "0");
            for(int i = 0; i < listAccount.length(); i++){
                app.accounts[i]->users[userPlayerIndex] = u1;
            }

            listUser.addAtEnd(playerName);
        }else if(playerCapitalString == "ACCOUNT-ADMIN"){
            userPlayerIndex = listUser.length();
            getline(dataFileAccountPlayer, playerDate);
            getline(dataFileAccountPlayer, playerName);
            getline(dataFileAccountPlayer, playerPassword);
            getline(dataFileAccountPlayer, playerCredits);

            u1 = new Admin(playerName, playerPassword, playerDate, playerCredits, "1");
            for(int i = 0; i < listAccount.length(); i++){
                app.accounts[i]->users[userPlayerIndex] = u1;
            }

            listUser.addAtEnd(playerName);
        }
    }

    /*
    ifstream dataFileAccountAdmin("data.txt");
	string adminCapitalString, adminDate, adminName, adminPassword, adminCredits;
    while(getline(dataFileAccountAdmin, adminCapitalString)){
        if(adminCapitalString == "ACCOUNT-ADMIN"){
            userPlayerIndex = listUser.length();
            getline(dataFileAccountAdmin, adminDate);
            getline(dataFileAccountAdmin, adminName);
            getline(dataFileAccountAdmin, adminPassword);
            getline(dataFileAccountAdmin, adminCredits);

            u1 = new Admin(adminName, adminPassword, adminDate, adminCredits);
            for(int i = 0; i < listAccount.length(); i++){
                app.accounts[i]->users[userPlayerIndex] = u1;
            }

            listUser.addAtEnd(userPlayerIndex);
        }
    }*/

    for(int i = 0; i < listLibrary.length(); i++){
        u1->library[i] = new LibraryItem("2018-06-17", app.GetStore().games[7], "320");
    }
}

char showMainMenuAndGetUserChoice()
{
	system("CLS");
	std::cout << "                    \n";
	std::cout << "  -= GAME LIBRARY =-\n";
	std::cout << "                    \n";
	std::cout << "  S) Browse Store   \n";

	if (app.IsUserLoggedIn())
	{
		std::cout << "  L) Logout of " << app.GetCurrentUser()->GetUsername() << "\n";
		std::cout << "  P) View profile for " << app.GetCurrentUser()->GetUsername() << "\n";
		// TODO: User profile option
	}
	else
	{
		std::cout << "  L) Login      \n";
	}

	std::cout << "                    \n";
	std::cout << "  B) Exit           \n";
	std::cout << "                    \n";
	std::cout << "                    \n";
	std::cout << "  >>> ";

	return Utils::getCharFromUser();
}

char showProfileMenuAndGetUserChoice()
{
	system("CLS");
	std::cout << "                    \n";
	std::cout << "  -= " << app.GetCurrentUser()->GetUsername() << "'s PROFILE =-       \n";
	std::cout << "                    \n";
	if (app.IsUserLoggedIn())
	{
	    string checkIfAdmin = app.GetCurrentUser()->CheckIfAmin();
	    int checkIfAdminInt = stoi(checkIfAdmin);

	    int userCredit = stoi(app.GetCurrentUser()->GetCredits());
	    std::cout << "  Credits: " << (userCredit)/100.0f << "\n";
		std::cout << "                                                      \n";
		std::cout << "  I) Purchase 1 credit " << "\n";
		std::cout << "  O) Purchase 10 credits " << "\n";
		std::cout << "  P) Purchase 100 credits " << "\n";
		std::cout << "                                                      \n";
		std::cout << "  GAMES      \n";
		if(listLibrary.length() < 1){
            std::cout << "  You do not own any games.                        \n";
		}else{
		    for (int i = 0; i < listLibrary.length(); i++)
            {
                std::cout << " "<< listLibrary.length() << "  " << (i + 1) << ") " << u1->library[i]->game->GetName() << "\n";
            }
		}

		if(checkIfAdminInt == 1){
            std::cout << "                                                      \n";
		    std::cout << "  ADMINISTRATOR      \n";
            std::cout << "  A) Add new user " << "\n";
            std::cout << "  R) Remove user " << "\n";
            std::cout << "  G) Guest per-game access " << "\n";
	    }else{
	        std::cout << "                                                      \n";
	    }
	}
	std::cout << "                    \n";
	std::cout << "                    \n";
	std::cout << "  B) Back           \n";
	std::cout << "                    \n";
	std::cout << "                    \n";
	std::cout << "  >>> ";

	return Utils::getCharFromUser();
}

char showSearchMenuAndGetUserChoice()
{
	system("CLS");
	std::cout << "                    \n";
	std::cout << "  -= SEARCH GAMES =-       \n";
	std::cout << "                    \n";

	int totalNumberOfGames = listGame.length();


	std::cout << "  SEARCHING " << totalNumberOfGames << " GAMES     \n";
	std::cout << "  N) Search by name          \n";
	std::cout << "  P) Search by price       \n";
	std::cout << "                    \n";


	std::cout << "                    \n";
	std::cout << "  B) Back           \n";
	std::cout << "                    \n";
	std::cout << "                    \n";
	std::cout << "  >>> ";

	return Utils::getCharFromUser();
}

char showSearchResultMenuAndGetUserChoice(int currentPage, bool nextPage)
{
	system("CLS");
	std::cout << "                    \n";
	std::cout << "  -= SEARCH RESULTS =-       \n";
	std::cout << "                    \n";

	if(listGame.length() > 0){
	}

	int totalNumberOfGames = listGame.length();

	int dividedByFive = totalNumberOfGames/5 + (totalNumberOfGames % 5 != 0);

	//These need to be initalized
	int i = 0;
	int j = 0;
	int countP = 0;


	if(currentPage == 1){
        i = 0;
        j = i;
        countP = i;
        // Output game list
        for (i; i < j + 5; i++) // TODO: Hardcoded, change when using List<T>
        {
            if(searchPrice != ""){
                int searchPriceInt = stoi(searchPrice);
                if(app.GetStore().games[i]->GetCost() == searchPriceInt){
                    std::cout << "  " << (i + 1) << ") " << app.GetStore().games[i]->GetName() << "\n";
                }
            }else{
                if(app.GetStore().games[i]->GetName() == searchName){
                    std::cout << "  " << (i + 1) << ") " << app.GetStore().games[i]->GetName() << "\n";
                }
            }

        }
	}else if(nextPage == true){
        j = j + 5;
        if(currentPage < dividedByFive){
            for (i; i < j + 5; i++) // TODO: Hardcoded, change when using List<T>
            {
                std::cout << "  " << (i + 1) << ") " << app.GetStore().games[i]->GetName() << "\n";
            }
        }else{
            for (i; i < totalNumberOfGames; i++) // TODO: Hardcoded, change when using List<T>
            {
                std::cout << "  " << (i + 1) << ") " << app.GetStore().games[i]->GetName() << "\n";
            }
        }
    }else if(nextPage == false){
	    i = i - 10;
	    j = j - 5;
        if(currentPage < dividedByFive){
            for (i; i < j + 5; i++) // TODO: Hardcoded, change when using List<T>
            {
                std::cout << "  " << (i + 1) << ") " << app.GetStore().games[i]->GetName() << "\n";
            }
        }else{
            for (i; i < totalNumberOfGames; i++) // TODO: Hardcoded, change when using List<T>
            {
                std::cout << "  " << (i + 1) << ") " << app.GetStore().games[i]->GetName() << "\n";
            }
        }
    }



	std::cout << "                    \n";
	std::cout << "                    \n";
	std::cout << "  PAGE " << currentPage << " OF " << dividedByFive << "\n";
	std::cout << "  S) Search          \n";
	if(currentPage > 1 && currentPage <  dividedByFive){
        std::cout << "  N) Next Page           \n";
        std::cout << "  P) Previous Page       \n";
	}else if(currentPage == 1){
	    std::cout << "  N) Next Page           \n";
	} else if(currentPage == dividedByFive){
	    std::cout << "  P) Previous Page       \n";
	}
	std::cout << "                    \n";
	std::cout << "                    \n";


	// TODO: Implement search store option

	// Output rest of menu

	std::cout << "                    \n";
	std::cout << "                    \n";
	std::cout << "  B) Back           \n";
	std::cout << "                    \n";
	std::cout << "                    \n";
	std::cout << "  >>> ";

	return Utils::getCharFromUser();

}

char showStoreMenuAndGetUserChoice(int currentPage, bool nextPage)
{
	system("CLS");
	std::cout << "                    \n";
	std::cout << "  -= STORE =-       \n";
	std::cout << "                    \n";

	int totalNumberOfGames = listGame.length();
	int dividedByFive = totalNumberOfGames/5 + (totalNumberOfGames % 5 != 0);

	int i = 0;
	int j = 0;
	int countP = 0;


	if(currentPage == 1){
        i = 0;
        j = i;
        countP = i;
        // Output game list
        for (i; i < j + 5; i++) // TODO: Hardcoded, change when using List<T>
        {
            std::cout << "  " << (i + 1) << ") " << app.GetStore().games[i]->GetName() << "\n";
        }
	}
	else if(nextPage == true)
	{
        j = j + 5;
        if(currentPage < dividedByFive){
            for (i; i < j + 5; i++) // TODO: Hardcoded, change when using List<T>
            {
                std::cout << "  " << (i + 1) << ") " << app.GetStore().games[i]->GetName() << "\n";
            }
        }else{
            for (i; i < totalNumberOfGames; i++) // TODO: Hardcoded, change when using List<T>
            {
                std::cout << "  " << (i + 1) << ") " << app.GetStore().games[i]->GetName() << "\n";
            }
        }
    }
	else if(nextPage == false)
	{
	    i = i - 10;
	    j = j - 5;
        if(currentPage < dividedByFive){
            for (i; i < j + 5; i++) // TODO: Hardcoded, change when using List<T>
            {
                std::cout << "  " << (i + 1) << ") " << app.GetStore().games[i]->GetName() << "\n";
            }
        }else{
            for (i; i < totalNumberOfGames; i++) // TODO: Hardcoded, change when using List<T>
            {
                std::cout << "  " << (i + 1) << ") " << app.GetStore().games[i]->GetName() << "\n";
            }
        }
    }



	std::cout << "                    \n";
	std::cout << "                    \n";
	std::cout << "  PAGE " << currentPage << " OF " << dividedByFive << "\n";
	std::cout << "  S) Search          \n";
	if(currentPage > 1 && currentPage <  dividedByFive){
        std::cout << "  N) Next Page           \n";
        std::cout << "  P) Previous Page       \n";
	}else if(currentPage == 1){
	    std::cout << "  N) Next Page           \n";
	} else if(currentPage == dividedByFive){
	    std::cout << "  P) Previous Page       \n";
	}
	std::cout << "                    \n";
	std::cout << "                    \n";


	// TODO: Implement search store option

	// Output rest of menu

	std::cout << "                    \n";
	std::cout << "                    \n";
	std::cout << "  B) Back           \n";
	std::cout << "                    \n";
	std::cout << "                    \n";
	std::cout << "  >>> ";

	return Utils::getCharFromUser();
}

char showLoginAccountMenuAndGetUserChoice()
{
	system("CLS");
	std::cout << "                    \n";
	std::cout << "  -= LOGIN Account=-       \n";
	std::cout << "                    \n";
	std::cout << "                    \n";

	// Output user list
	for (int i = 0; i < listAccount.length(); i++) // TODO: Hardcoded, change when using List<T>
	{

		std::cout << "  " << (i + 1) << ") " << app.accounts[i]->GetEmail()<< "\n";
	}

	// Output rest of menu
	std::cout << "  B) Back           \n";
	std::cout << "                    \n";
	std::cout << "                    \n";
	std::cout << "  >>> ";

	return Utils::getCharFromUser();
}

char showLoginUserMenuAndGetUserChoice(Account *account)
{
	system("CLS");
	std::cout << "                    \n";
	std::cout << "  -= LOGIN User=-       \n";
	std::cout << "                    \n";
	std::cout << "                    \n";

	// Output user list
	for (int i = 0; i < listUser.length(); i++) // TODO: Hardcoded, change when using List<T>
	{
		std::cout << "  " << (i + 1) << ") " << account->users[i]->GetUsername() << "\n";
	}

	if (app.IsAccountLoggedIn())
	{
		std::cout << "  L) Logout of " << app.GetCurrentAccount()->GetEmail() <<"\n";
	}

	// Output rest of menu
	std::cout << "                    \n";
	std::cout << "                    \n";
	std::cout << "  >>> ";

	return Utils::getCharFromUser();
}

char showRemoveUserMenuAndGetUserChoice(Account *account)
{
	system("CLS");
	std::cout << "                    \n";
	std::cout << "  -= REMOVE USER =-       \n";
	std::cout << "                    \n";
	std::cout << "                    \n";

	// Output user list
	for (int i = 0; i < listUser.length(); i++) // TODO: Hardcoded, change when using List<T>
	{
		std::cout << "  " << (i + 1) << ") " << account->users[i]->GetUsername() << "\n";
	}
	// Output rest of menu
	std::cout << "                    \n";
	std::cout << "                    \n";
	std::cout << "  B) Back                   \n";
	std::cout << "                            \n";
	std::cout << "                            \n";
	std::cout << "  >>> ";

	return Utils::getCharFromUser();
}

char showGameMenuAndGetUserChoice(Game* game)
{
	system("CLS");
	std::cout << "                                  \n";
	std::cout << "  -= " << game->GetName() << " =- \n";
	std::cout << "                                  \n";
	std::cout << "  " << game->GetDescription() << "\n";
	std::cout << "  Costs:" << (game->GetCost() / 100.0f) << "\n";
	std::cout << "                                  \n";

	if (app.IsUserLoggedIn())
	{
	    int userCredit = stoi(app.GetCurrentUser()->GetCredits());
	    std::cout << "  Credits: " << (userCredit)/100.0f << "\n";
		std::cout << "                                                      \n";
		std::cout << "  P) Purchase for " << (game->GetCost() / 100.0f) << "\n";
		std::cout << "                                                      \n";
	}

	std::cout << "  B) Back                   \n";
	std::cout << "                            \n";
	std::cout << "                            \n";
	std::cout << "  >>> ";

	return Utils::getCharFromUser();
}

void GetUserGames(){
    listLibrary.addAtEnd("1");
}

void gameMenu(Game* game)
{
	bool readyToGoBack = false;

	while (readyToGoBack == false)
	{
		int choice = showGameMenuAndGetUserChoice(game);

		switch (choice)
		{
			case 'P': {
				if (app.IsUserLoggedIn())
				{
					// TODO: Implement buying from the store
				}
			} break;
			case 'B': {
				readyToGoBack = true;
			} break;
		}
	}
}

void profileMenu()
{
	bool readyToGoBack = false;

	while (readyToGoBack == false)
	{
		int choice = showProfileMenuAndGetUserChoice();

		switch (choice)
		{
			case 'B': {
				readyToGoBack = true;
			}break;
			case 'I': {
			    app.GetCurrentUser()->SetOneCredit();
			}break;
			case 'O': {
				app.GetCurrentUser()->SetTenCredit();
			}break;
			case 'P': {
				app.GetCurrentUser()->SetHundredCredit();
			}break;
			case 'A': {
				std::cout << "  Enter Username : ";
                string nameEntered = Utils::getLineFromUser();
				std::cout << "  Enter Password : ";
                string passwordEntered = Utils::getLineFromUser();
                u1 = new Player(nameEntered, passwordEntered, "2018-06-17", "0", "0");
                app.GetCurrentAccount()->users[listUser.length()] = u1;
                listUser.addAtEnd(nameEntered);

			}break;
			case 'R': {
				removeUserMenu();
			}break;
			case 'G': {
				std::cout << " Not implemented! " << endl;
			}break;
			default: {
				int index = choice - '1';

				if (index >= 0 && index < listGame.length()) // TODO: Hardcoded numbers, change when using List<T>
				{
					cout << " " << index << " " << endl;
				}
			} break;
		}
	}
}

void searchMenu()
{
	bool readyToGoBack = false;

	while (readyToGoBack == false)
	{
		int choice = showSearchMenuAndGetUserChoice();

		switch (choice)
		{
			case 'B': {
				readyToGoBack = true;
			} break;
			case 'N': {
				std::cout << "  Enter name to search for: ";
				string nameEntered = Utils::getLineFromUser();
                searchName = nameEntered;
                searchResultMenu();
			} break;
			case 'P': {
				std::cout << "  Enter price range (e.g. 5-10): ";
				string priceEntered = Utils::getLineFromUser();
                searchPrice = priceEntered;
                searchResultMenu();
			} break;
			default: {
			} break;
		}
	}
}

void searchResultMenu()
{
	bool readyToGoBack = false;
	int currentPge = 1;
	bool nextPge = false;

	while (readyToGoBack == false)
	{

		int choice = showSearchResultMenuAndGetUserChoice(currentPge, nextPge);

		int totalNumberOfGames = listGame.length();
		int dividedByFive = totalNumberOfGames/5 + (totalNumberOfGames % 5 != 0);

		switch (choice)
		{
			case 'B': {
				readyToGoBack = true;
			} break;
			case 'S': {
				searchMenu();
			} break;
			case 'N': {
			    if(currentPge < dividedByFive){
                    currentPge++;
                    nextPge = true;
			    }else{
			        currentPge = 1;
			    }
			} break;
			case 'P': {
			    if(currentPge > 1){
                    currentPge--;
                    nextPge = false;
			    }else{
			    }
			} break;
			default: {
				int index = choice - '1';

				if (index >= 0 && index < listGame.length()) // TODO: Hardcoded numbers, change when using List<T>
				{
					gameMenu(app.GetStore().games[index]);
				}
			} break;
		}
	}
}

void storeMenu()
{
	bool readyToGoBack = false;

	int currentPge = 1;
	bool nextPge = false;

	while (readyToGoBack == false)
	{
		int choice = showStoreMenuAndGetUserChoice(currentPge, nextPge);

		int totalNumberOfGames = listGame.length();
		int dividedByFive = totalNumberOfGames/5 + (totalNumberOfGames % 5 != 0);

		switch (choice)
		{
			case 'B': {
				readyToGoBack = true;
			} break;
			case 'S': {
				searchMenu();
			} break;
			case 'N': {
			    if(currentPge < dividedByFive){
                    currentPge++;
                    nextPge = true;
			    }else{
			        currentPge = 1;
			    }
			} break;
			case 'P': {
			    if(currentPge > 1){
                    currentPge--;
                    nextPge = false;
			    }else{
			    }
			} break;
			default: {
				int index = choice - '1';

				if (index >= 0 && index < listGame.length()) // TODO: Hardcoded numbers, change when using List<T>
				{
					gameMenu(app.GetStore().games[index]);
				}
			} break;
		}
	}
}

void loginAccountMenu()
{
	bool readyToGoBack = false;

	while (readyToGoBack == false)
	{
	    if(app.IsUserLoggedIn()){
            readyToGoBack = true;
	    }else{

	        int choice = showLoginAccountMenuAndGetUserChoice();

	        switch (choice)
	        {
	            case 'B': {
	                readyToGoBack = true;
                } break;
                default: {
                    int index = choice - '1';

                    if (index >= 0 && index < listAccount.length()) // TODO: Hardcoded numbers, change when using List<T>
                    {
                        std::string userEmail = app.accounts[index]->GetEmail();
                        std::string userPassword = app.accounts[index]->GetPassword();

                        std::cout << "  Enter password for " << userEmail << ": ";
                        if(Utils::getLineFromUser() == userPassword){
                            app.LoginAccount(userEmail, userPassword, index);
                            loginUserMenu();
                        }
                    }
                } break;
            }
        }
    }
}

void loginUserMenu()
{
	bool readyToGoBack = false;

	while (readyToGoBack == false)
	{
		int choice = showLoginUserMenuAndGetUserChoice(app.GetCurrentAccount());

		switch (choice)
		{
			case 'L': {
			    app.LogoutAccount();
				readyToGoBack = true;
			} break;
			default: {
				int index = choice - '1';

				if (index >= 0 && index < listUser.length()) // TODO: Hardcoded numbers, change when using List<T>
				{
					std::string username = app.GetCurrentAccount()->users[index]->GetUsername();
					std::string userPassword = app.GetCurrentAccount()->users[index]->GetPassword();

					std::cout << "  Enter password for " << username << ": ";
					if(Utils::getLineFromUser() == userPassword){
                        if (app.LoginUser(username, userPassword, index))
                        {
                            readyToGoBack = true;
                        }
					}

				}
			} break;
		}
	}
}

void removeUserMenu()
{
	bool readyToGoBack = false;

	while (readyToGoBack == false)
	{
		int choice = showRemoveUserMenuAndGetUserChoice(app.GetCurrentAccount());

		switch (choice)
		{
			case 'B': {
				readyToGoBack = true;
			} break;
			default: {
				int index = choice - '1';

				if (index >= 0 && index < listUser.length()) // TODO: Hardcoded numbers, change when using List<T>
				{
					listUser.deleteOne(app.GetCurrentAccount()->users[index]->GetUsername());
                }
			} break;
		}
	}
}

void mainMenu()
{
	bool wantsToExit = false;

	while (wantsToExit == false)
	{
		int choice = showMainMenuAndGetUserChoice();

		switch (choice)
		{
			case 'S': {
				storeMenu();
			} break;
			case 'P': {
				profileMenu();
			} break;
			case 'L': {
				if (app.IsAccountLoggedIn())
				{
					loginUserMenu();
				}
				else
				{
				    loginAccountMenu();
				}/*
				if (app.IsUserLoggedIn())
				{
					app.LogoutUser();
				}
				else
				{
					loginUserMenu();
				}*/
			} break;
			case 'B': {
				wantsToExit = true;
			} break;
		}
	}
}

int main()
{

	// TODO: Remove call to dummy data, instead use Load and Save
	createHardcodedTestData();

	// TODO: app.Load();

	mainMenu(); // TODO: replace with proper menu system

	// TODO: app.Save();
}
