#ifndef __HANDLE_GENERIC_OP_H__
#define __HANDLE_GENERIC_OP_H__

#include <stdint.h>

typedef void (*generic_callback_dual_t)(const uint32_t, const uint32_t, const uint32_t);
typedef uint32_t* (*generic_callback_simple_t)(const uint32_t);
typedef void (*generic_callback_ring_t)(const unsigned int);
typedef void (*generic_callback_post_t)(const uint32_t, const uint32_t, const uint32_t);


// void fb_queue_ring_eth(unsigned int word) {

void handle_generic_callback_original(const unsigned int data);
void handle_generic_callback_dual(const unsigned int data);

void handle_generic_register_get_pointer(const generic_callback_simple_t fn);
void handle_generic_register_ring(const generic_callback_ring_t fn);
void handle_generic_register_dual_callback(const generic_callback_dual_t fn);
void handle_generic_register_post_callback(const generic_callback_post_t fn);

void g_op(
    uint32_t* const r0,
    uint32_t* const r1,
    const char operation,
    const uint32_t _sel,
    const uint32_t _val,
    const uint32_t _rb_type);


#define GENERIC_OP_RESET (0)
#define GENERIC_OP_ADD   (1)
#define GENERIC_OP_SUB   (2)
#define GENERIC_OP_SET   (3)
#define GENERIC_OP_GET   (4)

#endif
