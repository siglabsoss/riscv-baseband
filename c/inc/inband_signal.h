#ifndef __INBAND_SIGNAL__
#define __INBAND_SIGNAL__


typedef struct inband_header {
	unsigned int type;
	unsigned int read; // 1 for read 0 for write
	unsigned int addr;
	unsigned int data;

	//
	unsigned int rf_packet_id;     // a fixed number that changes once for each "rf" packet
	unsigned int rf_packet_size;   // how many samples (32bit words) in total will this rf packet be
	unsigned int udp_packet_size;  // size of this udp packet in bytes, maybe smaller for last packet
	unsigned int packet_countdown; // starts at the (number of packets-1) we will be sending for this "rf" packet, 0 means final packet

	unsigned int unused[24];
} inband_t;


#define INBAND_T_SIZE_BYTES (32*4)


#define INBAND_TYPE_CONTROL 0
#define INBAND_TYPE_DATA 1
#define INBAND_TYPE_BOOTLOAD_DATA 2


#define PRINT_INBAND_T(x) \
cout << "inband_t: " << endl; \
cout << "  type: " << x.type << endl; \
cout << "  read: " << x.read << endl; \
cout << "  addr: " << x.addr << endl; \
cout << "  data: " << x.data << endl; \
cout << "  rf_packet_id: " << x.rf_packet_id << endl; \
cout << "  rf_packet_size: " << x.rf_packet_size << endl; \
cout << "  udp_packet_size: " << x.udp_packet_size << endl; \
cout << "  packet_countdown: " << x.packet_countdown << endl;

#endif
