#ifndef TFO_QU_H
#define TFO_QU_H

class TFO_qu {
	int type, src1, src2, op_code, dest, imm;
	bool valid1, valid2;
	int ROB_ID;
public:
	//getters:
	int get_type() const;
	int get_dest() const;
	int get_imm() const;
	int get_opcode() const;
	int get_src1() const;
	int get_src2() const;
	int get_v1() const;
	int get_v2() const;
	int get_id() const;

	//setters:
	
	void set_type(const int) ;
	void set_dest(const int) ;
	void set_imm(const int) ;
	void set_op_code(const int) ;
	void set_src1(const int) ;
	void set_src2(const int) ;
	void set_v1(const int) ;
	void set_v2(const int) ;
	void set_id(const int) ;







	TFO_qu();				//constructor
	TFO_qu(const TFO_qu &q1);		// copy constructor
	~TFO_qu();				// destructor
};
#endif