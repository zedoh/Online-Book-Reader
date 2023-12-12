#include "../Headers/sys.h"
#include "../Headers/Backend.h"

#define BOOKPATH "res/books.csv"
#define USERPATH "res/usrDatabase.csv"
#define USERHISTORY "res/UserHistory.csv"


void Menu::ParentMenu() const{
	std::cout << "\n1: Login\n"; 
	std::cout << "\n2: Sign Up\n"; 
}


void Menu::ChildUserMenu() const {
	std::cout << "\nMenu:";
	std::cout << "\n\t1: View Profile\n"; 
	std::cout << "\n\t2: List & Select from My Reading History\n"; 
	std::cout << "\n\t3: List & Select from Available Books\n"; 
	std::cout << "\n\t4: Logout\n"; 
}


void Menu::ChildAdminMenu() const{
	std::cout << "\nMenu:"; 
	std::cout << "\n\t1: View Profile\n"; 
	std::cout << "\n\t2: Add Book\n"; 
	std::cout << "\n\t3: Logout\n"; 
}

void Menu::InlineMessage(int low, int high) const
{
	std::cout << "\nEnter a number in range " << low << " - " << high << ": ";
}

void Sys::signup() {
	User u; 
	std::string input; 
	std::cout << "\nEnter user name (No spaces): "; 
	std::cin >> input;
	u.UserName = input; 
	std::cout << "\nEnter password (No spaces): "; 
	std::cin >> input; 
	u.password = input; 
	std::cout << "\nEnter name (No spaces): "; 
	std::cin >> input; 
	u.name = input; 
	std::cout << "\nEnter email (No spaces): "; 
	std::cin >> input;
	u.email = input; 
	users.push_back(u); 
	std::string userinfo = u.CSVInfo(); 
	WriteFile(userinfo, USERPATH, true); 
	currentuser = &users.back(); 
	currentadmin = nullptr; 
	std::cout << "\nTesting current user pointer RTE: "; 
	std::cout << currentuser->name<<'\n';
}

void Sys::FillUsersAdmins()
{
	admins.clear(); 
	users.clear(); 
	std::vector<std::string>read = ReadFile(USERPATH); 
	for (auto& line : read) {
		std::string token; 
		std::istringstream iss(line); 
		getline(iss, token, ',');
		std::string sympol = token; 
		if (sympol == "#") {
			User u = UserType(line);
			users.push_back(u); 
		}
		else {
			Admin a = AdminType(line); 
			admins.push_back(a); 
		}
	}
}

void Sys::login() {
	// Load users and admins from the CSV file
	FillUsersAdmins();

	std::string input1, input2;
	std::cout << "\nEnter user name (no spaces): ";
	std::cin >> input1;
	std::cout << "\nEnter password (no spaces): ";
	std::cin >> input2;

	bool userFound = false;

	// Loop through each line in the user data CSV
	for (const auto& line : ReadFile(USERPATH)) {
		std::string sympol, username, password;
		std::istringstream iss(line);

		// Extract data from the CSV line
		getline(iss, sympol, ',');
		getline(iss, username, ',');
		getline(iss, password, ',');

		// Check if the entered username and password match
		if (input1 == username && input2 == password) {
			userFound = true;

			// Check if the user is a regular user
			if (sympol == "#") {
				for (auto& u : users) {
					if (u.UserName == username) {
						currentuser = &u;
						currentadmin = nullptr; 
						break;
					}
				}
			}
			// Check if the user is an admin
			else if (sympol == "*") {
				for (auto& a : admins) {
					if (a.username == username) {
						currentadmin = &a;
						currentuser = nullptr; 
						break;
					}
				}
			}
			break;
		}
	}

	if (!userFound) {
		std::cerr << "\nUser or Admin not found\n";
	}
	if (currentuser) {
		std::cout << "\nHello " << currentuser->name << " | User View\n"; 
	}
	else if(currentadmin) {
		std::cout << "\nHello " << currentadmin->username<< " | Admin View\n"; 
	}
}

void Sys::logout()
{
	if (currentadmin) {
		currentadmin = nullptr; 
	}
	else {
		currentuser = nullptr; 
	}
}


User Sys::UserType(std::string &info)
{
	User usr;
	std::string token; 
	std::istringstream iss(info);

	// Skip the first char (sympol)
	getline(iss, token, ','); 
	getline(iss, token, ','); 
	usr.UserName = token; 
	getline(iss, token, ','); 
	usr.password = token; 
	getline(iss, token, ','); 
	usr.name = token; 
	getline(iss, token, ','); 
	usr.email = token; 
	return usr;
}
Admin Sys::AdminType(std::string& info)
{
	Admin adm; 
	std::string token; 
	std::istringstream iss(info); 

	// Skip the first Char
	getline(iss, token, ','); 
	getline(iss, token, ','); 
	adm.username = token; 
	getline(iss, token, ','); 
	adm.password = token; 
	return adm; 
}


void Sys::AddBook()
{
	return currentadmin->AddBook(); 
}

void Sys::ViewProfile() {
	if (currentadmin)
		currentadmin->ViewProfile();
	else
		currentuser->ViewUserProfile(); 
}

void Sys::ReadFromHistory()
{
	currentuser->ReadFromHistory(); 
}

void Sys::ReadFromAvailable()
{
	currentuser->ReadFromAvailable(); 
}

void Sys::ListSystemBooks() {
	currentuser->ListSystemBooks(); 
}

void onlinebookreader::Run()
{
	menu.ParentMenu(); 
	int choice; 
	menu.InlineMessage(1, 2); 
	std::cin >> choice; 

	if (choice == 1) {
		sys.login(); 
	}
	else if (choice == 2) {
		
		sys.signup(); 
	}

	while (sys.currentadmin != nullptr) {
		menu.ChildAdminMenu();
		menu.InlineMessage(1, 3);
		std::cin >> choice;
		assert(choice >= 1 && choice <= 3);
		if (choice == 1) {
			sys.ViewProfile();
		}
		else if (choice == 2) {
			sys.AddBook();
		}
		else if (choice == 3) {
			sys.logout();
			break;
		}
	}
	while (sys.currentuser != nullptr) {
		menu.ChildUserMenu();
		menu.InlineMessage(1, 4);
		std::cin >> choice;
		assert(choice >= 1 && choice <= 4);
		if (choice == 1) {
			sys.ViewProfile();
		}
		else if (choice == 2)
		{
			sys.ReadFromHistory();
		}
		else if (choice == 3) {
			sys.ReadFromAvailable();
		}
		else if (choice == 4) {
			sys.logout();
		}
	}
}

