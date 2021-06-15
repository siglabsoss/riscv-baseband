#ifndef __CHECK_BOOTLOAD_H__
#define __CHECK_BOOTLOAD_H__

// 32 characters plus null
#define REGISTER_BOOTLOAD_SIZE (33)

void check_bootload_status(unsigned int word);
void register_bootload(const char* s, const unsigned int version);
void check_bootload_set_past_sync(const unsigned x);

#endif