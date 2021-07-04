#ifndef __SLICE_CONTAINER_HPP__
#define __SLICE_CONTAINER_HPP__

// #include "slice.hpp"
#include "slice_constants.hpp"
#include <stdint.h>

class SliceFunctionalModel;

class SliceContainerModel
{
public:
  SliceContainerModel();
  ~SliceContainerModel();
  void input(uint32_t opcode, uint32_t import);
  void reset();
  SliceFunctionalModel* slices[NSLICES];

  unsigned get_right_index(unsigned index);
  unsigned get_left_index(unsigned index);
  SliceFunctionalModel* get_right(unsigned index);
  SliceFunctionalModel* get_left(unsigned index);

};

#endif