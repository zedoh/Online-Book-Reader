#include "Headers/admin.h"
using namespace std; 




int main() {

	BooksManager test1; 
	test1.AddBook(); 
	cout << "\n\n Add new book to the system....\n"; 
	cout.flush();
	//test1.AddBook(); 
	cout << "Listing System Books\n"; 
	test1.ListSysBooks(); 


	return 0; 
}