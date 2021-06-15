#include "handle_power.h"
#include "ringbus.h"
#include "sort.h"
#include "circular_buffer_pow2.h"
#include "my_assert.h"

#include "ringbus2_pre.h"
#define EXCLUDE_RINGBUS2_FUNCTIONS
#define RINGBUS2_FUNCTIONS_FOWARD_DECLARE
#include "ringbus2_post.h"

// we dont link math.h, we just include it
// this means we can call pow() at compile time, but not at runtime
// tricky
#include <math.h>



static power_thresh_t p_thresh[POWER_LEVELS_THRESHOLDS];
static uint64_t p_thresh_sorted[POWER_LEVELS_THRESHOLDS];
static uint8_t p_thresh_index[POWER_LEVELS_THRESHOLDS];
static unsigned p_thresh_valid = 0;
static unsigned active_power_index = 0xffffffff; // invalid initial value to force update

circular_buf_pow2_t __inject_ring_queue = CIRBUF_POW2_STATIC_CONSTRUCTOR(__inject_ring_queue, (COMMANDS_PER_POWER*2) );
circular_buf_pow2_t* inject_ring_queue = &__inject_ring_queue;


void pwr_initilize(void) {
    for(int i = 0; i < POWER_LEVELS_THRESHOLDS; i++) {
        p_thresh[i].low = 0;
        p_thresh[i].command[0] = 0;
    }

    CIRBUF_POW2_RUNTIME_INITIALIZE(__inject_ring_queue);
}

static void pwr_inject_ringbus( const power_thresh_t* const x ) {
    if( x == 0 ) {
        // cout << "pwr_inject_ringbus() illegal pointer\n";
        return; // illegal pointer
    }
    // unsigned ret = 0;
    for(unsigned i = 0; i < COMMANDS_PER_POWER; i++) {
        const uint32_t word = x->command[i];
        
        if( word == 0 ) {
            break;
        }

        
        const int ret = circular_buf2_put(inject_ring_queue, word);
        MY_ASSERT(ret != -1);
        
        // inject_ringbus(word);
    }
}

int __attribute__((optimize("Os"))) pwr_adjust_u64(const uint64_t pow_mag2) {
    // const uint64_t pow_mag2 = db;
    // cout << "Adjust in: (" << pow_mag2 << ")" << "\n";
    
    if( p_thresh_valid == 0 ) {
        // cout << "adjust_f() exiting, table is empty\n";
        return -1;
    }
    
    
    
    int match_index = -1;
    
    uint64_t val_p = 0; // should be negative enough
    for(unsigned i = 0; i < p_thresh_valid; i++) {
        const uint8_t lookup = p_thresh_index[i];
        const power_thresh_t* const x = p_thresh + lookup;
        const uint64_t val = x->low;
        
        // cout << "  " << val << "\n";
        
        if( val_p < pow_mag2 && pow_mag2 <= val ) {
            // match = x;
            match_index = lookup;
            // cout << "  match\n";
            break;
        }
        
        val_p = val;
    }
    
    if( match_index == -1 ) {
        // cout << "warning, using maximum value\n";
        match_index = p_thresh_index[p_thresh_valid-1];
        // match = p_thresh + p_thresh_valid-1;
    }

    if( (unsigned)match_index == active_power_index) {
        return -1; // do nothing, we are already in the correct power bracket
    }

    
    
    const power_thresh_t* const match = p_thresh + match_index;

    pwr_inject_ringbus(match);

    active_power_index = match_index;
    
    return match_index;
}

void pwr_invalidate_current(void) {
    active_power_index = 0xffffffff;
}

// void print_power( const power_thresh_t* const x ) {
//     cout << "low: " << x->low << "\n";
//     for(int i = 0; i < POWER_LEVELS_THRESHOLDS; i++) {
//         uint32_t cmd = x->command[i];
        
//         if( cmd == 0 ) {
//             break;
//         }
        
//         cout << "  cmd " << i << ": " << HEX32_STRING(cmd) << "\n";
//     }
// }

static bool __attribute__((optimize("Os"))) pwr_entry_valid( const power_thresh_t* const x ) {
    if( x == 0 ) {
        // cout << "pwr_entry_valid() illegal pointer\n";
        return false; // illegal pointer
    }
    uint32_t cmd0 = x->command[0];
    return cmd0 != 0;
}

static unsigned __attribute__((optimize("Os"))) pwr_entry_length( const power_thresh_t* const x ) {
    if( x == 0 ) {
        // cout << "pwr_entry_length() illegal pointer\n";
        return 0; // illegal pointer
    }
    unsigned ret = 0;
    for(int i = 0; i < COMMANDS_PER_POWER; i++) {
        uint32_t cmd = x->command[i];
        
        if( cmd == 0 ) {
            break;
        }
        ret++;
    }
    return ret;
}

// call to set the global variable p_thresh_valid
static unsigned __attribute__((optimize("Os"))) valid_pwr_thresh(void) {
    unsigned ret = 0;
    bool finished = false;
    for(int i = 0; i < POWER_LEVELS_THRESHOLDS; i++) {
        // const unsigned length = pwr_entry_length(p_thresh + i);
        const bool valid = pwr_entry_valid(p_thresh + i);

        if( valid & !finished ) {
            ret++;
        } else {
            finished = true;
            // break;
        }
    }
    
    return ret;
}

// void print_all() {
//     for(int i = 0; i < POWER_LEVELS_THRESHOLDS; i++) {
//         print_power(p_thresh + i);
//     }
// }

void pwr_entry_each(const each_power_thresh_t cb) {
    if( cb == 0 ) {
        return;
    }

    for(uint32_t i = 0; i < p_thresh_valid; i++) {
        cb(i, p_thresh + i);
    }
}



// p_thresh_valid must be correct before you call this
void __attribute__((optimize("Os"))) pwr_update_index(void) {
    if( p_thresh_valid == 0 ) {
        return;
    }
    
    // load the array with the natural order
    for(unsigned i = 0; i < p_thresh_valid; i++) {
        p_thresh_sorted[i] = p_thresh[i].low;
        p_thresh_index[i] = i;
        // cout << "     " << p_thresh_sorted[i] << "\n";
    }
    
    selection_sort_parallel_u64_u8(p_thresh_sorted, p_thresh_index, p_thresh_valid);
    
    // for(unsigned i = 0; i < p_thresh_valid; i++) {
    //     cout << "       " << p_thresh_sorted[i] << "\n";
    //     cout << "       " << (unsigned)p_thresh_index[i] << "\n";
    // }
    
    // for(unsigned i = 0; i < p_thresh_valid; i++) {
    //     p_thresh_index
    // }
}

// always pass true to update_index, unless you are passing multiple in a row
// and in this case, call with false,false,...,true  where only the final entry is true
void __attribute__((optimize("Os"))) pwr_add_entry( const power_thresh_t* const x, const bool update_index ) {
    
    p_thresh_valid = valid_pwr_thresh();
    
    if( p_thresh_valid == 0 ) {
        p_thresh[0] = *x;
        p_thresh_valid = 1;
        if( update_index ) {
            pwr_update_index();
        }
        return;
    }
    
    uint64_t search = x->low;
    
    int existing = -1;
    
    for(int i = 0; i < POWER_LEVELS_THRESHOLDS; i++) {
        if( p_thresh[i].low == search ) {
            // cout << "    marked existing " << i << "\n";
            existing = i;
            break;
        }
    }
    
    if( existing != -1 ) {
        p_thresh[existing] = *x;
    } else {
        if( p_thresh_valid == POWER_LEVELS_THRESHOLDS ) {
            // cout << "  full, will not update\n";
            return;
        } else {
            // p_thresh_valid is a count, not an index
            // we want to
            const unsigned insert_at = p_thresh_valid;
            
            // cout << "    inserting at " << insert_at << "\n";
            
            p_thresh[insert_at] = *x;
            p_thresh_valid++;
        }
    }
    
    if( update_index ) {
        pwr_update_index();
    }
    
    
    
    
    // print_power(&x);
    // for(int i = 0; i < POWER_LEVELS_THRESHOLDS; i++) {
    //     cout << "i: " << i << "\n";
    // }
}


void pet_handle_pwr(void) {
    if( inject_ring_queue->occupancy > 0 ) {
        unsigned int word;
        circular_buf2_get(inject_ring_queue, &word);

        inject_ringbus(word);
    }
}
