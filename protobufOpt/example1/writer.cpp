#include <iostream>
#include <fstream>
#include "addr.book.pb.h"

using namespace std; 

int main(void) 
{ 
	addr::book msg1;
	msg1.set_id(101); 
	msg1.set_str("book1"); 

	fstream output("log", ios::out | ios::trunc | ios::binary); 
 
	if (!msg1.SerializeToOstream(&output)) { 
		cerr << "Failed to write msg." << endl; 
		return -1; 
	}         
	return 0; 
}
