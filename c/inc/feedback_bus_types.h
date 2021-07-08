#ifndef __FEEDBACK_BUS_TYPES__
#define __FEEDBACK_BUS_TYPES__

// zero is flushing
#define FEEDBACK_TYPE_FLUSH (0)
#define FEEDBACK_TYPE_STREAM (1)
#define FEEDBACK_TYPE_VECTOR (2)
#define FEEDBACK_TYPE_RINGBUS (3)
#define FEEDBACK_TYPE_UNJAM (4)


// omitting 0 as a value because this will make it easier
// to catch errors
#define FEEDBACK_VEC_FINE_SYNC (1)
#define FEEDBACK_VEC_TX_EQ     (2)
#define FEEDBACK_VEC_SCHEDULE  (3)
#define FEEDBACK_VEC_SCHEDULE_META  (4)
#define FEEDBACK_VEC_TX_USER_DATA (5)
#define FEEDBACK_VEC_DEMOD_DATA (6)
#define FEEDBACK_VEC_STATUS_REPLY (7)
#define FEEDBACK_VEC_TRANSPORT_RB (9)
#define FEEDBACK_VEC_INVOKE_USER_DATA (10)   // NOT USED or HANDLED
#define FEEDBACK_VEC_DELIVER_FSM_EVENT (11)
#define FEEDBACK_VEC_UPLINK (12)
#define FEEDBACK_VEC_FLUSH (13)
#define FEEDBACK_VEC_AIR (14)
#define FEEDBACK_VEC_PACKET_HASH (15)
#define FEEDBACK_VEC_REQ_RETRANSMIT (16)
#define FEEDBACK_VEC_REQUEST_ID (17)
#define FEEDBACK_VEC_REPLY_ID (18)
#define FEEDBACK_VEC_JS_ARB (19)
#define FEEDBACK_VEC_FETCH_REQUEST (20)
#define FEEDBACK_VEC_FETCH_REPLY (21)
#define FEEDBACK_VEC_JOINT_TRANSMIT (22)
#define FEEDBACK_VEC_JOINT_ACK (23)
#define FEEDBACK_VEC_WORDS_CORRECT (24)
#define FEEDBACK_VEC_EQ_ANALOG (25)         // Caught by fb_eq_split
#define FEEDBACK_VEC_EQ_CORRECTION  (26)         // Caught by fb_eq_split
#define FEEDBACK_VEC_JS_INTERNAL (27)

#define FEEDBACK_STREAM_DEFAULT (1)
#define FEEDBACK_STREAM_ALL_SC (2)


#define FEEDBACK_MAPMOV_QPSK (0)
#define FEEDBACK_MAPMOV_QAM8 (1)
#define FEEDBACK_MAPMOV_QAM16 (2)
#define FEEDBACK_MAPMOV_QAM32 (3)
#define FEEDBACK_MAPMOV_QAM64 (4)
#define FEEDBACK_MAPMOV_QAM128 (5)






#endif
