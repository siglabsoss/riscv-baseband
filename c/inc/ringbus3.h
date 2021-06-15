#ifndef __RINGBUS3_H__
#define __RINGBUS3_H__



/// New idea for organizing / anonymizing fpgas
/// Put the _ADDR_ version on the rhs of these
/// This allows us to move blocks around later on

#define RING_ADDR_TX_0 RING_ADDR_CS11
#define RING_ADDR_TX_1 RING_ADDR_CS12
#define RING_ADDR_TX_2 RING_ADDR_CS02
#define RING_ADDR_TX_3 RING_ADDR_CS01

/// This covers:
///   feedback_bus_parse
///   userdata / userdata buffering
///   schedule and schedule updates, lifetime32, tickle progress
///   TDMA
#define RING_ADDR_TX_PARSE RING_ADDR_TX_0

/// This covers:
///   Tx eq
///   Eq hash / any feedback
///   SFO rotation of EQ subcarriers
#define RING_ADDR_TX_EQ RING_ADDR_TX_0

/// This covers:
///   FFT
///   FFT Barrelshift
///   CP
#define RING_ADDR_TX_FFT RING_ADDR_TX_1


/// This covers:
///   Things after the tx fft, mainly
///   CFO
///   Residue Phase
///   SFO/STO sample dropping
#define RING_ADDR_TX_TIME_DOMAIN RING_ADDR_TX_1





#define RING_ADDR_RX_0 RING_ADDR_CS31
#define RING_ADDR_RX_1 RING_ADDR_CS32
#define RING_ADDR_RX_2 RING_ADDR_CS22
#define RING_ADDR_RX_3 RING_ADDR_CS21
#define RING_ADDR_RX_4 RING_ADDR_CS20


/// This covers:
///   Coarse Sync
///   CP Removal
///   sample adjust aka turnstile
///   FFT
///   FFT Barrelshift
#define RING_ADDR_RX_FFT RING_ADDR_RX_0

/// This covers:
///   Calculation of fine sync
///   Loading fine sync into trunk
///   RX side ook demodulation
#define RING_ADDR_RX_FINE_SYNC RING_ADDR_RX_1

/// This covers:
///   various modes of 1/x magnitude
///   Loading cfo into trunk
#define RING_ADDR_RX_EQ RING_ADDR_RX_2

/// This covers:
///   Running rx mover in software
///   Loading custom SC into output of mover
#define RING_ADDR_RX_MOVER RING_ADDR_RX_4

/// This covers:
///   Tagging feedback bus types
///   Deciding what tags to send when
///   Enabling the slicer for specific tag types
#define RING_ADDR_RX_TAGGER RING_ADDR_RX_4




#endif