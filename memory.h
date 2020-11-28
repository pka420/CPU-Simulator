#ifndef MEMORY_H
#define MEMORY_H

#include<iostream>
#include<fstream>
#include<string>
#include<vector>
using namespace std;

struct Register_file {
	int data;
	bool valid;			// 1 means valid for reading
						// 0 means invalid for reading and awaiting instruction's result
};

class memory {
	vector<unsigned int> instruction_memory;		// list of instructions read from csv
	Register_file rf[16];							// our register aka RAM
public:
	memory();
	memory(const int size, const string str);
	~memory();
	unsigned int get_instructions(const int);
	bool read_csv(const string );
	int reg_at_read(const int );		// reference because reg needs to be written by elo.
	bool reg_at_write(const int, const int);	// writing at Register_file 1st int is position and the other int is number to be written
	bool reg_is_valid(const int);
	bool is_inst_left(const int);		// to check if there are more instructions to fetch.
	void free_it();				// to free the memory
};

#endif

