#ifndef REORDERBUFFER_H
#define REORDERBUFFER_H

#include<list>

struct ROB_STARK {		// sorry I watch GOT.
	bool valid;				// validity
	unsigned int inst;		// instruction
	int ROB_ID;				// id
};

class ReorderBuffer{
	std::list<ROB_STARK> ROB_SET;
public:
	ReorderBuffer();
	~ReorderBuffer();

	void push_ROB(unsigned int inst);		//puts a new instruction on the ROB
	void pop_ROB_if_valid();				//pops the topmost valid instruction from ROB
	bool empty();							//to check if ROB is empty

	int get_ROB_ID();					//returns the last ROB_ID inputted into the queue
	void set_valid(int);

	void free_it();				// to empty the list for next code in line
};
#endif
