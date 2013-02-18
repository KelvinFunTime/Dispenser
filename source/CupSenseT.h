#ifndef PORTIO
#define PORTIO

static short * ptr_cup_data;
static short * ptr_drink_size;
static short * ptr_pump_sel;

extern void init_cup_pins( pthread_t * t, short & cup_data, short & drink_size, short & pump_sel );
extern void init_cup_service( short & cup_data, short & drink_size, short & pump_sel );
extern void set_cup_data( short cup_data );
extern void set_drink_size( short drink_size );
extern void set_pump_sel( short pump_sel );



#endif