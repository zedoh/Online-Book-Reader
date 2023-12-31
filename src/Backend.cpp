#include "../Headers/Backend.h"

#define BOOKPATH "res/books.csv"
#define USERPATH "res/usrDatabase.csv"
#define USERHISTORY "res/UserHistory.csv"

 

void WriteFile(std::vector<std::string>& info, const std::string& path) {
	auto status = std::ios::in | std::ios::out | std::ios::trunc; 
	std::fstream file(path.c_str(), status); 
	if (file.fail()) {
		std::cerr << "\nCan't open users history file\n";
	}
	 
	for (auto& line : info) {
		file << line << '\n'; 
	}
	file.close(); 
}

size_t GetBookSize(const std::string &bookname) {
	std::vector<Book> mybooks = system_books(); 
	for (auto& bk : mybooks) {
		if (bk.Title == bookname) {
			return bk.size; 
		}
	}
	return 0; 
}


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
	std::vector<Book> SystemBooks = system_books(); 
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
	WriteFile(books, BOOKPATH, true);

}

void Admin::ViewProfile()
{
	std::cout << "username: " << username<<'\n';
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
	csv += '*'; // Char works as an indication for Admins.
	csv += username; 
	csv += ','; 
	csv += password;  
	return csv; 
}



void User::ViewUserProfile()
{
	std::cout << "name: "<<name <<'\n';
	std::cout << "email: " << email << '\n'; 
	std::cout << "user name: " <<UserName<< '\n'; 
	return; 
}

void  User::ReadFromHistory()
{
	ReadingHistory = ReadHistory(UserName); 
	if (ReadingHistory.empty()) {
		std::cerr << "\nYou Don't have any books in your reading history yet, Please read from the available books in the library first!!\n";
		return; 
	}
	int i{ 1 }; 
	for (auto& x : ReadingHistory) {
		std::cout << i << " : " << x.first << "\tPage: " << x.second.first << "/" << GetBookSize(x.first) << '\t' << x.second.second << '\n'; //TODO : Required to add date and time to this printing
		++i; 
	}

	std::vector<Book> books ; // books that user have read before
	std::vector<Book> BOOKS = system_books(); 
	for (auto& x : ReadingHistory) {
		for (size_t i = 0; i < BOOKS.size(); ++i) {
			if (BOOKS[i].Title == x.first) {
				books.push_back(BOOKS[i]); 
			}
		}
	}


	int choice;
	std::cout << "\nWhich session to open?:\n";
	std::cout << "Enter number in range 1 - " << books.size() << ": ";
	std::cin >> choice;
	std::cout << "\n\n"; 
	assert(choice >= 1 && choice <= books.size());
	Book bk = books[choice - 1];
	int page = GetCurrentPage(UserName, bk.Title);
	std::string time; 
	while (true) {
		std::cout << bk.content[page-1]<<"\n\n";
		BookReadingMenu();
		std::cout << "Enter number in range 1 - 3: ";
		std::cin >> choice;
		std::cout << "\n\n"; 
		if (choice == 1) {
			if (page == bk.size) {
				std::cout << "\n---------------------------------------\n";
				std::cerr << "\nYou reached the last page already";
				std::cout << "\n---------------------------------------\n\n";
				ReadingHistory[bk.Title].first = page;
				time = TimeString(); 
				ReadingHistory[bk.Title].second = time; 
				continue; 
				//break;
			}
			++page; 
			time = TimeString();
		}
		else if (choice == 2) {

			if (page == 1) {
				std::cout << "\n---------------------------------------\n";
				std::cerr << "\nYou are in  the first page !";
				std::cout << "\n---------------------------------------\n\n";
				ReadingHistory[bk.Title].first = page;
				time = TimeString(); 
				ReadingHistory[bk.Title].second = time; 
				continue; 
				//break;
			}
			else {
				--page;
				time = TimeString(); 
			}
		}
		else if (choice == 3) {
			ReadingHistory[bk.Title].first = page;
			time = TimeString();
			ReadingHistory[bk.Title].second = time;
			break;
		}
		UpdateHistory(UserName, bk.Title, page, time); 
	}
	// Update the User History CSV file with the new page value 
	/*
		* The Function should take username,bookname,newpage value
		* Read the UserHistory CSV file. 
		* Go to the specific line that contains username,bookname, update the new page value
		* write the whole file with trunc opt
	*/
}

int User::GetCurrentPage(std::string username,std::string book_name) {
	std::unordered_map <std::string, std::pair<int,std::string>> history = ReadHistory(username); 
	for (auto& x : history) {
		if (x.first == book_name) {
			return x.second.first; // current page number <page,currenttime>
		}
	}
	return -1; 
}
void  User::ReadFromAvailable()
{
	
	int choice; 
	std::vector<Book>SystemBooks = system_books(); 
	std::unordered_map <std::string , std::pair<int,std::string>>MyHistory = ReadHistory(UserName); 

	std::cout << "\nOur current book collection:\n";
	for (size_t i = 0; i < SystemBooks.size(); ++i) {
		std::cout << i + 1 << "\t";
		std::cout << SystemBooks[i].Title<<'\n';
	}
	std::cout << "\nWhich book to read?\n"; 
	std::cout << "Enter number in range 1 - "<<SystemBooks.size()<<" : ";
	std::cin >> choice; 
	assert(choice >= 1 && choice <= SystemBooks.size()); 
	Book bk = SystemBooks[choice - 1]; 
	if (ReadingHistory.count(bk.Title)) {
		std::cout << "\nAlready in your reading history!!\n";
		return; 
	}
	int page{ 1 };
	while (true) {
		std::cout << "\nCurrent page: " << page << " / " << bk.size << "\n\n";
		std::cout << bk.content[page-1]<<'\n';
		BookReadingMenu();
		std::cout << "Enter number in range 1 - 3: ";
		std::cin >> choice;
		if (choice == 1) {
			if (page == bk.size) {
				std::cerr << "\nYou reached the last page already\n";
				ReadingHistory[bk.Title].first= page;
				break;
			}
			++page; 
		}
		else if (choice == 2) {

			if (page == 1) {
				std::cerr << "\nYou are in  the first page !\n";
				ReadingHistory[bk.Title].first = page;
				break;
			}
			else {
				--page;
			}
		}
		else if (choice == 3) {
			ReadingHistory[bk.Title].first= page; 
			break;
		}

	}
	SaveHistory(UserName, bk.Title, page); 
}

void User::ListSystemBooks()
{
	std::vector<Book> books = system_books(); 
	for (size_t i = 0; i < books.size(); ++i) {
		std::cout << i + 1 << ": " << books[i].Title << "\n"; 
	}
}


std::string User::CSVInfo() {
	std::string csv{ "" }; 
	csv += '#'; 
	csv += ','; 
	csv += UserName; 
	csv += ','; 
	csv += password; 
	csv += ','; 
	csv += name; 
	csv += ','; 
	csv += email; 
	return csv; 
}


std::vector<Book> system_books()
{
	std::vector<std::string>ReadFromCSV = ReadFile(BOOKPATH);
	std::vector<Book>CurrentBooks; 
	Book bk;
	for (auto& line : ReadFromCSV) {
		bk  = BookType(line); 
		CurrentBooks.push_back(bk); 
	}
	return CurrentBooks;
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

Book Book::BookType(std::string& info)
{
	Book bk; 
	std::string token;
	std::istringstream iss(info); 
	getline(iss, token, ','); 
	bk.ISBN = std::stoll(token); 
	getline(iss, token, ','); 
	bk.Title = token; 
	getline(iss, token, ','); 
	bk.AuthorName = token;
	getline(iss, token, ','); 
	int sz = std::stoi(token); 
	bk.size = (size_t)sz; 
	
	for (size_t i = 0; i < bk.size; ++i) {
		getline(iss, token, ','); 
		bk.content.push_back(token); 
	}

	return bk;
}

void User::SaveHistory(const std::string user_name, std::string book_name, int page) {
	std::string History{ "" };
	History += user_name; 
	History += ','; 
	History += book_name; 
	History += ','; 
	History += std::to_string(page); 
	History += ','; 
	History += TimeString(); 
	WriteFile(History,USERHISTORY,true); 
}


// TODO: Refactor this Trash Implementation!!!!
void User::UpdateHistory(std::string username , std::string book_name, int page ,const std::string &time) {
	std::vector<std::string>history = ReadFile(USERHISTORY); 
	std::vector<std::string>NewHistory; 
	for (auto& line : history) {
		std::string token; 
		std::istringstream iss(line); 
		getline(iss, token, ','); 
		std::string usr = token; 
		getline(iss, token, ','); 
		std::string book = token; 
		if (usr == username) {
			if (book == book_name) {
				std::string NewCSV{ "" }; 
				std::string num = std::to_string(page); 
				NewCSV += username; 
				NewCSV += ','; 
				NewCSV += book_name; 
				NewCSV += ','; 
				NewCSV += num; 
				NewCSV += ','; 
				NewCSV += time; 
				NewHistory.push_back(NewCSV);
			}
			else {
				NewHistory.push_back(line);
			}
		}
		else {
			NewHistory.push_back(line); 
		}
	}
	WriteFile(NewHistory, USERHISTORY); 
}

//TODO: Add date and time for the reading history
std::unordered_map<std::string, std::pair<int , std::string>> User::ReadHistory(std::string username) {
	std::vector<std::string>history = ReadFile(USERHISTORY); 
	for (auto& line : history) {
		std::string token; 
		std::istringstream iss(line); 
		getline(iss, token, ',');
		if (token == username) {
			getline(iss, token, ',');
			std::string bookname = token;
			getline(iss, token, ',');
			int page = std::stoi(token);
			getline(iss, token, ','); 


			ReadingHistory[bookname].first = page;
			ReadingHistory[bookname].second = token; 
		}
		else {
			continue; 
		}
	}
	return ReadingHistory;
}


std::string TimeString() {
	auto now = std::chrono::system_clock::now();
	auto timepoint = std::chrono::system_clock::to_time_t(now);

	struct tm timeinfo;
	localtime_s(&timeinfo, &timepoint);

	std::stringstream ss;
	ss << std::put_time(&timeinfo, "%Y-%m-%d %X");
	return ss.str();
}
