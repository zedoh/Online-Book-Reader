#include "../Headers/admin.h"

#define BOOKPATH "res/books.csv"

void BooksManager::AddBook() {
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
	std::vector<std::string> books = BookstoString(); 
	WriteFile( books, BOOKPATH , true);

}

std::vector<std::string> BooksManager::BookstoString()
{
	std::vector<std::string> BookStringInfo; 
	for (auto& book : SystemBooks) {
		BookStringInfo.push_back(book.BookInfo()); 
	}
	return BookStringInfo; 
}

std::vector<Book> BooksManager::ReadFile(const std::string& path)
{
	std::fstream file(path.c_str()); 
	std::string line; 
	std::vector<std::string> info;
	while (getline(file, line)) {
		info.push_back(line); 
	}

	std::vector<Book> books; 
	for (size_t i = 0; i < info.size(); ++i) {
		books.push_back(ToBookType(info[i])); 
	}
	return books;
}

void BooksManager::WriteFile(std::vector<std::string>& books, const std::string& path, bool append = true)
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

	for (auto& line : books) {
		file << line << "\n";
	}
	file.close(); 
}

Book BooksManager::ToBookType(std::string &info)
{
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

std::string Book::BookInfo() {
	std::string StringISBN = std::to_string(ISBN) ;
	std::string BooktoStr = "";
	BooktoStr += StringISBN;
	BooktoStr += ","; 
	BooktoStr += Title;
	BooktoStr += ","; 
	BooktoStr += AuthorName;
	BooktoStr += ","; 
	BooktoStr += std::to_string(size); 
	BooktoStr += ","; 
	for (size_t i = 0; i < size; ++i) {
		if (i == size - 1) {
			BooktoStr += content[i]; 
			break; 
		}
		BooktoStr += content[i]; 
		BooktoStr += ","; 
	}
	return BooktoStr; 
}

void BooksManager::ListSysBooks() {
	SystemBooks.clear(); 
	SystemBooks = ReadFile(BOOKPATH);
	std::vector<Book> test = ReadFile(BOOKPATH); 
	for (size_t i = 0; i < test.size(); ++i) {
		std::cout << "Book #" << i + 1 << " : " << test[i].Title << '\n'; 
	}
}


