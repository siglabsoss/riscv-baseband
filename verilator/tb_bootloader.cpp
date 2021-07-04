#include "Vq_engine.h"
#include "Vq_engine__Syms.h"
// #include "Vriscv_baseband_generic_dpram__Ad_D2000.h"
#ifdef REF
#include "VVexRiscv_RiscvCore.h"
#endif
#include "verilated.h"
#include "verilated_vcd_c.h"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <stdint.h>
#include <cstring>
#include <string.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <mutex>
#include <iomanip>
#include <algorithm>
#include <time.h>

// include files from specific test
#include "inband_signal.h"

// include shared tb files
#include "read_hexfile.hpp"

using namespace std;

#define HEX_STRING(n) std::hex << (n) << std::dec


#define THREAD_COUNT 1
#define BOOT_HEX_LEN (44)
// #define ISA_TEST
// #define REDO (10)

#undef IBUS_SIMPLE
#undef DBUS_SIMPLE

#define RESET srst

typedef Vq_engine top_t;


#define MEM_BANK_0 top->q_engine->mem->mem0
#define MEM_BANK_1 top->q_engine->mem->mem1
#define MEM_BANK_2 top->q_engine->mem->mem2
#define MEM_BANK_3 top->q_engine->mem->mem3

struct timespec timer_get(){
    struct timespec start_time;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start_time);
    return start_time;
}

class Memory{
public:
	uint8_t* mem[1 << 12];

	Memory(){
		for(uint32_t i = 0;i < (1 << 12);i++) mem[i] = NULL;
	}
	~Memory(){
		for(uint32_t i = 0;i < (1 << 12);i++) if(mem[i]) delete mem[i];
	}

	uint8_t* get(uint32_t address){
		if(mem[address >> 20] == NULL) {
			uint8_t* ptr = new uint8_t[1024*1024];
			for(uint32_t i = 0;i < 1024*1024;i+=4) {
				ptr[i + 0] = 0xFF;
				ptr[i + 1] = 0xFF;
				ptr[i + 2] = 0xFF;
				ptr[i + 3] = 0xFF;
			}
			mem[address >> 20] = ptr;
		}
		return &mem[address >> 20][address & 0xFFFFF];
	}

	uint8_t& operator [](uint32_t address) {
		return *get(address);
	}

	/*T operator [](uint32_t address) const {
		return get(address);
	}*/
};

//uint8_t memory[1024 * 1024];

uint32_t hti(char c) {
	if (c >= 'A' && c <= 'F')
		return c - 'A' + 10;
	if (c >= 'a' && c <= 'f')
		return c - 'a' + 10;
	return c - '0';
}

uint32_t hToI(char *c, uint32_t size) {
	uint32_t value = 0;
	for (uint32_t i = 0; i < size; i++) {
		value += hti(c[i]) << ((size - i - 1) * 4);
	}
	return value;
}

void loadHexImpl(string path,Memory* mem) {
	FILE *fp = fopen(&path[0], "r");
	if(fp == 0){
		cout << path << " not found" << endl;
	}
	fseek(fp, 0, SEEK_END);
	uint32_t size = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	char* content = new char[size];
	fread(content, 1, size, fp);

	int offset = 0;
	char* line = content;
	while (1) {
		if (line[0] == ':') {
			uint32_t byteCount = hToI(line + 1, 2);
			uint32_t nextAddr = hToI(line + 3, 4) + offset;
			uint32_t key = hToI(line + 7, 2);
			// printf("%d %d %d\n", byteCount, nextAddr,key);
			switch (key) {
			case 0:
				for (uint32_t i = 0; i < byteCount; i++) {
					*(mem->get(nextAddr + i)) = hToI(line + 9 + i * 2, 2);
					// printf("  %x %x %c%c\n",nextAddr + i,hToI(line + 9 + i*2,2),line[9 + i * 2],line[9 + i * 2+1]);
				}
				break;
			case 2:
//				cout << offset << endl;
				offset = hToI(line + 9, 4) << 4;
				break;
			case 4:
//				cout << offset << endl;
				offset = hToI(line + 9, 4) << 16;
				break;
			default:
//				cout << "??? " << key << endl;
				break;
			}
		}

		while (*line != '\n' && size != 0) {
			line++;
			size--;
		}
		if (size <= 1)
			break;
		line++;
		size--;
	}

	delete content;
}



#define TEXTIFY(A) #A

#define assertEq(x,ref) if(x != ref) {\
	printf("\n*** %s is %d but should be %d ***\n\n",TEXTIFY(x),x,ref);\
	throw std::exception();\
}

class success : public std::exception { };





class SimElement{
public:
	virtual ~SimElement(){}
	virtual void onReset(){}
	virtual void postReset(){}
	virtual void preCycle(){}
	virtual void postCycle(){}
};




class Workspace{
public:
	static mutex staticMutex;
	static uint32_t testsCounter, successCounter;
	static uint64_t cycles;
	uint64_t instanceCycles = 0;
	vector<SimElement*> simElements;
	Memory mem;
	string name;
	uint64_t currentTime = 22;
	uint64_t mTimeCmp = 0;
	uint64_t mTime = 0;
	top_t* top;
	bool resetDone = false;
	uint64_t i;
	double cyclesPerSecond = 10e6;
	double allowedCycles = 0.0;
	uint32_t bootPc = -1;
	uint32_t iStall = 1,dStall = 1;
	#ifdef TRACE
	VerilatedVcdC* tfp;
	#endif

	bool withInstructionReadCheck = true;
	void setIStall(bool enable) { iStall = enable; }
	void setDStall(bool enable) { dStall = enable; }

	ofstream regTraces;
	ofstream memTraces;
	ofstream logTraces;

	struct timespec start_time;


	Workspace(string name){
		staticMutex.lock();
		testsCounter++;
		staticMutex.unlock();
		this->name = name;
		top = new top_t;
		#ifdef TRACE_ACCESS
			regTraces.open (name + ".regTrace");
			memTraces.open (name + ".memTrace");
		#endif
		logTraces.open (name + ".logTrace");
		fillSimELements();
		clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start_time);
	}

	virtual ~Workspace(){
		delete top;
		#ifdef TRACE
		delete tfp;
		#endif

		for(SimElement* simElement : simElements) {
			delete simElement;
		}
	}

	Workspace* loadHex(string path){
		loadHexImpl(path,&mem);
		return this;
	}

	Workspace* setCyclesPerSecond(double value){
		cyclesPerSecond = value;
		return this;
	}

    Workspace* bootAt(uint32_t pc) { bootPc = pc;}


	virtual void iBusAccess(uint32_t addr, uint32_t *data, bool *error) {
#ifdef USE_CPP_IMEM
		if(addr % 4 != 0) {
			cout << "Warning, unaligned IBusAccess : " << addr << endl;
		//	fail();
		}


		*data =     (  (mem[addr + 0] << 0)
					 | (mem[addr + 1] << 8)
					 | (mem[addr + 2] << 16)
					 | (mem[addr + 3] << 24));

		cout << "iBusAccess " << (void*) addr << ":" << (void*) *data << endl;

		*error = addr == 0xF00FFF60u;
#endif
	}
	virtual void dBusAccess(uint32_t addr,bool wr, uint32_t size,uint32_t mask, uint32_t *data, bool *error) {
		assertEq(addr % (1 << size), 0);
		*error = addr == 0xF00FFF60u;
		if(wr){
			memTraces <<
			#ifdef TRACE_WITH_TIME
			(currentTime
			#ifdef REF
			-2
			 #endif
			 ) <<
			 #endif
			 " : WRITE mem" << (1 << size) << "[" << addr << "] = " << *data << endl;
			for(uint32_t b = 0;b < (1 << size);b++){
				uint32_t offset = (addr+b)&0x3;
				if((mask >> offset) & 1 == 1)
					*mem.get(addr + b) = *data >> (offset*8);
			}

			switch(addr){
			case 0xF0010000u: {
				cout << mem[0xF0010000u];
				logTraces << (char)mem[0xF0010000u];
				break;
			}
			case 0xF00FFF00u: {
				cout << mem[0xF00FFF00u];
				logTraces << (char)mem[0xF00FFF00u];
				break;
			}
			#ifndef DEBUG_PLUGIN_EXTERNAL
			case 0xF00FFF20u:
				if(*data == 0)
					pass();
				else
					fail();
				break;
			case 0xF00FFF24u:
					cout << "TEST ERROR CODE " << *data << endl;
					fail();
				break;
			#endif
			case 0xF00FFF48u: mTimeCmp = (mTimeCmp & 0xFFFFFFFF00000000) | *data;break;
			case 0xF00FFF4Cu: mTimeCmp = (mTimeCmp & 0x00000000FFFFFFFF) | (((uint64_t)*data) << 32);  /*cout << "mTimeCmp <= " << mTimeCmp << endl; */break;
			}
		}else{
			*data = VL_RANDOM_I(32);
			for(uint32_t b = 0;b < (1 << size);b++){
				uint32_t offset = (addr+b)&0x3;
				*data &= ~(0xFF << (offset*8));
				*data |= mem[addr + b] << (offset*8);
			}
			switch(addr){
			case 0xF00FFF10u:
				*data = mTime;
				#ifdef REF_TIME
				mTime += 100000;
				#endif
				break;
			case 0xF00FFF40u: *data = mTime;		  break;
			case 0xF00FFF44u: *data = mTime >> 32;    break;
			case 0xF00FFF48u: *data = mTimeCmp;       break;
			case 0xF00FFF4Cu: *data = mTimeCmp >> 32; break;
			case 0xF0010004u: *data = ~0;		      break;
			}
			memTraces <<
			#ifdef TRACE_WITH_TIME
			(currentTime
			#ifdef REF
			-2
			 #endif
			 ) <<
			 #endif
			  " : READ  mem" << (1 << size) << "[" << addr << "] = " << *data << endl;

		}
	}
	virtual void postReset() {}
	virtual void checks(){}
	virtual void checks_posedge(){}
	virtual void pass(){ throw success();}
	virtual void fail(){ throw std::exception();}
    virtual void fillSimELements();
    Workspace* noInstructionReadCheck(){withInstructionReadCheck = false; return this;}
	void dump(int i){
		#ifdef TRACE
		if(i/2 >= TRACE_START) tfp->dump(i);
		#endif
	}
	Workspace* run(uint64_t timeout = 5000){
//		cout << "Start " << name << endl;

		currentTime = 4;
		// init trace dump
		#ifdef TRACE
		Verilated::traceEverOn(true);
		tfp = new VerilatedVcdC;
		top->trace(tfp, 99);
		tfp->open((string(name)+ ".vcd").c_str());
		#endif

		// Reset
		top->clk = 0;
		top->RESET = 0;


		top->eval(); currentTime = 3;
		for(SimElement* simElement : simElements) simElement->onReset();

		top->RESET = 1;
		top->eval();
		#ifdef CSR
		top->timerInterrupt = 0;
		top->externalInterrupt = 1;
		#endif
		#ifdef DEBUG_PLUGIN_EXTERNAL
		top->timerInterrupt = 0;
		top->externalInterrupt = 0;
		#endif
		dump(0);
		top->RESET = 0;
		for(SimElement* simElement : simElements) simElement->postReset();

		top->eval(); currentTime = 2;


		postReset();

		resetDone = true;

		// #ifdef  REF
		// if(bootPc != -1) VEX_TOP->core->prefetch_pc = bootPc;
		// #else
		// if(bootPc != -1) VEX_TOP->prefetch_PcManagerSimplePlugin_pcReg = bootPc;
		// #endif


		try {
			// run simulation for 100 clock periods
			for (i = 16; i < timeout*2; i+=2) {
				while(allowedCycles <= 0.0){
					struct timespec end_time;
					clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end_time);
					uint64_t diffInNanos = end_time.tv_sec*1e9 + end_time.tv_nsec -  start_time.tv_sec*1e9 - start_time.tv_nsec;
					start_time = end_time;
					double dt = diffInNanos*1e-9;
					allowedCycles += dt*cyclesPerSecond;
					if(allowedCycles > cyclesPerSecond/100) allowedCycles = cyclesPerSecond/100;
				}
				allowedCycles-=1.0;


				#ifndef REF_TIME
				mTime = i/2;
				#endif
				#ifdef CSR
				top->timerInterrupt = mTime >= mTimeCmp ? 1 : 0;
				//if(mTime == mTimeCmp) printf("SIM timer tick\n");
				#endif

				currentTime = i;




				// dump variables into VCD file and toggle clock

				dump(i);
				//top->eval();
				top->clk = 0;
				top->eval();


				dump(i + 1);



				// if(VEX_TOP->writeBack_RegFilePlugin_regFileWrite_valid == 1 && VEX_TOP->writeBack_RegFilePlugin_regFileWrite_payload_address != 0){
				// 	regTraces <<
				// 		#ifdef TRACE_WITH_TIME
				// 		currentTime <<
				// 		 #endif
				// 		 " PC " << hex << setw(8) <<  VEX_TOP->writeBack_PC << " : reg[" << dec << setw(2) << (uint32_t)VEX_TOP->writeBack_RegFilePlugin_regFileWrite_payload_address << "] = " << hex << setw(8) << VEX_TOP->writeBack_RegFilePlugin_regFileWrite_payload_data << endl;
				// }

				for(SimElement* simElement : simElements) simElement->preCycle();

				// if(withInstructionReadCheck){
				// 	if(VEX_TOP->decode_arbitration_isValid && !VEX_TOP->decode_arbitration_haltItself){
				// 		uint32_t expectedData;
				// 		bool dummy;
				// 		iBusAccess(VEX_TOP->decode_PC, &expectedData, &dummy);
				// 		assertEq(VEX_TOP->decode_INSTRUCTION,expectedData);
				// 	}
				// }

				checks();
				//top->eval();
				top->clk = 1;
				top->eval();
				checks_posedge();
				instanceCycles += 1;

				for(SimElement* simElement : simElements) simElement->postCycle();



				if (Verilated::gotFinish())
					exit(0);
			}
			cout << "timeout" << endl;
			fail();
		} catch (const success e) {
			staticMutex.lock();
			cout <<"SUCCESS " << name <<  endl;
			successCounter++;
			cycles += instanceCycles;
			staticMutex.unlock();
		} catch (const std::exception& e) {
			staticMutex.lock();
			cout << "FAIL " <<  name << endl;
			cycles += instanceCycles;
			staticMutex.unlock();
		}

		// top->riscv_baseband->q_engine->mem;

		// currently we have two dedicated pass/fail variables, 32 bits each
		// if the ld file MEMORY section changes, these may change 
		uint32_t pf0 = (0x7ff8) / 4;
		uint32_t pf1 = (0x7ffc) / 4;

		uint32_t pass_fail_0 = (MEM_BANK_3[pf0]<<24) |
						   (MEM_BANK_2[pf0]<<16) |
						   (MEM_BANK_1[pf0]<< 8) | MEM_BANK_0[pf0];

		uint32_t pass_fail_1 = (MEM_BANK_3[pf1]<<24) |
						   (MEM_BANK_2[pf1]<<16) |
						   (MEM_BANK_1[pf1]<< 8) | MEM_BANK_0[pf1];

		cout << "Test Value: 0x" <<  HEX_STRING(pass_fail_0) << endl;

		dump(i);
		dump(i+10);
		#ifdef TRACE
		tfp->close();
		#endif
		return this;
	}
};



#ifdef IBUS_SIMPLE
class IBusSimple : public SimElement{
public:
	uint32_t inst_next = VL_RANDOM_I(32);
	bool error_next = false;
	bool pending = false;

	Workspace *ws;
	top_t* top;
	IBusSimple(Workspace* ws){
		this->ws = ws;
		this->top = ws->top;
	}

	virtual void onReset(){
		top->iBus_cmd_ready = 1;
		top->iBus_rsp_ready = 1;
	}

	virtual void preCycle(){
		if (top->iBus_cmd_valid && top->iBus_cmd_ready && !pending) {
			//assertEq(top->iBus_cmd_payload_pc & 3,0);
			pending = true;
			ws->iBusAccess(top->iBus_cmd_payload_pc,&inst_next,&error_next);
		}
	}
	//TODO doesn't catch when instruction removed ?
	virtual void postCycle(){
		top->iBus_rsp_ready = !pending;
		if(pending && (!ws->iStall || VL_RANDOM_I(7) < 100)){
			top->iBus_rsp_inst = inst_next;
			pending = false;
			top->iBus_rsp_ready = 1;
			top->iBus_rsp_error = error_next;
		}
		if(ws->iStall) top->iBus_cmd_ready = VL_RANDOM_I(7) < 100 && !pending;
	}
};
#endif




#ifdef DBUS_SIMPLE
class DBusSimple : public SimElement{
public:
	uint32_t data_next = VL_RANDOM_I(32);
	bool error_next = false;
	bool pending = false;

	Workspace *ws;
	top_t* top;
	DBusSimple(Workspace* ws){
		this->ws = ws;
		this->top = ws->top;
	}

	virtual void onReset(){
		top->dBus_cmd_ready = 1;
		top->dBus_rsp_ready = 1;
	}

	virtual void preCycle(){
		if (top->dBus_cmd_valid && top->dBus_cmd_ready) {
			pending = true;
			data_next = top->dBus_cmd_payload_data;
			ws->dBusAccess(top->dBus_cmd_payload_address,top->dBus_cmd_payload_wr,top->dBus_cmd_payload_size,0xF,&data_next,&error_next);
		}
	}

	virtual void postCycle(){
		top->dBus_rsp_ready = 0;
		if(pending && (!ws->dStall || VL_RANDOM_I(7) < 100)){
			pending = false;
			top->dBus_rsp_ready = 1;
			top->dBus_rsp_data = data_next;
			top->dBus_rsp_error = error_next;
		} else{
			top->dBus_rsp_data = VL_RANDOM_I(32);
		}

		if(ws->dStall) top->dBus_cmd_ready = VL_RANDOM_I(7) < 100 && !pending;
	}
};
#endif


#ifdef DEBUG_PLUGIN
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <netinet/tcp.h>

/** Returns true on success, or false if there was an error */
bool SetSocketBlockingEnabled(int fd, bool blocking)
{
   if (fd < 0) return false;

#ifdef WIN32
   unsigned long mode = blocking ? 0 : 1;
   return (ioctlsocket(fd, FIONBIO, &mode) == 0) ? true : false;
#else
   int flags = fcntl(fd, F_GETFL, 0);
   if (flags < 0) return false;
   flags = blocking ? (flags&~O_NONBLOCK) : (flags|O_NONBLOCK);
   return (fcntl(fd, F_SETFL, flags) == 0) ? true : false;
#endif
}

struct DebugPluginTask{
	bool wr;
	uint32_t address;
	uint32_t data;
};

class DebugPlugin : public SimElement{
public:
	Workspace *ws;
	top_t* top;

	int serverSocket, clientHandle;
	struct sockaddr_in serverAddr;
	struct sockaddr_storage serverStorage;
	socklen_t addr_size;
	char buffer[1024];
	uint32_t timeSpacer = 0;
	bool taskValid = false;
	DebugPluginTask task;


	DebugPlugin(Workspace* ws){
		this->ws = ws;
		this->top = ws->top;

		#ifdef DEBUG_PLUGIN_EXTERNAL
			ws->mTimeCmp = ~0;
		#endif
		top->debugReset = 0;



		//---- Create the socket. The three arguments are: ----//
		// 1) Internet domain 2) Stream socket 3) Default protocol (TCP in this case) //
		serverSocket = socket(PF_INET, SOCK_STREAM, 0);
		assert(serverSocket != -1);
		SetSocketBlockingEnabled(serverSocket,0);
		int flag = 1;
		int result = setsockopt(serverSocket,            /* socket affected */
								 IPPROTO_TCP,     /* set option at TCP level */
								 TCP_NODELAY,     /* name of option */
								 (char *) &flag,  /* the cast is historical
														 cruft */
								 sizeof(int));    /* length of option value */

		//---- Configure settings of the server address struct ----//
		// Address family = Internet //
		serverAddr.sin_family = AF_INET;
		// Set port number, using htons function to use proper byte order //
		serverAddr.sin_port = htons(7893);
		// Set IP address to localhost //
		serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
		// Set all bits of the padding field to 0 //
		memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

		//---- Bind the address struct to the socket ----//
		bind(serverSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

		//---- Listen on the socket, with 5 max connection requests queued ----//
		listen(serverSocket,1);

		//---- Accept call creates a new socket for the incoming connection ----//
		addr_size = sizeof serverStorage;

		clientHandle = -1;
	}

	virtual ~DebugPlugin(){
		if(clientHandle != -1) {
			shutdown(clientHandle,SHUT_RDWR);
			usleep(100);
		}
		if(serverSocket != -1) {
			close(serverSocket);
			usleep(100);
		}
	}

	virtual void onReset(){
		top->debugReset = 1;
	}



	virtual void postReset(){
		top->debugReset = 0;
	}

	void connectionReset(){
		printf("CONNECTION RESET\n");
		shutdown(clientHandle,SHUT_RDWR);
		clientHandle = -1;
	}


	virtual void preCycle(){

	}

	virtual void postCycle(){
		top->RESET = top->debug_resetOut;
		if(timeSpacer == 0){
			if(clientHandle == -1){
				clientHandle = accept(serverSocket, (struct sockaddr *) &serverStorage, &addr_size);
				if(clientHandle != -1)
					printf("CONNECTED\n");
				timeSpacer = 1000;
			}


			if(clientHandle != -1 && taskValid == false){
				int requiredSize = 1 + 1 + 4 + 4;
				int n;
				timeSpacer = 20;
				if(ioctl(clientHandle,FIONREAD,&n) != 0){
					connectionReset();
				} else if(n >= requiredSize){
					if(requiredSize != read(clientHandle,buffer,requiredSize)){
						connectionReset();
					} else {
						bool wr = buffer[0];
						uint32_t size = buffer[1];
						uint32_t address = *((uint32_t*)(buffer + 2));
						uint32_t data = *((uint32_t*)(buffer + 6));

						if((address & ~ 0x4) == 0xF00F0000){
							assert(size == 2);
							timeSpacer = 100;

							taskValid = true;
							task.wr = wr;
							task.address = address;
							task.data = data;
						}
					}
				} else {
					int error = 0;
					socklen_t len = sizeof (error);
					int retval = getsockopt (clientHandle, SOL_SOCKET, SO_ERROR, &error, &len);
					if (retval != 0 || error != 0) {
						connectionReset();
					}
				}
			}
		} else {
			timeSpacer--;
		}
	}

	void sendRsp(uint32_t data){
		if(clientHandle != -1){
			if(send(clientHandle,&data,4,0) == -1) connectionReset();
		}
	}
};
#endif

#ifdef DEBUG_PLUGIN_STD
class DebugPluginStd : public DebugPlugin{
public:
	DebugPluginStd(Workspace* ws) : DebugPlugin(ws){

	}

	virtual void onReset(){
		DebugPlugin::onReset();
		top->debug_bus_cmd_valid = 0;
	}

	bool rspFire = false;

	virtual void preCycle(){
		DebugPlugin::preCycle();

		if(rspFire){
			sendRsp(top->debug_bus_rsp_data);
			rspFire = false;
		}

		if(top->debug_bus_cmd_valid && top->debug_bus_cmd_ready){
			taskValid = false;
			if(!top->debug_bus_cmd_payload_wr){
				rspFire = true;
			}
		}
	}

	virtual void postCycle(){
		DebugPlugin::postCycle();

		if(taskValid){
			top->debug_bus_cmd_valid = 1;
			top->debug_bus_cmd_payload_wr = task.wr;
			top->debug_bus_cmd_payload_address = task.address;
			top->debug_bus_cmd_payload_data = task.data;
		}else {
			top->debug_bus_cmd_valid = 0;
			top->debug_bus_cmd_payload_wr = VL_RANDOM_I(1);
			top->debug_bus_cmd_payload_address = VL_RANDOM_I(8);
			top->debug_bus_cmd_payload_data = VL_RANDOM_I(32);
		}
	}
};

#endif

#ifdef DEBUG_PLUGIN_AVALON
class DebugPluginAvalon : public DebugPlugin{
public:
	DebugPluginAvalon(Workspace* ws) : DebugPlugin(ws){

	}

	virtual void onReset(){
		DebugPlugin::onReset();
		top->debugBusAvalon_read = 0;
		top->debugBusAvalon_write = 0;
	}

	bool rspFire = false;

	virtual void preCycle(){
		DebugPlugin::preCycle();

		if(rspFire){
			sendRsp(top->debugBusAvalon_readData);
			rspFire = false;
		}

		if((top->debugBusAvalon_read || top->debugBusAvalon_write) && top->debugBusAvalon_waitRequestn){
			taskValid = false;
			if(top->debugBusAvalon_read){
				rspFire = true;
			}
		}
	}

	virtual void postCycle(){
		DebugPlugin::postCycle();

		if(taskValid){
			top->debugBusAvalon_write = task.wr;
			top->debugBusAvalon_read = !task.wr;
			top->debugBusAvalon_address = task.address;
			top->debugBusAvalon_writeData = task.data;
		}else {
			top->debugBusAvalon_write = 0;
			top->debugBusAvalon_read = 0;
			top->debugBusAvalon_address = VL_RANDOM_I(8);
			top->debugBusAvalon_writeData = VL_RANDOM_I(32);
		}
	}
};

#endif

void Workspace::fillSimELements(){
	#ifdef IBUS_SIMPLE
		simElements.push_back(new IBusSimple(this));
	#endif
	#ifdef IBUS_SIMPLE_AVALON
		simElements.push_back(new IBusSimpleAvalon(this));
	#endif
	#ifdef IBUS_CACHED
		simElements.push_back(new IBusCached(this));
	#endif
	#ifdef IBUS_CACHED_AVALON
		simElements.push_back(new IBusCachedAvalon(this));
	#endif
	#ifdef DBUS_SIMPLE
		simElements.push_back(new DBusSimple(this));
	#endif
	#ifdef DBUS_SIMPLE_AVALON
		simElements.push_back(new DBusSimpleAvalon(this));
	#endif
	#ifdef DBUS_CACHED
		simElements.push_back(new DBusCached(this));
	#endif
	#ifdef DBUS_CACHED_AVALON
		simElements.push_back(new DBusCachedAvalon(this));
	#endif
	#ifdef DEBUG_PLUGIN_STD
		simElements.push_back(new DebugPluginStd(this));
	#endif
	#ifdef DEBUG_PLUGIN_AVALON
		simElements.push_back(new DebugPluginAvalon(this));
	#endif
}

mutex Workspace::staticMutex;
uint64_t Workspace::cycles = 0;
uint32_t Workspace::testsCounter = 0, Workspace::successCounter = 0;

#ifndef REF
#define testA1ReagFileWriteRef {1,10},{2,20},{3,40},{4,60}
#define testA2ReagFileWriteRef {5,1},{7,3}
uint32_t regFileWriteRefArray[][2] = {
	testA1ReagFileWriteRef,
	testA1ReagFileWriteRef,
	testA2ReagFileWriteRef,
	testA2ReagFileWriteRef
};


// change these if ld script changes

#define IMEM_LEN 0x6c00
#define DMEM_LEN 0x1000
#define BOOT_LEN 0x03f8
#define PASS_FAIL_LEN 0x0008

#define MEM_WORD(x) (MEM_BANK_3[x]<<24) | (MEM_BANK_2[x]<<16) | (MEM_BANK_1[x]<< 8) | MEM_BANK_0[x]

class TestControl : public Workspace{
public:


	uint32_t regFileWriteRefIndex = 0;
	uint32_t dma_input;

	uint32_t prev_ready;
	uint32_t ready;

	std::vector<uint32_t> input_stream;

	uint32_t start_after;
	uint32_t start_second_bootload;

	uint32_t pf0 = (0x7ff8) / 4;
	uint32_t pf1 = (0x7ffc) / 4;

	uint32_t pass_fail_1, pass_fail_1_prev;
	uint32_t pass_fail_0, pass_fail_0_prev;

	uint32_t udp_max_len = 1024;
	uint32_t header_len = INBAND_T_SIZE_BYTES;

	void dump_memory(uint32_t start, uint32_t end) {
		for(uint32_t i = start; i < end; i++) {
			if((i)%16 == 0) {
				cout << endl;
			}
			cout << setfill('0') << setw(8) << HEX_STRING(MEM_WORD(i)) << ", ";
		}
		cout << endl;
	}

	void get_pf() {
		pass_fail_1 = (MEM_BANK_3[pf1]<<24) |
						   (MEM_BANK_2[pf1]<<16) |
						   (MEM_BANK_1[pf1]<< 8) | MEM_BANK_0[pf1];

		pass_fail_0 = (MEM_BANK_3[pf0]<<24) |
						   (MEM_BANK_2[pf0]<<16) |
						   (MEM_BANK_1[pf0]<< 8) | MEM_BANK_0[pf0];
	}

	void handle_print0() {
		if(pass_fail_0 != pass_fail_0_prev)
		{
			// inband signal
			if(pass_fail_0 != 0xdeadbeef) {
				char buf[5];
				cout << "hex: 0x" << HEX_STRING(pass_fail_0) << " ( printed at " << i << " )" << endl;
			}
			pass_fail_0_prev = pass_fail_0;
		}
	}

	void handle_print() {
		if(pass_fail_1 != pass_fail_1_prev)
		{
			if(pass_fail_1 != 0) {
				char buf[5];

				// cout << "0x" << HEX_STRING(pass_fail_1) << " ";

				buf[0] = pass_fail_1 & 0xff;
				buf[1] = (pass_fail_1>>8) & 0xff;
				buf[2] = (pass_fail_1>>16) & 0xff;
				buf[3] = (pass_fail_1>>24) & 0xff;
				buf[4] = 0; // null


				for(auto i = 0; i <= 0; i++)
				{
					if(buf[i] == '\0')
					{
						for(auto j = i+1; j < 4; j++) {
							buf[j] = '\0';
						}
					}

				}

				bool flag = false;
				for(auto i = 0; i < 4; i++)
				{
					if(buf[i] == '\n')
					{
						buf[i] = ' ';
						flag = true;
					}
				}

				cout << buf;

				if(flag) {
					cout << "( printed at " << i << " )" << endl;
				}
				

				// cout << "0x" << HEX_STRING(pass_fail_1) << endl;
			}
			pass_fail_1_prev = pass_fail_1;
		}
	}

	void append_inband_header(std::vector<uint32_t> &stream, inband_t* header) {
		uint32_t *a;
		uint32_t *b;

		uint32_t size = sizeof(inband_t) / 4;

		a = (uint32_t*)header;

		for(auto i = 0; i < size; i++)
		{
			// stream.push(a[i]);
			stream.insert(stream.begin(), a[i]);
			// cout << "pushing: " << HEX_STRING(a[i]) << endl;
		}
	}

	void bootload_file(std::vector<uint32_t> &stream, std::string filename) {
		
		std::vector<uint8_t> file_contents; // 8 bit vector of bootloader
		std::vector<uint32_t> file_wide;    // 32 bit vector of bootloader
		int hack = 0;

		// read entire file as byte vector
		get_hexfile_as_uint8_t(file_contents, filename);


		// ready to resize to multiple of 4
		uint32_t sz = file_contents.size();
		uint32_t rem = (sz % 4);
		if(rem != 0)
		{
			cout << "adding " << (4-rem) << " bytes at the end." << endl;
			file_contents.resize(sz+(4-rem), 0);
			sz = file_contents.size(); // grab new size
		}

		file_wide.resize(sz/4, 0);

		for(auto i = 0; i < file_contents.size(); i+=4) {
			// cout << "i " << i << " with value: 0x" << HEX_STRING(file_contents[i]) << endl;
			file_wide[i/4] = file_contents[i] | (file_contents[i+1]<<8) | (file_contents[i+2]<<16) | (file_contents[i+3]<<24);
		}

		// remove ALL memory starting from the boot loader, and past
		file_wide.resize( ((IMEM_LEN + DMEM_LEN)/4) );

		

		// loop through backwards, looking for a non-zero address
		for(auto i = file_wide.size()-1; i > 0; i--) {
			// cout << "i " << i << " with value: 0x" << HEX_STRING(file_wide[i]) << endl;
			if(file_wide[i] != 0) {
				cout << "break at i " << i << endl;
				file_wide.resize(i+1);
				break;
			}
		}

		uint32_t sizew = file_wide.size();
		uint32_t total_bytes = sizew*4;

		uint32_t rf_packet_id = 0xb00d100d; // fixme randomize
		uint32_t packet_countdown;

		// how many bytes do we have for payload
		uint32_t payload_bytes = udp_max_len-header_len;

		inband_t d;
		memset(&d, 0, sizeof(inband_t));

		d.type = INBAND_TYPE_BOOTLOAD_DATA;
		d.read = 0;
		d.rf_packet_id = rf_packet_id;
		d.rf_packet_size = sizew;

		uint32_t total_packets;


		uint32_t bytes_sent = 0;

		total_packets = (total_bytes / payload_bytes);

		if((total_bytes % payload_bytes) != 0)
		{
			total_packets++;
		}

		bool verbose = true;

		if(verbose) {
			cout << "will send " << total_packets << " packets" << endl;
		}

		uint32_t data_payload_size;
		for(auto i = 0; i < total_packets; i++) {
			packet_countdown = (total_packets-1) - i;
			d.packet_countdown = packet_countdown;
			data_payload_size = min(payload_bytes, total_bytes - bytes_sent);
			d.udp_packet_size = header_len + data_payload_size;

			if(verbose) {
				cout << "data_payload_size: " << data_payload_size << endl;
				cout << "packet i " << i << endl;
				PRINT_INBAND_T(d);
			}


			append_inband_header(stream, &d);

			for(auto j = 0; j < data_payload_size/4; j++)
			{
				uint32_t calc = j + (bytes_sent/4);
				stream.insert(stream.begin(), file_wide[calc]);
				if(verbose) {
					// cout << calc << ", ";
					cout << HEX_STRING(file_wide[calc]) << ", ";
				}
			}

			if(verbose) {
				cout << endl;
			}

			bytes_sent += data_payload_size;
		}




		// for(auto i = 0; i < file_wide.size(); i++) {
		// 	cout << "i 0x" << HEX_STRING(i*4) << " with value: 0x" << HEX_STRING(file_wide[i]) << endl;
		// }


		// for(auto i = 0; i < file_wide.size(); i++) {

		// 	if(i == ((IMEM_LEN + DMEM_LEN+4)/4))
		// 	{
		// 		cout << "------------------------" << endl;
		// 	}

		// 	cout << "i " << i << " with value: 0x" << HEX_STRING(file_wide[i]) << endl;
		// }


		// for(auto i = 0; i < file_contents.size(); i++) {
		// 	cout << "i " << i << " with value: 0x" << HEX_STRING(file_contents[i]) << endl;
		// }
	}

	void control_write(std::vector<uint32_t> &stream, uint32_t addr, uint32_t data) {
		inband_t d;
		memset(&d, 0, sizeof(inband_t));
		d.type = INBAND_TYPE_CONTROL;
		d.read = 0;
		d.addr = addr;
		d.data = data;



		// d.type = 2;
		// d.read = 3;
		// d.addr = 4;
		// d.data = 5;

		// cout << "control write: 0x" << HEX_STRING( addr ) << " 0x" << HEX_STRING(data ) << endl;

		append_inband_header(stream, &d);
	}

	TestControl() : Workspace("testFirst") {

		withInstructionReadCheck = false;

		dma_input = 0x0f0f0000;

		// clock edge
		start_after = 300;

		// when to load the 2nd file
		start_second_bootload = 540000;

		setup_stream();

	}


	void setup_stream() {

		// control_write(input_stream, 0, 0xdeadbeef);
		// control_write(input_stream, 4, 0xcafebabe);
		// control_write(input_stream, 8, 0xfeefd00d);

		// must trigger this bootloader before sending bootloader packets
		control_write(input_stream, 0x10000, 0); // write anything
		bootload_file(input_stream, "c/bootloader_example/canned_hex/can2.hex");
	}

	virtual void checks() {
		get_pf(); // each loop
		handle_print0();
		handle_print();


		if( i >= start_after ) {
			if( input_stream.size() )
			{
				top->t0_data = input_stream.back();
				top->t0_valid = 1;
				// cout << "presenting: " << top->t0_data << endl;
			} else {
				top->t0_valid = 0;
			}


			// if(pass_fail_1 != 0)
			// {
			// 	cout << HEX_STRING( pass_fail_1 ) << endl;
			// }
		}

		if(i == start_second_bootload) {
			control_write(input_stream, 0x10000, 0); // write anything
			bootload_file(input_stream, "c/bootloader_example/canned_hex/can3.hex");
		}

		if( i == 100000 ) {
			// dump_memory(0, 0x8000>>2);
		}


	}

	// due to how valid /ready works
	// we added this checks_posedge which runs after the clock goes posedge
	virtual void checks_posedge(){
		
		if( i >= start_after ) {
			if( input_stream.size() ) {
				if(top->t0_ready) {
					// dma_input++;
					// cout << "consumed: " << HEX_STRING(input_stream.back()) << endl;

					input_stream.pop_back();
				}
			}
		}
	}
};




#endif
class Dhrystone : public Workspace{
public:
	string hexName;
	Dhrystone(string name,string hexName,bool iStall, bool dStall) : Workspace(name) {
		setIStall(iStall);
		setDStall(dStall);
		loadHex("../../resources/hex/" + hexName + ".hex");
		this->hexName = hexName;
	}

	virtual void checks(){

	}

	virtual void pass(){
		FILE *refFile = fopen((hexName + ".logRef").c_str(), "r");
    	fseek(refFile, 0, SEEK_END);
    	uint32_t refSize = ftell(refFile);
    	fseek(refFile, 0, SEEK_SET);
    	char* ref = new char[refSize];
    	fread(ref, 1, refSize, refFile);


    	logTraces.flush();
		FILE *logFile = fopen((name + ".logTrace").c_str(), "r");
    	fseek(logFile, 0, SEEK_END);
    	uint32_t logSize = ftell(logFile);
    	fseek(logFile, 0, SEEK_SET);
    	char* log = new char[logSize];
    	fread(log, 1, logSize, logFile);

    	if(refSize > logSize || memcmp(log,ref,refSize))
    		fail();
		else
			Workspace::pass();
	}
};

#ifdef DEBUG_PLUGIN

#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include <netinet/tcp.h>

#define RISCV_SPINAL_FLAGS_RESET 1<<0
#define RISCV_SPINAL_FLAGS_HALT 1<<1
#define RISCV_SPINAL_FLAGS_PIP_BUSY 1<<2
#define RISCV_SPINAL_FLAGS_IS_IN_BREAKPOINT 1<<3
#define RISCV_SPINAL_FLAGS_STEP 1<<4
#define RISCV_SPINAL_FLAGS_PC_INC 1<<5

#define RISCV_SPINAL_FLAGS_RESET_SET 1<<16
#define RISCV_SPINAL_FLAGS_HALT_SET 1<<17

#define RISCV_SPINAL_FLAGS_RESET_CLEAR 1<<24
#define RISCV_SPINAL_FLAGS_HALT_CLEAR 1<<25

class DebugPluginTest : public Workspace{
public:
	pthread_t clientThreadId;
	char buffer[1024];
	bool clientSuccess = false, clientFail = false;

	static void* clientThreadWrapper(void *debugModule){
		((DebugPluginTest*)debugModule)->clientThread();
		return NULL;
	}

	int clientSocket;
	void accessCmd(bool wr, uint32_t size, uint32_t address, uint32_t data){
		buffer[0] = wr;
		buffer[1] = size;
		*((uint32_t*) (buffer + 2)) = address;
		*((uint32_t*) (buffer + 6)) = data;
		send(clientSocket,buffer,10,0);
	}

	void writeCmd(uint32_t size, uint32_t address, uint32_t data){
		accessCmd(true, 2, address, data);
	}


	uint32_t readCmd(uint32_t size, uint32_t address){
		accessCmd(false, 2, address, VL_RANDOM_I(32));
		if(recv(clientSocket, buffer, 4, 0) != 4){
			printf("Should read 4 bytes");
			fail();
		}

		return *((uint32_t*) buffer);
	}



	void clientThread(){
		struct sockaddr_in serverAddr;

		//---- Create the socket. The three arguments are: ----//
		// 1) Internet domain 2) Stream socket 3) Default protocol (TCP in this case) //
		clientSocket = socket(PF_INET, SOCK_STREAM, 0);
		int flag = 1;
		int result = setsockopt(clientSocket,            /* socket affected */
								 IPPROTO_TCP,     /* set option at TCP level */
								 TCP_NODELAY,     /* name of option */
								 (char *) &flag,  /* the cast is historical
														 cruft */
								 sizeof(int));    /* length of option value */

		//---- Configure settings of the server address struct ----//
		// Address family = Internet //
		serverAddr.sin_family = AF_INET;
		// Set port number, using htons function to use proper byte order //
		serverAddr.sin_port = htons(7893);
		// Set IP address to localhost //
		serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
		// Set all bits of the padding field to 0 //
		memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

		//---- Connect the socket to the server using the address struct ----//
		socklen_t addr_size = sizeof serverAddr;
		int error = connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size);
//		printf("!! %x\n",readCmd(2,0x8));
		uint32_t debugAddress = 0xF00F0000;
		uint32_t readValue;

		while(resetDone != true){usleep(100);}

		while((readCmd(2,debugAddress) & RISCV_SPINAL_FLAGS_HALT) == 0){usleep(100);}
		if((readValue = readCmd(2,debugAddress + 4)) != 0x0000000C){
			printf("wrong break PC %x\n",readValue);
			clientFail = true; return;
		}

		writeCmd(2, debugAddress + 4, 0x13 + (1 << 15)); //Read regfile
		if((readValue = readCmd(2,debugAddress + 4)) != 10){
			printf("wrong break PC %x\n",readValue);
			clientFail = true; return;
		}

		writeCmd(2, debugAddress + 4, 0x13 + (2 << 15)); //Read regfile
		if((readValue = readCmd(2,debugAddress + 4)) != 20){
			printf("wrong break PC %x\n",readValue);
			clientFail = true; return;
		}

		writeCmd(2, debugAddress + 4, 0x13 + (3 << 15)); //Read regfile
		if((readValue = readCmd(2,debugAddress + 4)) != 30){
			printf("wrong break PC %x\n",readValue);
			clientFail = true; return;
		}

		writeCmd(2, debugAddress + 4, 0x13 + (1 << 7) + (40 << 20)); //Write x1 with 40
		writeCmd(2, debugAddress + 4, 0x13 + (29 << 7) + (0x10 << 20)); //Write x29 with 0x10
		writeCmd(2, debugAddress + 4, 0x67 + (29 << 15)); //Branch x29
		writeCmd(2, debugAddress + 0, RISCV_SPINAL_FLAGS_HALT_CLEAR); //Run CPU

		while((readCmd(2,debugAddress) & RISCV_SPINAL_FLAGS_HALT) == 0){usleep(100);}
		if((readValue = readCmd(2,debugAddress + 4)) != 0x00000014){
			printf("wrong break PC 2 %x\n",readValue);
			clientFail = true; return;
		}


		writeCmd(2, debugAddress + 4, 0x13 + (3 << 15)); //Read regfile
		if((readValue = readCmd(2,debugAddress + 4)) != 60){
			printf("wrong x1 %x\n",readValue);
			clientFail = true; return;
		}

		writeCmd(2, debugAddress + 4, 0x13 + (29 << 7) + (0x18 << 20)); //Write x29 with 0x10
		writeCmd(2, debugAddress + 4, 0x67 + (29 << 15)); //Branch x29
		writeCmd(2, debugAddress + 0, RISCV_SPINAL_FLAGS_HALT_CLEAR); //Run CPU



		while((readCmd(2,debugAddress) & RISCV_SPINAL_FLAGS_HALT) == 0){usleep(100);}
		if((readValue = readCmd(2,debugAddress + 4)) != 0x00000024){
			printf("wrong break PC 2 %x\n",readValue);
			clientFail = true; return;
		}


		writeCmd(2, debugAddress + 4, 0x13 + (3 << 15)); //Read x3
		if((readValue = readCmd(2,debugAddress + 4)) != 171){
			printf("wrong x3 %x\n",readValue);
			clientFail = true; return;
		}


		clientSuccess = true;
	}


	DebugPluginTest() : Workspace("DebugPluginTest") {
		loadHex("../../resources/hex/debugPlugin.hex");
		 pthread_create(&clientThreadId, NULL, &clientThreadWrapper, this);
		 noInstructionReadCheck();
	}

	virtual ~DebugPluginTest(){
		if(clientSocket != -1) close(clientSocket);
	}

	virtual void checks(){
		if(clientSuccess) pass();
		if(clientFail) fail();
	}
};

#endif


struct timespec timer_start(){
    struct timespec start_time;
    clock_gettime(CLOCK_REALTIME, &start_time); //CLOCK_PROCESS_CPUTIME_ID
    return start_time;
}

long timer_end(struct timespec start_time){
    struct timespec end_time;
    clock_gettime(CLOCK_REALTIME, &end_time);
    uint64_t diffInNanos = end_time.tv_sec*1e9 + end_time.tv_nsec -  start_time.tv_sec*1e9 - start_time.tv_nsec;
    return diffInNanos;
}

#define redo(count,that) for(uint32_t xxx = 0;xxx < count;xxx++) that
#include <pthread.h>
#include <queue>
#include <functional>
#include <thread>


static void multiThreading(queue<std::function<void()>> *lambdas, std::mutex *mutex){
	while(true){
		mutex->lock();
		if(lambdas->empty()){
			mutex->unlock();
			break;
		}
		std::function<void()> lambda = lambdas->front();
		lambdas->pop();
		mutex->unlock();

		lambda();
	}
}


static void multiThreadedExecute(queue<std::function<void()>> &lambdas){
	std::mutex mutex;
	std::thread * t[THREAD_COUNT];
	for(int id = 0;id < THREAD_COUNT;id++){
		t[id] = new thread(multiThreading,&lambdas,&mutex);
	}
	for(int id = 0;id < THREAD_COUNT;id++){
		t[id]->join();
		delete t[id];
	}
}

// char get_hex(int value)
// {
//    if (value < 0) return -1;
//    if (value > 16) return -1;
//    if (value <= 9) return (char)value;
//    value -= 10;
//    return (char)('A' + value);
// }


// void int_to_hex(char *c, unsigned int val) {

// }

int main(int argc, char **argv, char **env) {
	//Verilated::randReset(2);
	Verilated::traceEverOn(true);
	Verilated::commandArgs(argc, argv);

	printf("BOOT\n");
	timespec startedAt = timer_start();

	for(int idx = 0;idx < 1;idx++){

		#ifdef DEBUG_PLUGIN_EXTERNAL
		{
			Workspace w("debugPluginExternal");
			w.loadHex("../../resources/hex/debugPluginExternal.hex");
			w.noInstructionReadCheck();
			//w.setIStall(false);
			//w.setDStall(false);

			#if defined(TRACE) || defined(TRACE_ACCESS)
				//w.setCyclesPerSecond(5e3);
				//printf("Speed reduced 5Khz\n");
			#endif
			w.run(0xFFFFFFFFFFFF);
		}
		#endif

		// redo(REDO,TestControl().run(2*3*60000);)
		redo(REDO,TestControl().run(      1084308);)
		// redo(REDO,TestControl().run(      20000);)



		#ifdef CUSTOM_SIMD_ADD
			redo(REDO,Workspace("custom_simd_add").loadHex("../custom/simd_add/build/custom_simd_add.hex")->bootAt(0x00000000u)->run(50e3););
		#endif

	}

	uint64_t duration = timer_end(startedAt);
	cout << endl << "****************************************************************" << endl;
	cout << "Had simulate " << Workspace::cycles << " clock cycles in " << duration*1e-9 << " s (" << Workspace::cycles / (duration*1e-6) << " Khz)" << endl;
	if(Workspace::successCounter == Workspace::testsCounter)
		cout << "SUCCESS " << Workspace::successCounter << "/" << Workspace::testsCounter << endl;
	else
		cout<< "FAILURE " << Workspace::testsCounter - Workspace::successCounter << "/"  << Workspace::testsCounter << endl;
	cout << "****************************************************************" << endl << endl;


	exit(0);
}
