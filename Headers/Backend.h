#pragma once
#include <iostream>
#include <cassert>
#include <utility> 
#include <unordered_map>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <chrono>
#include <ctime>
#include <iomanip>
 


// TODO: Add Feature Users can't access the system while Admins are using it.

//----------------------------Forward Declarations---------------------//
struct Book; 

//----------------------------Utility Functions------------------------//
//Write a line on a CSV file 
void WriteFile( const std::string &info ,  const std::string& path, bool append); 

// Write a full file on a CSV file

void WriteFile(std::vector<std::string>& info, const std::string& path); 
// Reading from a CSV file
std::vector<std::string> ReadFile(const std::string& path); 


std::vector<Book> system_books();
size_t GetBookSize(const std::string &bookname) ; 

void BookReadingMenu(); 
//---------------------------------------------------------------------//
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



class Admin {

private:
	std::string username; 
	std::string password;
	std::string CSVInfo(); //username,password

	void AddBook(); 
	void ViewProfile(); 

	//void DeleteBook(); // TODO: Delete Book optional feature  

	friend class Sys;
};

/*
	*Admin Representation in CSV 
	* username,pass
	* ahmed,0000
	
	*!!!! NOTICE !!!!*
		 ADMINS have less info than USERS, Could be an indicator !!!!
	* User Representation in CSV
	* username,pass,name,email
*/



class User {
public:

	void ViewUserProfile(); 
	void ReadFromHistory(); 
	void ReadFromAvailable(); 
	void ListSystemBooks(); 
	

private:
	std::unordered_map<std::string , int>ReadingHistory; 
	void SaveHistory(const std::string user_name , std::string book_name , int page); 
	// Writing this history on a separate file with the following structure
	// username , book.title,current page
	// Write the user history before logging out

	std::unordered_map<std::string , int> ReadHistory(std::string username); 

	// Update the page values for books for specific user
	void UpdateHistory(std::string username ,std::string book_name , int page);

	// Returns the current page that user has stopped reading at by the username and the book name
	int GetCurrentPage(std::string username , std::string book_name); 

	

	std::string UserName;
	std::string password;
	std::string name;
	std::string email;

	std::string CSVInfo(); // CSV data entries format username,password,name,email
		

	friend class Sys; 
};

/*
	* System consists of: 
	* vector of Admins and Users 
		*Admins consist of book and functions 
	
*/
