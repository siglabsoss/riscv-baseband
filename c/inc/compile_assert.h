#ifndef __COMPILE_ASSERT_H__
#define __COMPILE_ASSERT_H__


// https://stackoverflow.com/questions/3385515/static-assert-in-c

/////////////////////////////////////
//
//
//  Provides 2 different ways of compile time assertions
//
//   COMPILE_ASSERT_2()  less specific, only gives line number NOT FILE
//
//   COMPILE_ASSERT()    very specific, but can't be used in global scope? why?
//   works fine inside a funciton



#define STATIC_ASSERT(COND,MSG) typedef char static_assertion_##MSG[(!!(COND))*2-1]
// token pasting madness:
#define COMPILE_TIME_ASSERT_EXPAND_3(X,L) STATIC_ASSERT(X,static_assertion_at_line_##L)
#define COMPILE_TIME_ASSERT_EXPAND_2(X,L) COMPILE_TIME_ASSERT_EXPAND_3(X,L)
// less desirable, this option 
#define COMPILE_ASSERT_2(X)    COMPILE_TIME_ASSERT_EXPAND_2(X,__LINE__)


#define COMPILE_ASSERT(X) ({ extern int __attribute__((error("assertion failure: '" #X "' not true"))) compile_time_check(); ((X)?0:compile_time_check()),0; })


#endif