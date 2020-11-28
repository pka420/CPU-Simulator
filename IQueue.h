#ifndef IQUEUE_H
#define IQUEUE_H

#include"TFO_qu.h"
#include<iostream>
#include<iomanip>
#include<queue>
using namespace std;
class IQueue: public TFO_qu {
	std::queue<TFO_qu> IQ;
public:
	IQueue();
	~IQueue();
	bool TFO_pop();		// to pop an instruction from queue.
	bool TFO_push(const TFO_qu &q1);		//to push
	bool TFO_update(bool v1, bool v2);	// to update/broadcast the valid bits in next instructions.
	void print();		// for debuug to be honest.
	
	bool empty();

	TFO_qu get_front();			// to return head of the queue
	int get_id() const;			// to return id,
};

#endif