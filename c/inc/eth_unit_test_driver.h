


/////////////////////// eth ///////////////////////

unsigned int dma_in_last;
unsigned int dma_in_last_consumed;
unsigned int dma_in_expected_occupancy;
unsigned int ring_send_pending;

// must be power of 2
#define DMA_IN_COUNT (32)
// how big is each packet data payload, aka dma trigger size
#define DMA_IN_LEN (2)
#define DMA_IN_OFFSET (VMEM_DMA_ADDRESS(dma_in))

// mask here must be (DMA_IN_COUNT-1)
#define DMA_IN_NEXT_FOR(given) (((given)+1) & (DMA_IN_COUNT-1))

#define DMA_IN_START(x) (DMA_IN_OFFSET+(DMA_IN_LEN*(x)))
VMEM_SECTION unsigned int dma_in[DMA_IN_COUNT*DMA_IN_LEN];




void handle_internal_cmd(unsigned int data_packet){
    unsigned int type = data_packet&TYPE_MASK;
    unsigned int data = data_packet&DATA_MASK;

    // report_test_results(data_packet);

    switch(type) {
        case SEED_RANDOM_CMD:
            seed_callback(data);
            break;
        default: // fixme add a counter for illegal commands arriving here?
            break;
    }
}



// only call this if guarenteed to be occupancy
// left in outbound ringbus
void to_ring(int index) {
    unsigned int addr;
    unsigned int data_packet;
    unsigned int mem_start = DMA_IN_START(index);

    addr        = vector_memory[mem_start + 0] & 0xff;
    data_packet = vector_memory[mem_start + 1];

    // SET_REG(x3, 0x30000000 | addr);
    // SET_REG(x4, data_packet);

    CSR_WRITE(RINGBUS_WRITE_ADDR, addr);
    CSR_WRITE(RINGBUS_WRITE_DATA, data_packet);
    CSR_WRITE_ZERO(RINGBUS_WRITE_EN);

    if( addr == 0 ) {
        handle_internal_cmd(data_packet);
    }

    // handle_internal_cmd(addr);

    // total_ring_sent++;
}



void trig_in(void)
{
    // one to trig is next is last+1
  unsigned int dma_in_next = DMA_IN_NEXT_FOR(dma_in_last);//  (dma_in_last+1) & 0x3;

  // at this point we are triggering a future DMA which dooms the memoryu
  // we need to check if we overflowd


  // SET_REG(x3, 0x20000000 | dma_in_next);
  // SET_REG(x3, 0x40000000 | dma_in_last_consumed); 

  // detect_ringbus_buffer_overflow(dma_in_next, dma_in_last_consumed);
  // x4 = dma_in_next;

  // the DMA_IN_START() macro here converts the index to a DMApointer
  CSR_WRITE(DMA_0_START_ADDR, DMA_IN_START(dma_in_next));
  CSR_WRITE(DMA_0_LENGTH, DMA_IN_LEN);
  CSR_WRITE(DMA_0_TIMER_VAL, 0xffffffff);  // start right away
  CSR_WRITE_ZERO(DMA_0_PUSH_SCHEDULE); // any value

  dma_in_last = dma_in_next;
}

void setup_dma_in(void) {
  trig_in();
  trig_in();
  trig_in();
  trig_in();
  // the core consumes a schedule when it starts running
  // so this number is 4-1
  dma_in_expected_occupancy = 4; 
}

void check_eth_ring(void) {

}



void handle_pending_ring(void){
  while(ring_send_pending) {

      dma_in_last_consumed = DMA_IN_NEXT_FOR(dma_in_last_consumed);// (dma_in_last_consumed+1) & 0x3;
      // x4 = dma_in_last_consumed;
      to_ring(dma_in_last_consumed);
      ring_send_pending--;

  }
}

void handle_single_dma_in(void)
{
  unsigned int occupancy;
  CSR_READ(DMA_0_SCHEDULE_OCCUPANCY, occupancy);
  unsigned int i;
  // check_dma = occupancy;
  for(i=occupancy;i<dma_in_expected_occupancy;i++) {
    trig_in(); // this can be earler for better performance
    ring_send_pending++;
    handle_pending_ring();
    break;
    // check_dma = 0xd0000000 | ring_send_pending;
  }
}



/////////////////////// eth ///////////////////////
