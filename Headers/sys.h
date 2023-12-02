#pragma once
#include "Backend.h"


struct Menu {
	struct ParentMenu {
	
	};

	struct UserMenu {

	};

	struct AdminMenu {

	};
};

class Sys {

private:
	Menu menu;
	std::vector<User> users; 
	std::vector<Admin> admins; 
	void WriteInfo(std::vector<std::string>& info, std::string path, bool append);

};
