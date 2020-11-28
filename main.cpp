#include <iostream>
#include "pipeline.h"
int ISSUE_WIDTH	= 1;
using namespace std;
int main(){

	cout << "Type 'exit' to terminate this application"<<endl;
	
	string input;
	pipeline pipe;

	while(true) {
		cout << "Enter a program for execution: "<<endl;
		getline(cin, input);

		if(input == "exit") 
			break;
		else {
			if(input[input.length()-1] == 'd') {
				pipe.set_debug_mode();
				int pos = input.find(' ');
				input = input.substr(0, pos);	// removes the garbage we write.
				//cout<<input<<endl; // for debug
				cout<<"opening in debug mode"<<endl;
			}
			try {
			if(pipe.load_memory(input)) {
					// file has been read
				do{
					pipe.fetch();
					if(pipe.is_finished())
						break;

					for(int i=0;i<ISSUE_WIDTH;i++) {
						pipe.execute();
					}

					pipe.commit();

					pipe.update_stats();		// we update every clock cycle.
				}while(pipe.is_finished() != true);
				pipe.free_for_next();
			}	
		} catch(string str) {
			cout<<"ERROR: "<<str<<endl;
			abort();
		}

	}
	}
	return 0;
};