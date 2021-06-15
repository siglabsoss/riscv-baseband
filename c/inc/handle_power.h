#ifndef __HANDLE_POWER_H__
#define __HANDLE_POWER_H__

#include <stdint.h>
#include <stdbool.h>


#define POWER_LEVELS_THRESHOLDS (8)
#define COMMANDS_PER_POWER (16)

// #define POWER_DB_SHIFT (10)
// #define POWER_DB_MUL (1<<POWER_DB_SHIFT)


// picked at random by ben, but shared in s-modem and higgs_helper
#define FIXED_DB_REFERENCE ((double)30000.0f)

#define POW_DB_FROM_MAG2(x) (10*(log10(sqrt(x)/FIXED_DB_REFERENCE)))
#define POW_MAG2_FROM_DB(x) ((uint64_t)(pow(((pow(10.0f,(((double)x)/10.0)))*FIXED_DB_REFERENCE),2)))





typedef struct power_thresh_t {
    uint64_t low;
    uint32_t command[COMMANDS_PER_POWER];
} power_thresh_t;


typedef void (*each_power_thresh_t)(const uint32_t, const power_thresh_t* const x);


void pwr_initilize(void);
int  pwr_adjust_u64(const uint64_t pow_mag2);
void pwr_update_index(void);
void pwr_add_entry( const power_thresh_t* const x, const bool update_index );
void pet_handle_pwr(void);
void pwr_entry_each(const each_power_thresh_t cb);
void pwr_invalidate_current(void);



#endif
