#ifndef __STATIC_HASH_H__
#define __STATIC_HASH_H__

#include <stdint.h>

// static_hash.h
// modified from http://lolengine.net/blog/2011/12/20/cpp-constant-string-hash

// a modified version of ARRAY_SIZE
#define __STR_LEN(arr) ((sizeof(arr) / sizeof(arr[0]))-1)

#define __H1(s,i,x)   (x*65599u+(uint8_t)s[(i)<__STR_LEN(s)?__STR_LEN(s)-1-(i):__STR_LEN(s)])
#define __H4(s,i,x)   __H1(s,i,__H1(s,i+1,__H1(s,i+2,__H1(s,i+3,x))))
#define __H16(s,i,x)  __H4(s,i,__H4(s,i+4,__H4(s,i+8,__H4(s,i+12,x))))
#define __H64(s,i,x)  __H16(s,i,__H16(s,i+16,__H16(s,i+32,__H16(s,i+48,x))))
#define __H256(s,i,x) __H64(s,i,__H64(s,i+64,__H64(s,i+128,__H64(s,i+192,x))))
#define STATIC_HASH(s)    ((uint32_t)(__H256(s,0,0)^(__H256(s,0,0)>>16)))



// possible runtime version of above code
// #include <string.h>
// #define HASH(str) generateHash(str, strlen(str))

// inline unsigned int generateHash(const char *string, size_t len)
// {
//     unsigned int hash = 0;
//     for(size_t i = 0; i < len; ++i)
//         hash = 65599 * hash + string[i];
//     return hash ^ (hash >> 16);
// }



//
// use t3 for an example
//

// uint32_t t1 = __STR_LEN("hello");
// uint32_t t2 = __H1("not hashed very much",1,2134);
// uint32_t t3 = STATIC_HASH("funny_bone") & DATA_MASK;

// ring_block_send_eth(0xDE000000 | t1);
// ring_block_send_eth(0xDE000000 | t2);
// ring_block_send_eth(0xDE000000 | t3);

#endif