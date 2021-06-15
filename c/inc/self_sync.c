#include "self_sync.h"
#include "ringbus.h"
#include "csr_control.h"
#include "bootloader.h"
#include "get_timer.h"

#define LEDON()  CSR_SET_BITS(GPIO_WRITE, LED_GPIO_BIT)
#define LEDOFF() CSR_CLEAR_BITS(GPIO_WRITE, LED_GPIO_BIT)


// forward declare.
void ring_block_send_eth(unsigned int data);

static unsigned int serve_ring_and_get_timer(void) {
    unsigned int occupancy;
    unsigned int word;
    unsigned int finished = 0;
    unsigned int type;
    unsigned int data;


    do {
        CSR_READ(RINGBUS_READ_OCCUPANCY, occupancy);

        if( occupancy == 0 ) {
            continue;
        }

        CSR_READ(RINGBUS_READ_DATA, word);

        type = (word)&TYPE_MASK;
        data = (word)&DATA_MASK;

        switch(type) {
            case RING_TEST_CMD:
                _ring_test(data);
                break;
            case BOOTLOADER_CMD:
                no_exit_bootload(data, 0);
                break;
            case CHECK_BOOTLOAD_CMD:
                ring_block_send_eth(CHECK_BOOTLOAD_PCCMD | OUR_RING_ENUM);
                break;
            case GET_TIMER_CMD:
                readback_timer_callback(data);
                break;
            case SELF_SYNC_CMD:
                finished = 1;
                break;
            default:
                break;
        }
        if( finished ) {
            break;
        }
    } while(1);

    return data << 8;
}


void self_sync_block_boot(void) {

    // setup gpio
    CSR_SET_BITS(GPIO_WRITE_EN, LED_GPIO_BIT);
    LEDOFF();
    
    const unsigned int wake_timer = serve_ring_and_get_timer();

    LEDON();

    unsigned int now;
    int delta;
    do {
        CSR_READ(TIMER_VALUE, now);
        delta = now - wake_timer;
    } while(delta < 0);
    LEDOFF();
}
