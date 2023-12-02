#pragma once
#include <iostream>
#include <cassert>
#include <utility> 
#include <unordered_map>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>


//----------------------------Utility Functions------------------------//

//Write on a CSV file 
void WriteFile( const std::string &info ,  const std::string& path, bool append); 

// Reading from a CSV file
std::vector<std::string> ReadFile(const std::string& path); 

void BookReadingMenu(); 
 
struct Book{
	long long ISBN; 
	std::string Title;
	std::string AuthorName; 
	size_t size; // Size of the book content 
	std::vector<std::string>content;

	std::string CSVInfo(); 
	Book BookType(std::string& info);
};
	/*
		* CSV Format for representing books
		* ISBN     ,Title    ,Author  ,size,page1,2  ,3 ,4
		* 121234324,Deep Work,Cal Newport,4,this,book,is,good 
	*/

class SystemManager {
public:
	


private:
	//--------------For Admin Use--------------//
	void ViewAdminProfile(); 
	void DeleteBook(); // TODO: Delete Book optional feature  


	friend class Admin; 

};


class Admin {
private:
	std::string username; 
	std::string password;
	std::string CSVInfo(); //username,password
	Admin AdminType(std::string& info); // Convert CSV format to Book type
	void AddBook(); 
	std::vector<Book> SystemBooks; // Storing System books, Works as a MEDIUM between Code and the Database
	friend class sys;
};



/*
	*Admin Representation in CSV 
	* username,pass
	* ahmed,0000
	
	*!!!! NOTICE!!!!*
		 ADMINS have less info than USERS, Could be an indicator !!!!
	* User Representation in CSV
	* username,pass,name,email
*/
class User {
public:

	void ViewUserProfile(); 
	void ListSysBooks(); 
	void ListHistory(); // List and Select from reading history opt
	void ListAvailable(); //List available books
	std::pair<Book, int> ReadBook(); // Return book and stopped page

private:
	std::unordered_map<Book, std::pair<int,int>>ReadingHistory; //TODO: Change pair.second (int) to Date type
	// returns book,(stopped page , date)

	User UserType(std::string& info); 
	std::string UserName;
	std::string password;
	std::string name;
	std::string email;

	std::string CSVInfo(); // CSV data entries format username,password,name,email
	User ToUserType(); 
};

