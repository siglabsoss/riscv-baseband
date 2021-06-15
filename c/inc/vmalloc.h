#ifndef __VMALLOC_H__
#define __VMALLOC_H__

#include "linker_symbols.h"

//////////////////////
//
//  Implements a fixed size malloc which gives out vmem exclusivly
//  
//  An array of nodes is created into a linked list.  this array is 
//  fixed allocated.  as nodes are handed out and taken back into the list
//  the next pointers will become unsorted, however the node location themselves
//  is fixed
//
//  at startup we link the list and scan for nodes that overlap compile time constants
//  we treat these sections as initially vmalloc'd
// 

// in bytes
#define VMEM_START (0x40000)
// in bytes
#define VMEM_TOTAL_SIZE (0x40000)
// in bytes
#define VMALLOC_CHUNK_SIZE (1024*4)

#define VMALLOC_CHUNK_COUNT (VMEM_TOTAL_SIZE/VMALLOC_CHUNK_SIZE)

#define VM_IDX_TO_ADDRESS(x) (VMEM_START+((x)*VMALLOC_CHUNK_SIZE))
#define VM_ADDRESS_TO_IDX(x) (((((unsigned int)x)-VMEM_START)/VMALLOC_CHUNK_SIZE))

// a pointer to a block of vmemory with a fixed size
// typedef unsigned int vmem_1024_t[VMALLOC_CHUNK_SIZE];

// a pointer in vex address space
typedef unsigned int vmem_t;

typedef unsigned int* vmem_dma_t;

typedef unsigned int* vmem_row_t;

typedef struct vmlnode {
  // (opt) make a short or a char
  int idx; // we keep track of this linked list using ids, however this gets mul/divided into address when passed to user
  // (opt) make a short* because imem/dmem does not go over 64k
  struct vmlnode* next;
  // could add an int bundled; which is set iff a multi allocaiton was used
  // grouped 
} vmlnode_t;

////////////////////////////////
//
//
//  Link list basics
//  We keep track of head and tail
//
//  when head==tail we have 1 thing left
//  when head==0, tail==0 we have 0 things left
//

// extern const volatile unsigned int __vmem_start;
// extern const volatile unsigned int __vmem_end;

typedef struct vmalloc_struct {
  vmlnode_t nodes[VMALLOC_CHUNK_COUNT];
  vmlnode_t *head;
  vmlnode_t *tail;
  unsigned int double_free_count; // error tracking

} VMalloc;

void _get_VMalloc_defaults(VMalloc *mgr) {
  mgr->double_free_count = 0;
}

void __attribute__((deprecated)) init_VMalloc(VMalloc *mgr) {
  // VMalloc tmp = _get_VMalloc();
  _get_VMalloc_defaults(mgr);

  // sanity check....
  // we are using defines above, but this verifies that they match the linker section
  if(
    ((unsigned int) &__vmem_start) != VMEM_START 
    )
  {
    // hang error, if you get here the linker script vmem has changed
    while(1){};
  }

  // grab the last address of pre-compiled constants (set by linker)
  unsigned int precompile_end = ((unsigned int) &__vmem_end);

  // tiny state machine to catch if we were skipping vmem chunks
  // and then stop and then start skipping again (should never happen)
  // starts at 1, and is set to 1 during loop when we are skipping nodes
  // skipmode gets set to 0 (only once), and that's when first_node_idx is taken
  int skipmode = 1;
  int first_node_idx = 0;

  // setup linked list
  // skip allocating nodes that collide with preallocated memory
  for(unsigned int i = 0; i < VMALLOC_CHUNK_COUNT; i++) {
    // always set node idx
    mgr->nodes[i].idx = i;

    // calculated address of node we are creating
    unsigned int node_i_address = VM_IDX_TO_ADDRESS(i);

    // check if its allocated
    if (node_i_address < precompile_end) {
      
      // skip this one
      if( skipmode != 1 ) {
        while(1){}; // this means comparing against precompile_end changed (universe is broken)
      } else {
        // address of this node collides with pre-allocated memory
        // 
        mgr->nodes[i].next = 0;
      }
    } else {

      if( skipmode == 1 ) {
        first_node_idx = i;
      }
      // we stop skipping
      skipmode = 0;
      // normal
      mgr->nodes[i].next = &(mgr->nodes[i+1]);
    }
  }
  // fix last node's next pointer
  mgr->nodes[VMALLOC_CHUNK_COUNT-1].next = 0;

  // head/tail
  // head gets the first un-skipped node from above
  mgr->head = &(mgr->nodes[first_node_idx]);
  mgr->tail = &(mgr->nodes[VMALLOC_CHUNK_COUNT-1]);
}

// returns 1 for success
// removes the head of the linked list, and gives you a pointer
// to the original location NOT a copy
unsigned int _get_remove_head(VMalloc *mgr, vmlnode_t **node_out) {

  // true if only 1 left
  unsigned int one_item_left = mgr->head == mgr->tail;

  if(mgr->head != 0) {
    // copy a ref
    vmlnode_t *node = mgr->head;

    // move head
    mgr->head = mgr->head->next;

    // update "taken" node
    node->next = 0;

    *node_out = node;
    
    // if this was the last node in the list, nuke the tail
    if(one_item_left) {
      mgr->tail = 0;
    }


    return 1;
  }
  return 0;
}

// gets a single chuck of size chunk
// returns 0 if fail
vmem_t* __attribute__((deprecated)) vmalloc_single(VMalloc *mgr) {
  vmlnode_t* got_node;
  int success = _get_remove_head(mgr, &got_node);

  if(success) {
    return (vmem_t*)VM_IDX_TO_ADDRESS(got_node->idx);
  }
  return 0; // fail
}

// we are getting a free call from an address
// we reverse calculate which link list node we are getting from the address
// then we update tail to point there.
void vfree(VMalloc *mgr, vmem_t* p) {
  // which node are we going to add back
  // todo check for out of range index
  unsigned int idx = VM_ADDRESS_TO_IDX(p);
  vmlnode_t* freed = &(mgr->nodes[idx]);

  // if at least one thing in the list
  if(mgr->tail != 0) {

    ///////////////////////
    //
    //  Double free detection
    //
    //  Only runs if list has items (cant double free if list is empty)
    //  two conditions:
    //    * back to back double free:
    //      - the tail == freed. (and freed->next is 0)
    //    * delated double free
    //      - the tail == something else, and freed->next is not 0
    //

    // if the tail already pointing at p
    if(mgr->tail == freed) {
      // double free
      mgr->double_free_count++;
      return;
    } else if (freed->next != 0) {
      // double free
      mgr->double_free_count++;
      return;
    }

  }

  if(mgr->tail != 0) {
    // update tail node's next to be the free'd node
    mgr->tail->next = freed;
    // update the free'd node to point at 0
    mgr->nodes[idx].next = 0;

    // move tail pointer to free'd node
    mgr->tail = mgr->tail->next;
  } else {
    // special case needs test
    // set tail to free'd node
    mgr->tail = freed;

    // set tail node next to null
    mgr->tail->next = 0;

    // set head to tail
    mgr->head = mgr->tail;
  }
}


// expensive, for testing purposes do not call

unsigned int vmalloc_available(VMalloc *mgr) {

  if(mgr->head == 0) {
    return 0;
  }

  vmlnode_t* cur = mgr->head;

  unsigned int sz = 1;
  while(cur->next != (void*)0) {
    cur = cur->next;
    sz++;
  }

  return sz;

}
#endif
