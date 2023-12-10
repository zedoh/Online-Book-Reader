#pragma once
#include "Backend.h"


struct Menu {
	void ParentMenu()const;
	void ChildUserMenu()const;
	void ChildAdminMenu()const;
	void InlineMessage(int low, int high)const; 
};



class Sys {
private:
	User* currentuser; 
	Admin* currentadmin;
	std::vector<User>users; 
	std::vector<Admin>admins;
	void signup();
	void login();
	void logout(); 
	void FillUsersAdmins(); 
	bool IsAdminLogged(); 
	bool AdminInTheSys(); 
	void AddBook(); 
	void ViewProfile(); 
	void ReadFromHistory(); 
	void ReadFromAvailable(); 
	void ListSystemBooks(); 
	User UserType(std::string& info); 
	Admin AdminType(std::string& info); // Convert CSV format to Book type
	friend class onlinebookreader; 
};

class onlinebookreader {
public:
	Menu menu; 
	Sys sys;
	void Run(); 
};
