#ifndef __BOOTLOADER_H__
#define __BOOTLOADER_H__

// do not define more than one function under this label
// this allows us to pin the bootloader to a specific address
#define BOOTLOADER_SECTION_ENTRY_FUNCTION __attribute__((section(".bootloader.entry")))
#define BOOTLOADER_SECTION __attribute__((section(".bootloader")))
#define BOOTLOADER_VARIABLE_SECTION __attribute__((section(".bootloader.data")))

void no_exit_bootload(unsigned int total_word_count, unsigned int is_eth);

// FIXME do not put any files with BOOTLOADER_SECTION here
void bootload_eth(unsigned int start_index, unsigned int size);

#endif