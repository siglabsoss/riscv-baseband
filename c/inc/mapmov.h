///////////////////////////////////////////
///
/// Shared Functions
///



// we will reserve 0 and 1 for fun
// stop using these
#define MAPMOV_MODE_128_CENTERED          (2)
#define MAPMOV_MODE_DEBUG                 (3)
#define MAPMOV_MODE_128_CENTERED_LINEAR   (4)
#define MAPMOV_MODE_128_CENTERED_FILTERED (5)
#define MAPMOV_MODE_REED_SOLOMON          (6)
#define MAPMOV_MODE_320_CENTERED          (7)

// move to these
#define MAPMOV_SUBCARRIER_128             (2)
#define MAPMOV_SUBCARRIER_320             (7)
#define MAPMOV_SUBCARRIER_640_LIN         (8)
#define MAPMOV_SUBCARRIER_512_LIN         (9)
#define MAPMOV_SUBCARRIER_64_LIN         (10)


#define AIRPACKET_CODE_UNCODED               (0)
#define AIRPACKET_CODE_REED_SOLOMON          (1)


#ifndef VERILATE_TESTBENCH
#include "csr_control.h"

///////////////////////////////////////////
///
/// Vex functions
///


void CSR_WRITE_MAPMOV_ACTIVE(const unsigned int index, const unsigned int value);

void mapmov_choose_mode(const unsigned int mode, const unsigned int reset_module);

void mapmov_report_settings(void);

// probably never called outside the function aka don't need in .h
void mapmov_latch_settings(const unsigned int active,
                           const unsigned int start,
                           const unsigned int end);

void mapmov_pet_partial(void);

#else

///////////////////////////////////////////
///
/// TestBench / S-Modem functions
///



#endif
