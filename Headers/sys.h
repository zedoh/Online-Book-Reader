#pragma once
#include "Backend.h"


struct Menu {
	void ParentMenu()const;
	void ChildUserMenu()const;
	void ChildAdminMenu()const;
};

class Sys {
public:

private:
	Menu menu;
	std::vector<User> users; 
	std::vector<Admin> admins; 

};
