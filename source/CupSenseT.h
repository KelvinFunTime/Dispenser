#ifndef PORTIO
#define PORTIO

#include "PortIO_Thread.h"
#include <pthread.h>

extern void init_cup_pins( pthread_t * t );
extern void init_cup_service();
extern void set_cup_data( short cup_data );
extern void set_drink_size( short drink_size );
extern void set_pump_sel( short pump_sel );
extern short get_cup_data();

#endif