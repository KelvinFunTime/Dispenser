#ifndef PORTIO
#define PORTIO

#include "PortIO_Thread.h"

static port_args cup_args;

extern void init_cup_pins( pthread_t * t, short & cup_data, short & drink_size, short & pump_sel );
extern void init_cup_service();
extern void set_cup_data( short cup_data );
extern void set_drink_size( short drink_size );
extern void set_pump_sel( short pump_sel );
extern void get_cup_data( short cup_data );

#endif