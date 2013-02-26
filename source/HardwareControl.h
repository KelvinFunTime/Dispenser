#ifndef H_CONTROL
#define H_CONTROL

typedef struct soft_args
{
	//data that is controlled by gui goes here
    short pump_num;
    short size;
    short cup;
} soft_args;

extern void * enterControl(void *);
extern void initSystem(void);
extern void initServo(void);

#endif
