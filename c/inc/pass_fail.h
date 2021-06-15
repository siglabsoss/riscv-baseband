#ifndef __PASS_FAIL_H__
#define __PASS_FAIL_H__


/////////////////////////////////////////
//
//  This handles the "passfail (RW)" memory section
//  also known as "hard_pointers" in the linker script
//


// if the ld file MEMORY section changes, these may change
// unsigned int volatile *pass_fail_0 = (unsigned int *) 0x7ff8;
#define pass_fail_0 ((volatile unsigned int *) 0x7ff8)
#define pass_fail_1 ((volatile unsigned int *) 0x7ffc)


#endif
