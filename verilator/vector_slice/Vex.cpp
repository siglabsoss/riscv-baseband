#include "Vex.hpp"

#include <iostream>
using namespace std;


	Vex::Vex(){
		  for(auto i = 0; i < NREGS-1; i++)
		  {
		    this->vregs[i] = this->vector_slice->vreg[i];
		  }
		    this->srst        = 0;
		    this->clk         = 1;
		    this->t0_data     = 0;
		    this->t0_valid    = 0;
		    this->t1_data     = 0;
		    this->t2_data     = 0;
		    this->t_mem_addr  = 0;
		    this->t_mem_data  = 0;
		    this->t_mem_we    = 0;
		    this->t_mem_valid = 0;
		    this->i_mem_ready = 1;

		    this->main_time   = 0;

	}

	void Vex::initialize(VerilatedVcdC *tfp ){
		this->tfp = tfp;
	}

	bool Vex::get_ready(){
		return this->t0_ready;
	}

	void Vex::print_regs(void) {
		cout << "Vregs: " << endl;
		for(int i = 0; i < NREGS; i++) {
			cout << " " << i << ": " << HEX_STRING(vector_slice->vreg[i]) << endl;
		}
	}
	

	void Vex::print_all_regs(void)
	{
		print_regs();
		print_k_regs();
	}

	void Vex::print_k_regs(void)
	{
		cout << "Kregs: " << endl;
		cout << " " << 15 << ": " << HEX_STRING(vector_slice->k15_reg) << endl;
	}



	// sequence of op-codes to reset vregs
	void Vex::reset_regs_sequence() {
		for(int i = 0; i < NREGS; i++) {
			mv_x_v(0x0, i);
		}
	}

	void Vex::mv_x_v(uint16_t xrs1_import, int dest){

		uint16_t first_op = (OPCODE_MV_X_V << OPCODE_OP_SHIFT) | (7 << OPCODE_RS1_SHIFT) | ( dest << OPCODE_DS_SHIFT) ;

		uint64_t combined = ((uint64_t)xrs1_import << 32 ) | first_op;

		this->setter(combined);

		this->clearer();

		this->vregs[dest] = xrs1_import;


	}

	void Vex::rol(uint16_t xrs1_import, int dest){

		uint64_t combined = ((uint64_t)xrs1_import << 32 ) | (OPCODE_ROL<< OPCODE_OP_SHIFT) | ( dest << OPCODE_DS_SHIFT) ;

		this->setter(combined);

		this->clearer();

		this->vregs[dest] = this->t2_data;

	}

	void Vex::ror(uint16_t xrs1_import, int dest){
		uint64_t combined = ((uint64_t)xrs1_import << 32 ) | (OPCODE_ROR << OPCODE_OP_SHIFT) | ( dest << OPCODE_DS_SHIFT) ;

		this->setter(combined);

		this->clearer();

		this->vregs[dest] = this->t1_data;

	}


	void Vex::vadd(uint16_t xrs1_import, int dest, int src_1, int src_2){
		uint64_t combined = ((uint64_t)xrs1_import << 32 ) | (OPCODE_ADD << OPCODE_OP_SHIFT) | (src_1 << OPCODE_S1_SHIFT) | (src_2 << OPCODE_S2_SHIFT) | ( dest << OPCODE_DS_SHIFT) ;

		this->setter(combined);

		this->clearer();

		this->vregs[dest] = this->vregs[src_1]+this->vregs[src_2];

	}

	void Vex::vand(uint16_t xrs1_import, int dest, int src_1, int src_2){
		uint64_t combined = ((uint64_t)xrs1_import << 32 ) | (OPCODE_AND << OPCODE_OP_SHIFT) | (src_1 << OPCODE_S1_SHIFT) | (src_2 << OPCODE_S2_SHIFT) | ( dest << OPCODE_DS_SHIFT) ;

		this->setter(combined);

		this->clearer();

		this->vregs[dest] = this->vregs[src_1] & this->vregs[src_2];

	}

	void Vex::vor(uint16_t xrs1_import, int dest, int src_1, int src_2){
		uint64_t combined = ((uint64_t)xrs1_import << 32 ) | (OPCODE_OR << OPCODE_OP_SHIFT) | (src_1 << OPCODE_S1_SHIFT) | (src_2 << OPCODE_S2_SHIFT) | ( dest << OPCODE_DS_SHIFT) ;

		this->setter(combined);

		this->clearer();

		this->vregs[dest] = this->vregs[src_1] | this->vregs[src_2];

	}

	void Vex::vxor(uint16_t xrs1_import, int dest, int src_1, int src_2){
		uint64_t combined = ((uint64_t)xrs1_import << 32 ) | (OPCODE_XOR << OPCODE_OP_SHIFT) | (src_1 << OPCODE_S1_SHIFT) | (src_2 << OPCODE_S2_SHIFT) | ( dest << OPCODE_DS_SHIFT) ;

		this->setter(combined);

		this->clearer();

		this->vregs[dest] = this->vregs[src_1] ^ this->vregs[src_2];

	}

	void Vex::vsub(uint16_t xrs1_import, int dest, int src_1, int src_2){
		uint64_t combined = ((uint64_t)xrs1_import << 32 ) | (OPCODE_SUB << OPCODE_OP_SHIFT) | (src_1 << OPCODE_S1_SHIFT) | (src_2 << OPCODE_S2_SHIFT) | ( dest << OPCODE_DS_SHIFT) ;

		this->setter(combined);

		this->clearer();

		this->vregs[dest] = this->vregs[src_1] - this->vregs[src_2];

	}

	void Vex::mv_k15_V(uint16_t xrs1_import, int dest){
		uint64_t combined = ((uint64_t)xrs1_import << 32 ) | (OPCODE_MV_K15_V << OPCODE_OP_SHIFT) | ( dest << OPCODE_DS_SHIFT) ;

		this->setter(combined);

		this->clearer();

		this->vregs[dest] = this->k15;

	}

	void Vex::mv_V_K15(int src_2){
		uint64_t combined = ((OPCODE_MV_V_K15 << OPCODE_OP_SHIFT) | (src_2 << OPCODE_S2_SHIFT));

		this->setter(combined);

		this->clearer();

		this->k15 = this->vregs[src_2];

	}

	void Vex::mv(uint16_t xrs1_import, int dest, int src_2){
		uint64_t combined = ((uint64_t)xrs1_import << 32 ) | (OPCODE_MV << OPCODE_OP_SHIFT) | (src_2 << OPCODE_S2_SHIFT) | ( dest << OPCODE_DS_SHIFT);

		this->setter(combined);

		this->clearer();

		this->vregs[dest] = this->vregs[src_2];
	}

	void Vex::setter(uint64_t combined){
		this->t0_data = combined;
		this->t0_valid = 1;
		this->tick();
	}

	void Vex::clearer(){
		this->tick();
		this->t0_valid = 0;
	}

	uint16_t Vex::get_vexreg(int i){
		return vregs[i];
	}

	void Vex::set_left(int val){
		this->t1_data = val;
	}

	void Vex::set_right(int val){
		this->t2_data = val;
	}

	 void Vex::tick(int val){
		 for (int i=0;i<val;i++) {
			 if(this->tfp) {
				this->clk = !this->clk;
				this->tfp->dump(this->main_time);
				this->eval();
				(this->main_time)++;
			}
		 }
	  }

	 void Vex::reset(int val){
		 this->srst        = 1;
		 this->tick(2*val-1);
		 this->srst        = 0;
		 this->tick();
	 }

	 void Vex::posedge(int val){
		 this->tick(2*val);
	  }

	 bool Vex::verify(){
		if (this->test()){
		 		std::cout << "<<<Test Passed>>>\n";
		 	} else {
		 		std::cout << "<<<Test Failed>>>\n";
		 	}
	 }

	 bool Vex::test(){
		 bool rtn = true;

		 for (int i=0;i<NREGS-1;i++) {
			 if ( this->vector_slice->vreg[i] != this->vregs[i]) {
				 rtn = false;
				 std::cout << "@E[" << i << "] "<< this->vector_slice->vreg[i] << " " << this->vregs[i] << "\n";
			 }

		 }

		 if (this->vector_slice->k15_reg != this->k15){
			 rtn = false;
			 std::cout << "@E[K17] " << this->vector_slice->k15_reg << " " << this->k15 << "\n";
		 }

		 return rtn;
	 }
