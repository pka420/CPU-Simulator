#ifndef STATISTICS_H
#define STATISTICS_H

#include<iostream>
#include<vector>
#include<unordered_map>

class Statistics {
	int cycles;					// to keep a count on cycles
	int current_throughput;		// latest throughput
	std::unordered_map<double, int> latencies;		// map of ROB_ID and latencies 
	std::vector<int> throughputs;
public:
	Statistics();
	Statistics(int );
	~Statistics();

	void update_cycle();					//increments the clock
	void update_latency(double time, int ID);			//increments the latency of the ROB_ID
	void update_current_throughput();		//increments the current through put
	void update_throughput_list();			//pushes current throughput to a vector for updating and calculating at the end
	void print_stats();						// prints the stats after the program is done 

};

#endif