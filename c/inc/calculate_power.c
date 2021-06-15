
#include "calculate_power.h"
#include "copy_config.h"

#include "dma.h"
#include "vmem.h"
#include "csr_control.h"
#include "vmem_copy.h"

///
/// YOUR main.c MUST include these config words for this to work:
///

// #include "config_word_cmul_rx4_00.h"
// #include "config_word_add_rx4_01.h"
// #include "config_word_magsquare_rx4_01.h"

extern unsigned short config_word_cmul_rx4_00[32];
extern unsigned short config_word_add_rx4_01[32];
extern unsigned short config_word_magsquare_rx4_01[32];



VMEM_SECTION uint32_t pwr_all_one[16] = {0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1};
VMEM_SECTION uint32_t pwr_test_data[16] = {0x00010001, 0x00020002, 0x00030003,0x00040004,0x00050005,0x00060006,0x00070007,0x00080008,0x00090009,0x000a000a,0x000b000b,0x000c000c,0x000d000d,0x000e000e};
VMEM_SECTION uint32_t pwr_output_0[512] = {0};
VMEM_SECTION uint32_t pwr_output_1[128] = {0};
VMEM_SECTION uint32_t pwr_output_2[32] = {0};
VMEM_SECTION uint32_t pwr_output_3[16] = {0};

// for power control
VMEM_SECTION uint32_t pwr_bank_address_1[16] = {0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3};
VMEM_SECTION uint32_t pwr_permutation_4[16] = {0x0, 0x3000, 0x6000, 0x9000, 0xd000, 0xd000, 0xd000, 0xe000, 0xe000, 0xe000, 0xf000, 0xf000, 0xf000, 0x0, 0x0, 0x0};

static uint32_t* pwr_output_cpu = 0;
static uint32_t pwr_test_row = 0;
static uint32_t pwr_bank_row = 0;
static uint32_t pwr_permutation_row = 0;
static uint32_t pwr_one_row = 0;
static uint32_t pwr_row_0 = 0;
static uint32_t pwr_row_1 = 0;
static uint32_t pwr_row_2 = 0;
static uint32_t pwr_row_3 = 0;

// these don't have pwr in their names.  this won't matter once this file gets
// converted into .c/.h pair
static uint32_t cfg_stage_0 = 0;
static uint32_t cfg_stage_1 = 0;
static uint32_t cfg_stage_2 = 0;
// static uint32_t cfg_stage_3 = 0;

// 128 bits of results, note not all of these are usable
// more like 64 usable bits
static uint32_t power_128[4];
static uint16_t* power_half_words;


// cfg words with variable barrel shift
VMEM_SECTION unsigned short variable_cfg_stage_0[32];
VMEM_SECTION unsigned short variable_cfg_stage_1[32];
VMEM_SECTION unsigned short variable_cfg_stage_2[32];
// VMEM_SECTION unsigned short variable_cfg_stage_3[32];


static void setup_power_buffers(void) {
    pwr_output_cpu = pwr_output_2;
    pwr_test_row = VMEM_ROW_ADDRESS(pwr_test_data);
    pwr_bank_row = VMEM_ROW_ADDRESS(pwr_bank_address_1);
    pwr_permutation_row = VMEM_ROW_ADDRESS(pwr_permutation_4);
    pwr_one_row = VMEM_ROW_ADDRESS(pwr_all_one);
    pwr_row_0 = VMEM_ROW_ADDRESS(pwr_output_0);
    pwr_row_1 = VMEM_ROW_ADDRESS(pwr_output_1);
    pwr_row_2 = VMEM_ROW_ADDRESS(pwr_output_2);
    pwr_row_3 = VMEM_ROW_ADDRESS(pwr_output_3);
    power_half_words = (uint16_t*)power_128;
}


///
/// Set the barrel shift for each stage
unsigned power_set_shift(const unsigned stage, const unsigned shift ) {
    if(stage > 3) {
        return 1;
    }
    if( shift > 0x15 ) {
        return 2;
    }

    switch(stage) {
        case 0:
            copy_set_barrel(config_word_magsquare_rx4_01,   variable_cfg_stage_0, shift);
            break;
        case 1:
            copy_set_barrel(config_word_add_rx4_01,         variable_cfg_stage_1, shift);
            break;
        case 2:
            copy_set_barrel(config_word_cmul_rx4_00,        variable_cfg_stage_2, shift);
            break;
        // case 3:
        //     copy_set_barrel(config_word_cmul_rx4_00,        variable_cfg_stage_3, shift);
        //     break;
        default:
            return 3; // should be impossible to get here
            break;
    }

    return 0;
}

void power_shift_all(const unsigned a, const unsigned b, const unsigned c) {
    power_set_shift(0, a);
    power_set_shift(1, b);
    power_set_shift(2, c);
}

///
///
///
static void power_setup_cfg_zero(void) {
    power_set_shift(0, 0);
    power_set_shift(1, 0);
    power_set_shift(2, 0);
    // power_set_shift(3, 0);
    // copy_set_barrel(config_word_magsquare_rx4_01, variable_cfg_stage_0, 1);
}

static void power_setup_cfg_ben(void) {
    // 6
    // power_set_shift(0, 3);
    // power_set_shift(1, 2);
    // power_set_shift(2, 1);

    // 6 but with bad lumpiung
    // this will saturate internally and actually we dont
    // even detect it because we only check for sat at the output
    // power_set_shift(0, 0);
    // power_set_shift(1, 5);
    // power_set_shift(2, 1);
}

/// given a shift, this function chooses an ideal aka 
/// "good defaul" of a shift.  We stack the shifted bits
/// evently across the stages.  Reminder shift bits
/// get placed in later stages
void power_choose_ideal_shift(unsigned s) {
    unsigned int shift[3] = {0,0,0};
    
    const unsigned base = s / 3;
    const unsigned rem = s - (base*3);
    
    for(unsigned i = 0; i < 3; i++) {
        shift[i] = base;
        
        if( (2-i) < rem )  {
            shift[i]++;
        }
        
        power_set_shift(i, shift[i]);
        // cout << "shift[ " << i << "] " << shift[i] << "\n";
    }
    // cout << " base " << base << "\n";cout << " rem " << rem << "\n";
}


void __attribute__((optimize("Os"))) power_smart_shift(const unsigned s) {
    if( s <= 6 ) {
        power_choose_ideal_shift(s);
        return;
    }

    switch(s) {
        case 7:
            power_shift_all(5,1,1);
            break;
        case 8:
            power_shift_all(5,2,1);
            break;
        case 9:
            power_shift_all(5,3,1);
            break;
        case 10:
            power_shift_all(6,2,2);
            break;
        case 11:
            power_shift_all(7,2,2);
            break;
        case 12:
            power_shift_all(8,3,1);
            break;
        case 13:
            power_shift_all(9,3,1);
            break;
///////// guessing /////////
        case 14:
            power_shift_all(10,3,1);
            break;
        case 15:
            power_shift_all(11,3,1);
            break;
        case 16:
            power_shift_all(13,2,1);
            break;
        case 17:
            power_shift_all(13,3,1);
            break;
        case 18:
            power_shift_all(16,2,0);
            break;
///////// guessing /////////
        case 19:
            power_shift_all(15,4,0);
            break;
        case 20: // guess
            power_shift_all(17,3,0);
            break;
        case 21: // guess
            power_shift_all(18,3,0);
            break;
        case 22:
            power_shift_all(19,3,0);
            break;
        case 23:
            power_shift_all(19,3,1);
            break;
    }
}

// this number or less
// should match the switch above
#define POWER_MAX_SHIFT (23)




static void setup_power_cfg(void) {
    ///
    /// Stage 0
    ///
    cfg_stage_0 = VMEM_ROW_ADDRESS(variable_cfg_stage_0);
    
    ///
    /// Stage 1
    ///
    cfg_stage_1 = VMEM_ROW_ADDRESS(variable_cfg_stage_1);

    ///
    /// Stage 2
    ///
    cfg_stage_2 = VMEM_ROW_ADDRESS(variable_cfg_stage_2);
}

void setup_calculate_power(void) {

    ///
    /// Choose one of these to pick values for the 3 shift stages
    ///

    // power_setup_cfg_zero(); // init to zero shift 
    // power_choose_ideal_shift(7);
    // power_shift_all(19,3,1);
    power_smart_shift(15);
    // power_setup_cfg_ben();




    ///
    /// other setup
    /// 
    setup_power_buffers();
    setup_power_cfg();
}


static uint32_t pwr_run_time_0 = 0;
static uint32_t pwr_run_time_1 = 0;

// returns runtime for last execution
uint32_t calculate_power_runtime_0(void) {
    return pwr_run_time_0;
}

uint32_t calculate_power_runtime_1(void) {
    return pwr_run_time_1;
}


void judge_power_results(const uint64_t signal_power, const int signal_shift, char* advice, int* direction) {

    const uint64_t too_weak_tol = 5000;
    const uint64_t very_weak_tol = 1000;
    // too_weak_tol = 5000;
    // too_weak_tol = 25058;

    if( signal_power < very_weak_tol) {
        if( signal_shift - 6 >= 0 ) {
            *advice = 'c';
            *direction = -6;  // this number should be added to the shift and try again
            return;
        }
    }

    // signal power was too weak
    if( signal_power < too_weak_tol) {
        if( signal_shift - 2 >= 0 ) {
            *advice = 'c';
            *direction = -2;  // this number should be added to the shift and try again
            return;
        }
    }

    bool sat = (signal_power & 0x8000000000000000) == 0x8000000000000000;

    if( sat ) {
        if( signal_shift + 2 <= POWER_MAX_SHIFT ) {
            *advice = 'c';
            *direction = 2;  // this number should be added to the shift and try again
            return;
        }
    }

    *advice = 'o';
    *direction = 0;
}



/// calculates mag2
///
///  Regs
///     V13  - used for that VNOP_LK8,VNOP_LK9,VNOP_SK1 flush sequence
uint64_t calculate_power(const unsigned int source_row) {
    // const unsigned int output_pwr_addr = VMEM_DMA_ADDRESS(pwr_output_3);//VMEM_ROW_ADDRESS(pwr_output_3)*16;
    // vector_memory[output_pwr_addr] = 0;
    unsigned int start_clk;
    unsigned int end_clk;
    unsigned int end_clk2;
    CSR_READ(TIMER_VALUE, start_clk);





    pwr_output_cpu[0] = 0;
    pwr_output_cpu[4] = 0;
    pwr_output_cpu[8] = 0;
    pwr_output_cpu[12] = 0;

    MVXV_KNOP(V13, pwr_test_row);

    
    MVXV_KNOP(V0, cfg_stage_0);
    VNOP_LK14(V0);
    // FLush out these inputs
    VNOP_LK8(V13);
    VNOP_LK9(V13);
    VNOP_SK1(V13);

    /// 
    /// Stage 0
    /// 
    ///  Iterate over source row, add results to power_row_0
    ///
    MVXV_KNOP(V1, source_row);
    MVXV_KNOP(V2, source_row + 1);
    MVXV_KNOP(V3, pwr_row_0);
    MVXV_KNOP(V4, 1);
    MVXV_KNOP(V5, 1-(1<<12));
    MVXV_KNOP(V6, 2);

    const unsigned latency_0 = 4;

    for(unsigned int index = 0; index < latency_0; index++){
        ADD_LK8(V1, V1, V6, 0);
        ADD_LK9(V2, V2, V6, 0);
    }

    for(unsigned int index = 0; index < 32 - latency_0; index++){
        ADD_LK8(V1, V1, V6, 0);
        ADD_LK9(V2, V2, V6, 0);
        ADD_SK1(V3, V3, V5, 0);
    }

    for(unsigned int index = 0; index < latency_0; index++){
        ADD_SK1(V3, V3, V5, 0);
    }


    MVXV_KNOP(V0, cfg_stage_1);
    VNOP_LK14(V0);
    // Flush out these inputs
    VNOP_LK8(V13);
    VNOP_LK9(V13);
    VNOP_SK1(V13);

    /// Stage 1
    ///
    /// Iterate over row 0, results to row 1
    MVXV_KNOP(V1, pwr_row_0);
    MVXV_KNOP(V2, pwr_row_1);
    MVXV_KNOP(V3, pwr_row_0 + 4);
    MVXV_KNOP(V8, 8);
    MVXV_KNOP(V5, 1-(1<<12));
    
    MVXV_KNOP(V7, pwr_bank_row);
    VNOP_LK15(V7);
    MVK15V_KNOP(V7, 0);
    ADD_KNOP(V1, V1, V7, 0);
    ADD_KNOP(V3, V3, V7, 0);

    const unsigned latency_1 = 2;

    for(unsigned int index = 0; index < latency_1; index++){
        ADD_LK8(V1, V1, V8, 0);
        ADD_LK9(V3, V3, V8, 0);
    }

    for(unsigned int index = 0; index < 4 - latency_1; index++){
        ADD_LK8(V1, V1, V8, 0);
        ADD_LK9(V3, V3, V8, 0);
        ADD_SK1(V2, V2, V5, 0);
    }

    for(unsigned int index = 0; index < latency_1; index++){
        ADD_SK1(V2, V2, V5, 0);
    }

    
    MVXV_KNOP(V0, cfg_stage_2);
    VNOP_LK14(V0);
    // Flush out these inputs
    VNOP_LK8(V13);
    VNOP_LK9(V13);
    VNOP_SK1(V13);

    // return 0;

    /// Stage 2
    ///
    /// Iterate over row 1, results to row 2
    MVXV_KNOP(V1, pwr_one_row);
    MVXV_KNOP(V2, pwr_row_1);
    MVXV_KNOP(V3, pwr_row_2);

    ADD_KNOP(V2, V2, V7, 0);

    VNOP_LK8(V1);
    VNOP_LK9(V2);
    VNOP_SK1(V3);


    /// Stage 3 was repalced by software
    /// this means there is no shift in the 3rd state

    
    // MVXV_KNOP(V0, cfg_stage_3);
    // VNOP_LK14(V0);
    // // Flush out these inputs
    // VNOP_LK8(V13);
    // VNOP_LK9(V13);
    // VNOP_SK1(V13);

    /// Stage 3
    ///
    /// Iterate over row 2 results to row 3
    // MVXV_KNOP(V2, pwr_row_2);
    // MVXV_KNOP(V3, pwr_row_3);

    // MVXV_KNOP(V12, pwr_permutation_row);
    // VNOP_LK15(V12);
    // MVK15V_KNOP(V12,0);
    // ADD_KNOP(V2, V12, V2, 0);

    // VNOP_LK8(V1);
    // VNOP_LK9(V2);
    // VNOP_SK1(V3);

    ///// end of state 3 commented code /////

    CSR_READ(TIMER_VALUE, end_clk);

    for(int i = 0; i < 8; i++) {
        STALL(10);
    }

    // Stage 2 leaves the memory at multiples of 4 words
    power_128[0] = pwr_output_cpu[0];
    power_128[1] = pwr_output_cpu[4];
    power_128[2] = pwr_output_cpu[8];
    power_128[3] = pwr_output_cpu[12];



    int saturate = 0;
    uint64_t signal_power = 0;
    // uint16_t one_power;

    // these both point to the same memory
    // power_128          4 uint32_t
    // power_half_words   8 uint16_t

    // SET_REG(x3, 0x40000000);

    // loop through them as uint16_t types
    // for each type we check for saturation and then add
    for(int i = 0; i < 8; i++) {
        if( power_half_words[i] == 0x7fff ) {
            signal_power += 0x7fff; // unsure if this is faster
            saturate++;
        } else{
            signal_power += power_half_words[i];
        }

        // SET_REG(x3, power_half_words[i]);
        // SET_REG(x3, 0x40000000);
    }

    // for now we set this bit to notify of saturation
    // we could split this into a separate variable
    // for now this will work fine

    if( saturate > 0 ) {
        signal_power |= 0x8000000000000000;
    }



    CSR_READ(TIMER_VALUE, end_clk2);


    pwr_run_time_0 = end_clk - start_clk;
    pwr_run_time_1 = end_clk2 - end_clk;

    return signal_power;
}







////////////// examples of cfg words that I found in code //////////////
///
/// Stage 0
///
// cfg_stage_0 = VMEM_ROW_ADDRESS(config_word_magsquare_rx4_01);
// cfg_stage_0 = VMEM_ROW_ADDRESS(config_word_magsquare_rx4_15);
// cfg_stage_0 = VMEM_ROW_ADDRESS(config_word_magsquare_rx4_00);
// cfg_stage_0 = VMEM_ROW_ADDRESS(variable_cfg_stage_0);

///
/// Stage 1
///
// cfg_stage_1 = VMEM_ROW_ADDRESS(config_word_add_rx_01);
// cfg_stage_1 = VMEM_ROW_ADDRESS(config_word_add_rx4_01); // rx and rx4 are same
// cfg_stage_1 = VMEM_ROW_ADDRESS(config_word_add_rx4_02);
// cfg_stage_1 = VMEM_ROW_ADDRESS(config_word_add_rx_00);
// cfg_stage_1 = VMEM_ROW_ADDRESS(variable_cfg_stage_1);

///
/// Stage 2
///
// cfg_stage_2 = VMEM_ROW_ADDRESS(config_word_cmul_rx4_00);
// cfg_stage_2 = VMEM_ROW_ADDRESS(variable_cfg_stage_2);
