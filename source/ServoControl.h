#include <wiringPi.h>

/**********************************************************
*function_name:
*	pwm_control
*
*inputs:
*	short pos (defines how far the PWM will turn)
*outputs:
*	Changes where the servo motor has moved to
*
**********************************************************/
extern void pwm_control( short pos );