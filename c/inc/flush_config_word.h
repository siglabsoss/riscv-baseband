////////////////////////////////
//
//  Include this file as many times as needed, required to also include flush_config_word_data.h once
//


#ifndef __FLUSH_CONFIG_DATA_H__
#define __FLUSH_CONFIG_DATA_H__

#include "xbaseband.h"
#include "vmem.h"

// tell gcc to look for this (it will find in flush_config_word_data.h)
extern unsigned int flush_config_junk_row[16];


///////////////////////////////////
//
//   Call this macro every time you change a config word
//   It will overwrite the specified VREG in the process
//
#define FLUSH_CONFIG_WORD(_v0) \
    MVXV_KNOP(_v0, VMEM_ROW_ADDRESS(flush_config_junk_row)); \
    VNOP_LK8(_v0); \
    VNOP_LK9(_v0); \
    VNOP_SK1(_v0);


#endif