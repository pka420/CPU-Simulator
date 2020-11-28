#include"IQueue.h"

bool IQueue::empty() {
	if(IQ.size() == 0)
		return 1;
	return 0;
}

IQueue::IQueue() {
	//constructor
	
}

IQueue::~IQueue() {
	//destructor
}

bool IQueue::TFO_push(const TFO_qu &q1) {
	IQ.push(q1);
	return 1;
}

bool IQueue::TFO_pop() {
	// pops the top element of the queue
	if(IQ.size()>0)
		IQ.pop();
	else 
		return 0;
	return 1;
}

bool IQueue::TFO_update(bool v1, bool v2) {
	// update the queue while broadcasting/ commintitng
	IQ.front().set_v1(v1);
	IQ.front().set_v2(v2);
	return 1;
}

void IQueue::print() {
	cout<<"printing IQ's head: "<<endl;
	cout<<"---------------------------instruction queue----------------------------------------"<<endl;
	cout<<"type    valid1    src1 	  valid2    src2    op_code    dest 	immediate    ROB_ID"<<endl;
	cout<<setw(4)<<get_front().get_type();
	cout<<setw(8)<<get_front().get_v1();
	cout<<setw(7)<<get_front().get_src1();
	cout<<setw(10)<<get_front().get_v2();
	cout<<setw(9)<<get_front().get_src2();
	cout<<setw(9)<<get_front().get_opcode();
	cout<<setw(13)<<get_front().get_dest();
	cout<<setw(7)<<get_front().get_imm();
	cout<<setw(12)<<get_front().get_id()<<endl;

	
}


TFO_qu IQueue::get_front() {
	return IQ.front();
}

int IQueue::get_id() const {
	return IQ.front().get_id();
}