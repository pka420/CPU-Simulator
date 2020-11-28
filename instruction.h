#ifndef INSTRUCTION_H
#define INSTRUCTION_H

//#include"memory.h"
#include<bitset>
#include<string>
#include<iostream>
using namespace std;

class instruction {
	int inst_type;
	int src1;
	int src2;
	int dest;
	int op_code;
	int imm_value;

public:
	instruction();
	instruction(unsigned int n);
	instruction(const instruction& i);
	bool decode(unsigned int inst, int debug);	// to decode this thhing to all the private members we have
	int get_src1() const;
	int get_src2() const;
	int get_opcode() const;
	int get_type() ;
	int get_dest() const;
	int get_immediate() const;
};

#endif


