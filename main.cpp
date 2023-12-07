#include "Headers/sys.h"
using namespace std; 




int main() {
	User u("ziko","123","zeyad","sdkf@jj.com");
	User u1("mido","1e23","mohamed","vruce@hotmail.com");
	u.ReadFromHistory(); 


	cout << "\nUser No.2 Reading from last sessions\n"; 
	u1.ReadFromHistory(); 
	return 0; 
}