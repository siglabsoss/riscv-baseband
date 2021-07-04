#include "slice.hpp"
#include "slice_container.hpp"


#include <iostream>
#include <assert.h>

using namespace std;

SliceContainerModel::SliceContainerModel()
{
  for(int i = 0; i < NSLICES; i++)
  {
    slices[i] = new SliceFunctionalModel(i);
    slices[i]->parent = this;
    slices[i]->verbose = false;
  }
}

SliceContainerModel::~SliceContainerModel()
{
  for(int i = 0; i < NSLICES; i++)
  {
    if(slices[i]) {
      delete slices[i];
      slices[i] = 0;
    }
  }
}


void SliceContainerModel::input(uint32_t opcode, uint32_t import)
{
  for(int i = 0; i < NSLICES; i++)
  {
    slices[i]->input(opcode, import);
  }
}


void SliceContainerModel::reset()
{
  for(int i = 0; i < NSLICES; i++)
  {
    slices[i]->reset();
  }
}

unsigned SliceContainerModel::get_right_index(unsigned index)
{
  unsigned calc = (index + 1 + NSLICES) % NSLICES;
  return calc;
}

unsigned SliceContainerModel::get_left_index(unsigned index)
{
  unsigned calc = (index - 1 + NSLICES) % NSLICES;
  return calc;
}

SliceFunctionalModel* SliceContainerModel::get_right(unsigned index)
{
  assert(index <= NSLICES);
  return slices[ get_right_index(index) ];
}

SliceFunctionalModel* SliceContainerModel::get_left(unsigned index)
{
  assert(index <= NSLICES);
  return slices[ get_left_index(index) ];
}

