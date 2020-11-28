#include "Statistics.h"

Statistics::Statistics() {
	//constructor
}
Statistics::Statistics(int size) {
	// overloaded constructor
	latencies.reserve(size);
	throughputs.reserve(size);
	int cycles=0;
	int current_throughput=0;
};

Statistics::~Statistics() {
	// destructor
	std::unordered_map<double, int>::iterator it = latencies.begin();
	latencies.erase(it, latencies.end() );
	// latencies has been deleted
	// vector throughputs would be erased automatically by c++.
};

void Statistics::update_cycle() {
	cycles++;
}
void Statistics::update_latency(double time, int ROB_ID) { 
	//latencies.find(ROB_ID)->first = time;		// getting time from main and updating this list
}
void Statistics::update_current_throughput(){
	throughputs.push_back(current_throughput);	//store latestThroughput
	current_throughput = 0;						//reset it to 0 for the next cycle
};

void Statistics::print_stats() {
	double avg_lat = 0;		// average latency
	double avg_tp = 0;		// average throughput

	for(auto it = latencies.begin(); it != latencies.end(); it++) 
		avg_lat = avg_lat + it->second;

	for(int i=0;i<throughputs.size();i++)
		avg_tp = avg_tp + throughputs[i];

	avg_lat = avg_lat/avg_tp;		
	avg_tp = avg_tp/cycles;		
	std::cout << "Average latency per instruction: " << avg_lat << std::endl;
	std::cout << "Average throughput per cycle: " << avg_tp << std::endl;	
}