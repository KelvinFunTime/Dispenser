#ifndef PORTIO
#define PORTIO

typedef struct port_args
{
	short data;
	short drink_size;
	short pump_sel;
	short pin_num;
	int deb_length;
} port_args;

extern void * service_thread(void * args);
extern void pump_pwm( short pin_num, short * time, short * pwm, short * data );

#endif