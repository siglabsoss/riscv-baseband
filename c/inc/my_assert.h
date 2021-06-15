#ifndef __MY_ASSERT_H__
#define __MY_ASSERT_H__

#define MY_ASSERT(x) if(!(x)) { ring_block_send_eth(APP_ASSERT_PCCMD|__LINE__);}

#endif
