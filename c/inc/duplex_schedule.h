#ifndef __DUPLEX_SCHEDULE_H__
#define __DUPLEX_SCHEDULE_H__

#include <stdint.h>
#include <stdbool.h>


#define DUPLEX_ROLE_RX   0
#define DUPLEX_ROLE_TX_0 1
#define DUPLEX_ROLE_TX_1 2
#define DUPLEX_ROLE_TX_2 3
#define DUPLEX_ROLE_TX_3 4

#define DUPLEX_FRAMES (128)

#define DUPLEX_SEND_ZERO          (0)   // _
#define DUPLEX_SEND_DL_PILOT_0    (1)   // p
#define DUPLEX_SEND_DL_PILOT_1    (2)   // q
#define DUPLEX_SEND_DL_PILOT_2    (3)   // r
#define DUPLEX_SEND_DL_PILOT_3    (4)   // s
#define DUPLEX_SEND_DL_DATA       (5)   // d
#define DUPLEX_SEND_UL_PILOT      (6)   // P
#define DUPLEX_SEND_UL_FINESYNC   (7)   // S
#define DUPLEX_SEND_UL_DATA       (8)   // D
#define DUPLEX_SEND_UL_FEEDBACK_0 (9)   // F
#define DUPLEX_SEND_UL_FEEDBACK_1 (10)  // G
#define DUPLEX_SEND_UL_FEEDBACK_2 (11)  // H
#define DUPLEX_SEND_UL_FEEDBACK_3 (12)  // I
#define DUPLEX_SEND_DL_BEAM_PILOT (13)  // i


#define DUPLEX_B0 (4)    // boundary 0
#define DUPLEX_B1 (41)   // boundary 1

#define DUPLEX_ULFB_START (DUPLEX_B0+15)
#define DUPLEX_ULFB_END   (DUPLEX_ULFB_START+4)

#define DUPLEX_START_FRAME_TX (DUPLEX_B1+2)
#define DUPLEX_START_FRAME_RX (DUPLEX_B0+3)

typedef struct duplex_timeslot_t {
    uint32_t role;
    uint32_t lt_period;
    uint32_t lt_phase;
    uint32_t lt_target;
    uint32_t lifetime_p;
    bool lt_target_valid;
} duplex_timeslot_t;

uint32_t get_duplex_mode(duplex_timeslot_t* const dts, const uint32_t i, const uint32_t lifetime);
bool duplex_should_forward_eq_data(const duplex_timeslot_t* const dts, const uint32_t i, const uint32_t cooked_data_type);
bool duplex_do_not_rotate(const duplex_timeslot_t* const dts, const uint32_t i, const uint32_t cooked_data_type, const uint32_t extra);
int32_t duplex_ul_feedback_phase(const uint32_t i);
int32_t duplex_ul_pilot_phase(const uint32_t i);
int32_t duplex_dl_pilot_transmitter(const uint32_t i);
bool duplex_do_userdata(const duplex_timeslot_t* const dts, const uint32_t i, bool flip);
bool duplex_tag_section(const uint32_t i, const uint32_t tag);
bool duplex_calculate_phase(duplex_timeslot_t* const dts, const uint32_t lifetime);
void init_duplex(duplex_timeslot_t* const dts, const uint32_t role);
void update_duplex_role(duplex_timeslot_t* const dts);
uint32_t duplex_fft_set_for_mode(const duplex_timeslot_t* const role, const uint32_t mode);
int32_t duplex_dl_pilot_phase(const uint32_t i);
int32_t duplex_dp_pilot_phase_individual(const duplex_timeslot_t* const dts, const uint32_t i);
int32_t duplex_dl_beam_pilot_phase(const uint32_t i);
uint32_t duplex_start_data_for_role(const duplex_timeslot_t* const dts);
uint32_t duplex_next_frame(const uint32_t lifetime, const uint32_t sf);
uint32_t duplex_duty_per_radio(const duplex_timeslot_t* const dts, const bool flip);
void duplex_build_tx_map(const duplex_timeslot_t* const dts, bool* const map, const bool flip);
uint32_t duplex_duty_frame_done(const uint32_t start, const uint32_t duration, const bool* const map);
bool duplex_narrowband_move(const duplex_timeslot_t dts, const uint32_t lifetime_32);

extern const unsigned duplex_partial_pilot[20];
extern const unsigned duplex_partial_pilot_rx[20];

#endif
