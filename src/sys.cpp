#include "../Headers/sys.h"

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