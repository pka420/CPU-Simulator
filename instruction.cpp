#include"instruction.h"

instruction::instruction() {
	// constructor
	inst_type = 0;		// type of instruction 
	src1 = -1 ;
	src2 = -1 ;
	op_code = 0;
	imm_value = 0;
	dest = -1;
}

instruction::instruction(const instruction &i) {
	inst_type = i.inst_type;		
	src1 = i.src1 ;
	src2 = i.src2 ;
	op_code = i.op_code;
	imm_value = i.imm_value;
	dest = i.dest;
}

instruction::instruction(unsigned int n) {
	// overloaded constructor
	decode(n, 0);
}

std::string convert2binary(unsigned int n) {
	std::bitset<32> temp;
    for(int i=0;i<32;i++) {
    	temp[i] = n%2;
    	n = n/2;
    }
    //std::cout<<temp<<std::endl;			// to check thats all
    return temp.to_string();
}
bool instruction::decode(unsigned int inst, int debug) {
	// decode only 1 instruction passed as an argument in form of unsigned integer.
	std::string inst_bin;		// string of binary numbers
	inst_bin = convert2binary(inst);

	if(debug == 1) {
		std::cout<<"instruction converted to binary is: "<<std::endl;
		std::cout<<inst_bin<<std::endl;		//--to check thats all.
	}

	inst_type = stoi(inst_bin.substr(0,2), nullptr, 2);		// type- r, j, p or i
	switch (inst_type) {
		case 0 :	// R type
				op_code = stoi(inst_bin.substr(2, 4), nullptr, 2);
				dest = stoi(inst_bin.substr(6, 5), nullptr, 2);
				src1 = stoi(inst_bin.substr(11, 5), nullptr, 2);
				src2 = stoi(inst_bin.substr(16, 5), nullptr, 2);		// 15 to 19 src 2 rest unused

			break;
		case 1 :	//  i type
				op_code = stoi(inst_bin.substr(2, 4), nullptr, 2);
				dest = stoi(inst_bin.substr(6, 5), nullptr, 2);
				src1 = stoi(inst_bin.substr(11, 5), nullptr, 2);
				imm_value = stoi(inst_bin.substr(16), nullptr, 2);	// 15 to end is immediate value.
			break;
		case 2:		// j type
				imm_value = stoi(inst_bin.substr(2), nullptr, 2);		// from 2 to end its address.
			break;
		case 3:		// p type
				op_code = stoi(inst_bin.substr(2, 4), nullptr, 2);
				dest = stoi(inst_bin.substr(6, 5), nullptr, 2);
			break;
		default:
			std::cerr<<"ERROR: instruction type not supported"<<std::endl;
			return 0;
			break;
	}
	return 1;		// done successfully.
}

int instruction::get_src1() const {
	return src1;
}

int instruction::get_src2() const {
	return src2;
}

int instruction::get_immediate() const {
	return imm_value;
}

int instruction::get_dest() const {
	return dest;
}

int instruction::get_opcode() const {
	return op_code;
}
int instruction::get_type()  {
	return inst_type;
}

/*
			// to check nothing else.
int main() {
	instruction i1, i2, i3, i4;
	cout<<"I type"<<endl;
		i1.decode(1090519045, 1);
	cout<<"type :"<<i1.get_type()<<endl;
	cout<<"op_code :"<<i1.get_opcode()<<endl;
	cout<<"src2 :"<<i1.get_src2()<<endl;
	cout<<"src1 :"<<i1.get_src1()<<endl;
	cout<<"dest :"<<i1.get_dest()<<endl;	
	cout<<"i1mmedi1ate :"<<i1.get_immediate()<<endl<<endl;
		
		cout<<"R type"<<endl;
	i2.decode(2234368, 1);
	cout<<"type :"<<i2.get_type()<<endl;
	cout<<"op_code :"<<i2.get_opcode()<<endl;
	cout<<"src2 :"<<i2.get_src2()<<endl;
	cout<<"src1 :"<<i2.get_src1()<<endl;
	cout<<"dest :"<<i2.get_dest()<<endl;	
	cout<<"i2mmedi2ate :"<<i2.get_immediate()<<endl<<endl;
		
		cout<<"j type"<<endl;
	i3.decode(2147483663, 1);
	cout<<"type :"<<i3.get_type()<<endl;
	cout<<"op_code :"<<i3.get_opcode()<<endl;
	cout<<"src2 :"<<i3.get_src2()<<endl;
	cout<<"src1 :"<<i3.get_src1()<<endl;
	cout<<"dest :"<<i3.get_dest()<<endl;	
	cout<<"immediate :"<<i3.get_immediate()<<endl<<endl;

		cout<<"P type"<<endl;
	i4.decode(3225419776, 1);
	cout<<"type :"<<i4.get_type()<<endl;
	cout<<"op_code :"<<i4.get_opcode()<<endl;
	cout<<"src2 :"<<i4.get_src2()<<endl;
	cout<<"src1 :"<<i4.get_src1()<<endl;
	cout<<"dest :"<<i4.get_dest()<<endl;	
	cout<<"immediate :"<<i4.get_immediate()<<endl;
	return 0;
}
*/