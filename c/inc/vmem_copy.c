#include "vmem_copy.h"
#include "xbaseband.h"
#include "vmem.h"
#include "circular_shift.h"



void vmem_copy_rows(const unsigned int input_rows, const unsigned int output_rows, const unsigned int rows){
    MVXV_KNOP(V2, input_rows);
    MVXV_KNOP(V3, output_rows);
    MVXV_KNOP(V4, 0x1);

    for (unsigned int i = 0; i < rows; i++){
        ADD_LK13(V2, V2, V4, 0x0);
        ADD_SK13(V3, V3, V4, 0x0);
    }
}


  // VNOP_LK13(V2);
  // VNOP_SK13(V3);
  // ADD_KNOP(V2, V2, V4, 0x0);
  // ADD_KNOP(V3, V3, V4, 0x0);


// used in unit tests as model
// also used when there are less than 16 words to move
void vmem_copy_words_slow(const unsigned int input_dma, const unsigned int output_dma, const unsigned int words){

    unsigned* const input_cpu = REVERSE_VMEM_DMA_ADDRESS(input_dma);
    unsigned* const output_cpu = REVERSE_VMEM_DMA_ADDRESS(output_dma);

    for(unsigned i = 0; i < words; i++) {
        output_cpu[i] = input_cpu[i];
    }
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wattributes"

///
/// Returns N bits starting from the zero position (lsb)
/// Returned value is a type uint16_t
///
inline uint16_t __attribute__((always_inline)) grow_bits_16(unsigned count) {
    switch(count) {
        default:
        case 0:
            return 0x0000;
        case 1:
            return 0x0001;
        case 2:
            return 0x0003;
        case 3:
            return 0x0007;
        case 4:
            return 0x000f;
        case 5:
            return 0x001f;
        case 6:
            return 0x003f;
        case 7:
            return 0x007f;
        case 8:
            return 0x00ff;
        case 9:
            return 0x01ff;
        case 10:
            return 0x03ff;
        case 11:
            return 0x07ff;
        case 12:
            return 0x0fff;
        case 13:
            return 0x1fff;
        case 14:
            return 0x3fff;
        case 15:
            return 0x7fff;
        case 16:
            return 0xffff;
    }
}

#pragma GCC diagnostic pop

// tested but not currently under test
// this may be faster than the generic vmem_copy_words() but only if input is alined
// will give WRONG results if input in not aligned

bool vmem_copy_words_input_aligned(const unsigned int input_dma, const unsigned int output_dma, const unsigned int words, const unsigned int garbage_row) {

    // bool input_aligned  = (input_dma % 16) == 0;
    // bool output_aligned = (output_dma % 16) == 0;

    const unsigned int rows = words / 16;

    const unsigned int input_rows = VMEM_DMA_ADDRESS_TO_ROW(input_dma);
    const unsigned int output_rows = VMEM_DMA_ADDRESS_TO_ROW(output_dma);


    // trick is to skew by N
    // the amount of skew need to store in the previous row address
    // meaning it goes backwards
    // this means that the skew becomes un-skewed in memory
    // in this diagram, the rows are only 4 wide for easy understanding
/*
input        |0123|4567|89  |
output      0|1234|5678|9   |
*/
    // in this case, output skew is 1
    // if we load 0123, we want to store the zero backwards
    // so we adjust the row and then store

    // if( input_aligned && !output_aligned ) {
    if( 1 ) {

        // how far left of 16 is the output
        uint16_t output_skew = 16 - (output_dma % 16);

        MVXV_KNOP(V4, 0x1); // for increment

        // using store permutation we shift by N to the left
        const uint16_t s_perm = (output_skew << 12) & 0xf000;
        // const uint16_t l_perm = (output_skew << 12) & 0xf000;

        MVXV_KNOP(V8, s_perm);

        // we need to make a predicate for the banks that overlap the
        // negavite boundary
        uint16_t negative_pred = grow_bits_16(16-output_skew);

        // reset V14
        // Load 1 into V15
        // use the predicate to set V14 to non homogeneous value
        MVXV_KNOP(V14, 0);
        MVXV_KNOP(V15, 1);
        MV_KNOP(V14, V15, negative_pred);



        // load row pointers
        MVXV_KNOP(V2, input_rows);
        MVXV_KNOP(V3, output_rows+1); // output is fractional, so bump

        SUB_KNOP(V3, V3, V14);

        // add on permutations / skew, held in V8
        // ADD_KNOP(V2, V2, V7);
        ADD_KNOP(V3, V3, V8);

        // Loop over the rows
        //
        for (unsigned int i = 0; i < rows; i++){
            ADD_LK13(V2, V2, V4, 0x0);
            ADD_SK13(V3, V3, V4, 0x0);
        }

        // we need to guard against the last store
        const unsigned tail = words - (words - (words%16));

        // we need to overwrite V3 (the output pointer)
        // with the garbage row to protect the tail (the fractional)
        // end of the row that we dont want to write
        // we do this by calculating how many bits we need to set
        // (same as tail)
        // and then skewing the bits (rotate right) by the output skew

        uint16_t tail_pred = grow_bits_16(tail);

        tail_pred = ror16(tail_pred, output_skew);


        // we also (need?) to apply the same skew to the garbage address
        // so we use the same technique we used on V3, here.
        // then we selectivly overwrite the tail
        MVXV_KNOP(V15, garbage_row);
        ADD_KNOP(V15, V15, V8);
        MV_KNOP(V3, V15, tail_pred);

        VNOP_LK13(V2);
        VNOP_SK13(V3);


        return true;
    }


    return false;
}

// extern void report_test_results(const unsigned int data);


bool vmem_copy_words(const unsigned int input_dma, const unsigned int output_dma, const unsigned int words, const unsigned int garbage_row) {

    // bool input_aligned  = (input_dma % 16) == 0;
    // bool output_aligned = (output_dma % 16) == 0;

    // if( input_aligned ) {
    //     return vmem_copy_words_input_aligned(input_dma, output_dma, words, garbage_row);
    // }

    const unsigned int rows = words / 16;

    if( rows == 0 ) {
        vmem_copy_words_slow(input_dma, output_dma, words);
        return true;
    }

    const unsigned int input_rows = VMEM_DMA_ADDRESS_TO_ROW(input_dma);
    const unsigned int output_rows = VMEM_DMA_ADDRESS_TO_ROW(output_dma);


    MVXV_KNOP(V4, 0x1); // for increment

    // trick is to skew by N
    // the amount of skew need to store in the previous row address
    // meaning it goes backwards
    // this means that the skew becomes un-skewed in memory
    // in this diagram, the rows are only 4 wide for easy understanding
/*

input        |0123|4567|89  |
output      0|1234|5678|9   |

*/
    // in this case, output skew is 1
    // if we load 0123, we want to store the zero backwards
    // so we adjust the row and then store


    // example 2
    // both input and output are not aligned

/*

input        | 012|3456|789 |
output     01|2345|6789|    |

*/

/*
V4     increment 1's,  these 1's are also used when calculating V14

V2     input row
V3     output row

V8     upper address bits (skew bits), with no lower address bits

V13....garbage row
V15....garbage row modified
V14    some ones (for subtracting bank by 1 for the negative hanging over)
*/



    // how far left of 16 is the output
    const uint16_t output_skew = 16 - (output_dma % 16);
    const uint16_t input_skew  = 16 - (input_dma  % 16);
    const uint16_t delta_skew  = (16 - (output_dma % 16) + (input_dma % 16)) % 16;

    // using store permutation we shift by N to the left
    const uint16_t s_perm = (delta_skew << 12) & 0xf000;

    MVXV_KNOP(V8, s_perm);

    // we need to make a predicate for the banks that overlap the
    // negavite boundary
    const uint16_t negative_pred_head = grow_bits_16(16-output_skew);

    // reset V14
    // 1's exist in V4
    // use the predicate to set V14 to non homogeneous value
    MVXV_KNOP(V14, 0);
    MV_KNOP(V14, V4, negative_pred_head);



    // load row pointers
    MVXV_KNOP(V2, input_rows);
    MVXV_KNOP(V3, output_rows+1); // output is fractional, so bump

    SUB_KNOP(V3, V3, V14);  // apply the negative 1 in V14 so V3 is non homogenous

    // add on permutations / skew, held in V8
    ADD_KNOP(V3, V3, V8);

    // keep track of how many we have moved
    // this is more tricky than the input aligned case
    uint32_t moved = 0;


    MVXV_KNOP(V13, garbage_row);

    // deal with head
    const unsigned head = 16 - input_skew;

    if( 1 ) {

        // (in case of !input and !output aligned )
        // we loaded too many, we need to mask off this many when we do the first store
        // we need a unique pred for the first load

        uint16_t head_pred = ~grow_bits_16(head);

        head_pred = ror16(head_pred, delta_skew);


        // Garbage row is in V13
        ADD_KNOP(V15, V13, V8);

        MV_KNOP(V3, V15, head_pred);

        VNOP_LK13(V2);
        VNOP_SK13(V3);

        ADD_KNOP(V2, V2, V4, 0x0);
        // we don't bump V3 as we will re-calculate it below

        // track how many words we've "moved" aka written
        moved += input_skew;
    }

    // we need a predicate for normal operation
    uint16_t negative_pred = grow_bits_16((16+(16-output_skew) - head) % 16);

    if( 1 ) {


        // 26, 22, 27              needs +1
        // 33, 31, 17              needs +2
        // 1,  6,  45              needs +2
        // 4,  37, 30              needs +2
        // 7,  39, 45              needs +2

        // unsure about this part, why is V3 so inconsitent?
        // depending on which skew is larger we do or don't
        // add an extra row to V3.
        // not entirly sure why but it passes tests
        uint32_t output_add = 1;
        if( input_skew >= output_skew ) {
            output_add = 2;
        }

        MVXV_KNOP(V3, output_rows+output_add);


        // reset V14
        // V4 already has 1's
        // use the predicate to set V14 to non homogeneous value
        MVXV_KNOP(V14, 0);
        MV_KNOP(V14, V4, negative_pred);

        SUB_KNOP(V3, V3, V14);  // apply the negative 1 in V14 so V3 is non homogenous

        // add on permutations / skew, held in V8
        ADD_KNOP(V3, V3, V8);
    }

    // Loop over the rows
    //
    while( moved+16 <= words ) {
        ADD_LK13(V2, V2, V4, 0x0);
        ADD_SK13(V3, V3, V4, 0x0);
        moved += 16;
        // return true;
    }

    // we need to guard against the last store
    const unsigned tail = (words - (words - (words%16)));

    // we need to overwrite V3 (the output pointer)
    // with the garbage row to protect the tail (the fractional)
    // end of the row that we dont want to write
    // we do this by calculating how many bits we need to set
    // (same as tail)
    // and then skewing the bits (rotate right) by the output skew

    uint16_t tail_pred = grow_bits_16(((tail+head)%16));

    tail_pred = ror16(tail_pred, delta_skew);

    // we also (need?) to apply the same skew to the garbage address
    // so we use the same technique we used on V3, here.
    // then we selectivly overwrite the tail
    // Garbage row is in V13
    ADD_KNOP(V15, V13, V8);
    MV_KNOP(V3, V15, tail_pred);

    VNOP_LK13(V2);
    VNOP_SK13(V3);


    return true;
}



/// interleave copy repeat
/// Copies memory from two source vectors into
/// one destination vector with ability to choose source a or b samplewise
/// passing
///
/// arg1 input row, 16 only
/// arg2 input row, 16 only
/// arg3 output row, will be rows long
/// predicate, the pattern to copy them in
///   bit position set to 1 will copy from a, set to 0 will copy from b
void vmem_interleave_copy_repeat(const unsigned int input_row_a, const unsigned int input_row_b, const unsigned int output_row, const unsigned int rows, const unsigned int predicate){
    MVXV_KNOP(V2, input_row_a); // input address

    if( input_row_b > input_row_a ) {
        MVXV_KNOP(V6, input_row_b-input_row_a); // delta address
        ADD_KNOP(V2, V2, V6, predicate);
    } else {
        MVXV_KNOP(V6, input_row_a-input_row_b); // delta address
        SUB_KNOP(V2, V2, V6, predicate);
    }


    MVXV_KNOP(V3, output_row);
    MVXV_KNOP(V4, 0x1);

    for (unsigned int i = 0; i < rows; i++){
        VNOP_LK13(V2);
        VNOP_SK13(V3);
        // ADD_KNOP(V2, V2, V4, 0x0);
        ADD_KNOP(V3, V3, V4, 0x0);
    }
}
