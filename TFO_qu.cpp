// helper for IQueue.
#include"TFO_qu.h"

TFO_qu::TFO_qu() {
	// constructor
	type =0;
	src1=0; 
	src2=0;
	op_code=0;
	dest=0;
	imm=0;
	valid1 = valid2 = 0;
	ROB_ID = 0;
}

TFO_qu::TFO_qu(const TFO_qu &q1) {
	type = q1.type;
	src1 = q1.src1; 
	src2 = q1.src2;
	op_code = q1.op_code;
	dest = q1.dest;
	imm = q1.imm;
	valid1 = q1.valid1;
	valid2 = q1.valid2;
	ROB_ID = q1.ROB_ID; 
}

TFO_qu::~TFO_qu() {
	// destructor
}

int TFO_qu::get_type() const {
	return type;
}
int TFO_qu::get_dest() const {
	return dest;
}
int TFO_qu::get_imm() const {
	return imm;
}
int TFO_qu::get_opcode() const {
	return op_code;
}
int TFO_qu::get_src1() const {
	return src1;
}
int TFO_qu::get_src2() const {
	return src2;
}
int TFO_qu::get_v1() const {
	return valid1;
}
int TFO_qu::get_v2() const {
	return valid2; 
}
int TFO_qu::get_id() const {
	return ROB_ID;
}

void TFO_qu::set_type(const int t)  {
	type = t;
}
void TFO_qu::set_dest(const int destination)  {
	dest = destination;
}
void TFO_qu::set_imm(const int immed)  {
	imm = immed;
}
void TFO_qu::set_op_code(const int code) {
	op_code = code;
}

void TFO_qu::set_src1(const int s1) {
	src1 = s1;
}
void TFO_qu::set_src2(const int s2) {
	src2 = s2;
}
void TFO_qu::set_v1(const int v1)  {
	valid1 = v1;
}
void TFO_qu::set_v2(const int v2) {
	valid2 = v2;
}
void TFO_qu::set_id(const int id) {
	ROB_ID = id;
}
