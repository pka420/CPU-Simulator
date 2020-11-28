// pipe it is

#include"pipeline.h"
int FETCH_WIDTH = 1;
int COMMIT_WIDTH = 1;

pipeline::pipeline() {
	//constructor
	debug = false;
	finished =0;
	PC =0;
}

pipeline::~pipeline() {
	//destructor
}

void pipeline::set_debug_mode() {
	debug = true;
}

void pipeline::fetch() {
	if(debug == true)
		cout<<endl<<endl<<"----------------Fetching-------------------"<<endl;
	int i=0;
	while(i<FETCH_WIDTH) {
		unsigned int temp = m.get_instructions(PC);
		inst.decode(temp, debug);			// this will decode the instruction
		ROB_ID.push_ROB(temp);
		if(debug == true) {
			cout<<"#"<<PC<<" instruction: "<<temp<<endl;
			cout<<"type: "<<inst.get_type()<<endl;
		}

		convert_inst_to_IQ_push(ROB_ID.get_ROB_ID());		// this will convert the decoded inst and push it to the queue
		i++;
	}

}


void pipeline::execute_R() {
	// helper for execute() -- that is formal 
	// for rtype inst
	//IQ.print(); 	// to debug
	int temp = alu.run_ALU(IQ.get_front().get_opcode(), m.reg_at_read(IQ.get_front().get_src1()), m.reg_at_read(IQ.get_front().get_src2()));
	int check = m.reg_at_write(IQ.get_front().get_dest(), temp);		// pos, num

	if(debug == true) {
		cout<<"Writing "<<temp<<" at";
		cout<<" #r "<<IQ.get_front().get_dest()<<endl;
	}
	if(check == 0)
		throw("cannot write!");
	PC++;
}

void pipeline::execute_I() {
	// helper for execute() -- that is formal 
	if(IQ.get_front().get_opcode()<5) {		// checking if not branched.
		int temp = alu.run_ALU(IQ.get_front().get_opcode(), m.reg_at_read(IQ.get_front().get_src1()), IQ.get_front().get_imm() );
		int check = m.reg_at_write(IQ.get_front().get_dest(), temp);
		if(debug == true) {
			cout<<"Writing "<<temp<<" at";
			cout<<" #r "<<IQ.get_front().get_dest()<<endl;
		}
		if(check == 0)
			throw("cannot write!");
		PC++;
	}
	else {		// for branching
		if(IQ.get_front().get_opcode() == 5) {		// branch if equal
			//cout<<m.reg_at_read(IQ.get_front().get_dest())<<endl; 
			//cout<<m.reg_at_read(IQ.get_front().get_src1())<<endl;
			if(m.reg_at_read(IQ.get_front().get_dest()) == m.reg_at_read(IQ.get_front().get_src1()) ) {
				PC = IQ.get_front().get_imm();
			}
			else
				PC++;
			if(debug == true) {
				cout<<"In branch if equal"<<" comparing r"<<IQ.get_front().get_dest()<<"and r"<<m.reg_at_read(IQ.get_front().get_src1())<<endl;
				cout<<"PC changed to"<<PC<<endl;
			}
		}
		else if(IQ.get_front().get_opcode() == 6) { 	// branch not equal
			if(m.reg_at_read(IQ.get_front().get_dest()) != m.reg_at_read(IQ.get_front().get_src1()) ) {
				PC = IQ.get_front().get_imm();
			}
			else
				PC++;
			if(debug == true) {
				cout<<"In branch not equal"<<" comparing r"<<IQ.get_front().get_dest()<<"and r"<<IQ.get_front().get_src1()<<endl;
				cout<<"PC changed to"<<PC<<endl;
			}
		}
		else
			throw("ERROR: Invalid r-type instruction in pipeline");
	}
}

void pipeline::execute_J() {
	// helper for execute() -- that is formal 
	PC = IQ.get_front().get_imm();	//this was easy
	if(debug == true)
		cout<<"Jumping to instruction #"<<PC<<endl;
	if(m.is_inst_left(PC) == false) {
		throw("no instruction at #"+PC);
	}
}

void pipeline::execute_P() {
	// helper for execute() -- that is formal 
	int temp;
	if(IQ.get_front().get_opcode() == 7 || IQ.get_front().get_opcode() == 8) {
		cout<<"Result: "<<m.reg_at_read(IQ.get_front().get_dest())<<endl;		// printing result available at dest
		PC++;
	}
	else if(IQ.get_front().get_opcode()<5) {		// call r type to do some work
		cout<<"Enter parameter: "<<endl;
		cin>>temp;
		int check = m.reg_at_write(IQ.get_front().get_dest(), temp);
		PC++;
		if(check == 0)
			throw("cannot write!");
	}
	else {
		throw("ERROR: Invalid p-type instruction in pipeline");
	}
}

void pipeline::execute() {
	//printing IQ
	if(debug == true) {
		IQ.print();
	}

	if(IQ.empty())
		return;
		switch(IQ.get_front().get_type()) {
			case 0:				// R-type
				if(debug == true) {
					cout<<"Solving R-type instruction."<<endl;
				}
				if(IQ.get_front().get_v1()==0 || IQ.get_front().get_v2() == 0) {
					throw("ERROR: Invalid sources in pipeline");
					return;
				}
				execute_R();
				break;
			case 1:			// I type
				if(debug == true) {
					cout<<"Solving I-type instruction."<<endl;
				}
				execute_I();
				break;
			case 2:
				if(debug == true)
					cout<<"Solving J-type instruction."<<endl;
				execute_J();
				break;
			case 3:
				if(debug == true)
					cout<<"Solving P-type instruction."<<endl;
				execute_P();
				break;
		}
	// execution is done
	// updating stats and ROB ID
	ROB_ID.set_valid(IQ.get_id() );		// current rob id is done
	IQ.TFO_pop();						// deleting oldest instruction in queue.
	update_IQ();
	// debug mode---- here

	stats.update_current_throughput();			// increasing current throughput
}

void pipeline::commit() {
	if(debug == true)
		cout<<"----------------commiting----------------"<<endl;
	for(int i=0; i<COMMIT_WIDTH; i++) {
		if(ROB_ID.empty()) {
			return;		// nothing to commit there was no fucking execution, why?? ask debug
			finished = 0;
		}
	if(m.is_inst_left(PC) == false) {
		if(debug == true)
			cout<<"No more instruction left to fetch, we are done soldiers."<<endl;
		finished = 1;
		return;
	}
		if(debug ==true) {
			cout<<"commiting ROB_ID: "<<ROB_ID.get_ROB_ID()<<endl;
		}
		ROB_ID.pop_ROB_if_valid();
	}
}


bool pipeline::load_memory(string str) {
	return m.read_csv(str);
}

void pipeline::update_stats() {

}

bool pipeline::is_finished() {
	return finished;
}


bool pipeline::convert_inst_to_IQ_push(int ROB_ID) 
{	
	TFO_qu temp;
	temp.set_type(inst.get_type());
	switch(inst.get_type()) {
		case 0:		//r-type
			temp.set_src1(inst.get_src1());
			temp.set_src2(inst.get_src2());
			temp.set_dest(inst.get_dest());
			temp.set_op_code(inst.get_opcode());
			break;
		case 1: 	// inst type:
			temp.set_dest(inst.get_dest());
			temp.set_imm(inst.get_immediate());
			temp.set_src1(inst.get_src1());
			temp.set_op_code(inst.get_opcode());
			break;
		case 2:		// j type:
			temp.set_imm(inst.get_immediate());
			break;
		case 3: 	// ptype:
			temp.set_dest(inst.get_dest());
			temp.set_op_code(inst.get_opcode());
			break;
		default:
			throw("unknown instruction in IQueue");
			return 0;
	}
	
	temp.set_id(ROB_ID);
	
	//setting validity
	temp.set_v1(m.reg_is_valid(temp.get_src1()));
	temp.set_v2(m.reg_is_valid(temp.get_src2()));
	
	IQ.TFO_push(temp);
	//cout<<IQ.get_front().get_dest()<<endl;
	return 1;
}

bool pipeline::update_IQ() {
	// update the queue while broadcasting/ commintitng
	//cout<<IQ.get_front().get_src1()<<endl;
	//cout<<m.reg_is_valid(IQ.get_front().get_src1())<<endl;
	//cout<<m.reg_is_valid(IQ.get_front().get_src2())<<endl;		// to debug this code.
	return IQ.TFO_update(m.reg_is_valid(IQ.get_front().get_src1()), m.reg_is_valid(IQ.get_front().get_src2()) );
}

void pipeline::free_for_next() {
	m.free_it();
	while(IQ.empty() != true)
		IQ.TFO_pop();
	ROB_ID.free_it();
	PC =0;
	finished = 0;
	debug = false;
}