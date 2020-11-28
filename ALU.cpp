#include"ALU.h"

int ALU::run_ALU(const int opcode, int op1, int op2) {
	int result=0;
	switch(opcode) {
		case 0:
			result = op1+op2;
			break;
		case 1:
			result = op1-op2;
			break;
		case 2:
			result = op1*op2;
			break;
		case 3:
			result = op1/op2;
			break;
		case 4:
			result = op1%op2;
			break;
		default:
			throw("invalid operation in ALU");
			break;
	}
	return result;
}