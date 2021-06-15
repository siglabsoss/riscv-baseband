#ifndef __RING_ASSERT_H__

// see https://barrgroup.com/Embedded-Systems/How-To/Define-Assert-Macro
// you must have a variable testfails for this to work
#define ASSERT(expr) \
if (!(expr)) \
  testfails++;
#endif