///
/// This is meant to serve 2 purposes.
/// 1. allow us to interrogate declared "features" with arbitrary strins
/// 2. allows us to differentiate between a flashed and a bootloaded fpga

#ifndef __FEATURE_FLAGS_H__
#define __FEATURE_FLAGS_H__

void feature_flags_report(void);

// Call this from the bootloader 
// not the bitfile, but the code that came inside the bitfile
void feature_flags_report_bitfile(void);


// call at runtime from your main, only once
void setup_feature_flags(void);


void feature_flags_callback_a(unsigned int data);


// // ask the bootloaded code (or app)
//    FEATURE_FLAGS_A_CMD
// // not asking the bitfile, but asking the code that came inside the bitfile
//    FEATURE_FLAGS_B_CMD

#endif
