#ifndef PIPELINE_H
#define PIPELINE_H

#include"instruction.h"
#include"IQueue.h"
#include"memory.h"
#include"ReorderBuffer.h"
#include"Statistics.h"
#include"TFO_qu.h"
#include"ALU.h"
#include<iostream>
#include<string>

using namespace std;

class pipeline {
	instruction inst;		// just one instruction
	IQueue IQ;				// this is a queue of instructions 			-- this is a list
	memory m;				// our memory unit							-- we will load file here
	ALU alu;				// our ALU unit
	ReorderBuffer ROB_ID;	// Our list of Reoerder Buffer sets			-- this is also a list
	Statistics stats;		// our stats class -- have to make some graphs
	int PC;

	bool debug;				// for debug mode
	bool finished;			// like finished signal in hardware or other machines.
public:
	
	pipeline();
	//pipeline(int );		//-- if needed later
	~pipeline();

	void fetch();						// to fetch the instructions

	void execute();
	void execute_R();		// helper functions for execute()
	void execute_I();		//	""
	void execute_J();		//	""
	void execute_P();		//	""		-- 'i' is the index of IQ that we gonna execute.

	void commit();						// to commit to the demon

	bool load_memory(string str);		// to load file
	void update_stats();				// to update statistics
	bool is_finished();					// to check finished signal or to terminate the run.

	bool convert_inst_to_IQ_push(int ROB_ID);		// convert from instruction to IQueue type
	bool update_IQ();			// to update validity in Queue.

	void free_for_next();		// to free mem. iQ and ....

	void set_debug_mode();		// to set to debug mode, default is normal mode.
};

#endif