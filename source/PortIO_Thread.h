#ifndef PORTIO
#define PORTIO

struct port_args
{
	short * data;
	short * drink_size;
	short * pump_sel;
	int deb_length
	short pin_num;
};

extern void service_thread(port_args Args);
extern void pump_pwm( short pin_num, short * time, short * pwm, short * data );

#endif