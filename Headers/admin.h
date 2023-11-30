#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>

struct Book{
	long long ISBN; 
	std::string Title;
	std::string AuthorName; 
	size_t size; // Size of the book content 
	std::vector<std::string>content;
	std::string BookInfo(); 
	/*
		* CSV Formula for representing books
		* 121234324,Deep Work,Cal Newport,4,this,book,is,good ==> (first book)
	*/
};

class BooksManager {
public:
	
	//----------For User Use-----------------//
	void ListSysBooks(); 

private:
	//--------------For Admin Use--------------//
	void AddBook(); 
	void DeleteBook(); 
	std::vector<Book> SystemBooks; // Storing System books, Works as a MEDIUM between Code and the Database

	// ------------------------Utility------------------------------//
	std::vector<std::string> BookstoString();
	std::vector<Book> ReadFile(const std::string &path);  // Reading from a CSV File. 
	void WriteFile(std::vector<std::string>& books, const std::string &path, bool append); // Writing on a CSV File.
	Book ToBookType(std::string &info); // converting string info back to the book container type 
};
