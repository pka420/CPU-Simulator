#include"ReorderBuffer.h"

ReorderBuffer::ReorderBuffer() {
	// constructor
}

ReorderBuffer::~ReorderBuffer() {
	//destructor
}

void ReorderBuffer::push_ROB(unsigned int inst) {
	ROB_STARK temp;				// temp struct
	temp.valid = false;						
	temp.inst = inst;
	if (ROB_SET.size())
		temp.ROB_ID = ROB_SET.back().ROB_ID + 1;	// previous ROB entry+1, if not first, else 0
	else 
		temp.ROB_ID = 0;		
	ROB_SET.push_back(temp);		
};

void ReorderBuffer::pop_ROB_if_valid(){
	if (ROB_SET.front().valid) ROB_SET.pop_front();	//if the oldest inst is validated, pop it
};

bool ReorderBuffer::empty(){
	if (ROB_SET.size() == 0)
		return 1;	
	else 
		return 0;
};

int ReorderBuffer::get_ROB_ID() {
	return ROB_SET.back().ROB_ID;
}

void ReorderBuffer::set_valid(int ID) { 
	for(auto it = ROB_SET.begin(); it != ROB_SET.end(); it++) {
		if(it->ROB_ID = ID) 
			it->valid = true;
	}
}

void ReorderBuffer::free_it() {
	ROB_SET.erase(ROB_SET.begin(), ROB_SET.end());
}