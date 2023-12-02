#include "../Headers/Backend.h"

#define BOOKPATH "res/books.csv"
#define USERPATH "res/users.csv"



void BookReadingMenu() {
	std::cout << "1. Next Page\n";
	std::cout << "2. Previous Page\n";
	std::cout << "3. Stop Reading\n"; 
}

Book BookType(std::string& info) {
	Book bk;

	std::string  token;
	std::istringstream iss(info);
	getline(iss, token, ',');
	bk.ISBN = std::stoll(token);
	getline(iss, token, ',');
	bk.Title = token;
	getline(iss, token, ',');
	bk.AuthorName = token;
	getline(iss, token, ',');
	int sz = std::stoi(token);
	bk.size = sz;
	for (int i = 0; i < sz; ++i) {
		getline(iss, token, ',');
		bk.content.push_back(token);
	}
	return bk;
		
}


std::vector<std::string> ReadFile(const std::string& path) {
	std::fstream file(path.c_str()); 
	if (file.fail()) {
		std::cerr << "\nCouldn't open book file\n"; 
		return {}; 
	}
	std::vector<std::string> info; 
	std::string line;  
	while (getline(file, line)) {
		info.push_back(line); 
	}
	return info; 
}

void Admin::AddBook() {
	Book book; 
	std::cout << "Enter ISBN: "; 
	std::cin >> book.ISBN;  
	std::cin.ignore(); 
	std::cout << "\nEnter Title: "; 
	getline(std::cin, book.Title); 
	std::cout << "\nEnter Author Name: "; 
	getline(std::cin, book.AuthorName); 
	std::cout << "\nEnter How many pages: "; 
	std::cin >> book.size; 
	std::cin.ignore(); 
	
	std::string BookContent; 
	for (size_t i = 0; i < book.size; i++) {
		std::cout << "\n Enter page # " << i + 1 << ": "; 
		getline(std::cin, BookContent); 
		book.content.push_back(BookContent); 
	}
	SystemBooks.push_back(book); 
	std::string books = book.CSVInfo(); 
	WriteFile( books, BOOKPATH , true);

}


void WriteFile(const std::string &info, const std::string& path, bool append = true)
{
	auto status = std::ios::in | std::ios::out | std::ios::app ; 
	if (!append) {
		status =  std::ios::in | std::ios::out | std::ios::trunc;
	}
	std::fstream file(path.c_str(), status);
	if (file.fail()) {
		std::cerr << "\nFailed to open books file!!\n"; 
		return;
	}

	file << info << '\n'; 
	file.close(); 
}



std::string Admin::CSVInfo() {
	std::string csv{ "" }; 
	csv += username; 
	csv += ','; 
	csv += password;  
	return csv; 
}


std::string User::CSVInfo() {
	std::string csv{ "" }; 
	csv += UserName; 
	csv += ','; 
	csv += password; 
	csv += ','; 
	csv += name; 
	csv += ','; 
	csv += email; 
	return csv; 
}

std::string Book::CSVInfo()
{
	std::string csv{ "" }; 

	csv += std::to_string(ISBN);
	csv += ','; 
	csv += Title; 
	csv += ','; 
	csv += AuthorName; 
	csv += ','; 
	csv += std::to_string(size); 
	csv += ','; 
	for (size_t i = 0; i < size; ++i) {
		if (i == size - 1) {
			csv += content[i]; 
			break; 
		}
		csv += content[i]; 
		csv += ','; 
	}
	return csv;
}
