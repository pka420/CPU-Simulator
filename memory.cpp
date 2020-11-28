#include"memory.h"

memory::memory() {
	instruction_memory.reserve(20);		// assuming 10 instructiosn to come in
	rf[0].data = 0;
	rf[0].valid = 1;
	for(int i=1;i<16;i++) {
		rf[i].data =0;
		rf[i].valid = 1;
	}
}
memory::memory(const int size, const string str) {
	rf[0].data = 0;
	rf[0].valid = 1;
	for(int i=1;i<16;i++) {
		rf[i].data =0;
		rf[i].valid = 1;
	}
	instruction_memory.reserve(size);
	read_csv(str);		// reading csv
}

memory::~memory() {
	// destructor
	// our rf will be automatically destructed.
	// vector will also be deleted automatically
}

bool memory::read_csv(const string str) {		// str is file's name
	//POST CONDITION:
	// reads the file and store the instructions_memory vector
	unsigned int temp;

	ifstream fin;
	fin.open(str);
	if(fin.fail() == true) {
		throw("cannot open file "+str);
		return 0;
	}

	char ch;	// ch for comma ","
	while(!fin.eof()) {
		fin>>temp;
		instruction_memory.push_back(temp);
		//cout<<temp;	// to check nothing else
		fin>>ch;
	}

	return 1;
}

int memory::reg_at_read(const int pos) {
	//post : returns the register file's content at position pos.
	if(pos>16 || rf[pos].valid == 0)
		throw("voilation access of memory");
	return rf[pos].data;
}

bool memory::reg_at_write(const int pos, const int num) {
	//post : write at the the register file's content at position pos the value of num.
	if(pos<1) 	// can't write at pos =0 reserved by cpu in TFO
		return 0;
	else if(pos>16) {
		throw("memory_full");
		return 0;
	}

	rf[pos].data = num;
	rf[pos].valid = 1;
	return 1;
}

bool memory::reg_is_valid(const int pos) {
	// register's validity to write.
	if(pos>16)
		return 0;
	else 
		return rf[pos].valid;
}

unsigned int memory::get_instructions(const int pos ) {
	if(pos>instruction_memory.size())
		throw "no more instructions to fetch";
	return instruction_memory[pos];
}

bool memory::is_inst_left(const int pos) {	
	// POSt condition: returns 1 if there are instructions left in memory 0 otherwise
	if(pos>=instruction_memory.size())
		return 0;
	return 1;				// yes instructions are left
}

void memory::free_it() {
	instruction_memory.erase(instruction_memory.begin(), instruction_memory.end());
}


 //to check nothing else
/*
int main()
{
	/*string str = "fibonacci.csv";
	try{
		memory m(10, str);
	}
	catch(string str) {
		cerr<<str<<endl;
		abort();
	}
	
	memory m;
	m.reg_at_write(7,4);	// write 7 at 4.
	cout<<m.reg_is_valid(7)<<endl;
	return 0;
}
*/