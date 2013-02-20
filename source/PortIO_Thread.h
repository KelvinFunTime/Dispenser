#ifndef PORTIO
#define PORTIO

typedef struct port_args
{
	short data;
	short drink_size;
	short pump_sel;
	int deb_length;
	short pin_num;
} port_args;

extern void service_thread(port_args * args);
extern void pump_pwm( short pin_num, short * time, short * pwm, short * data );

#endif