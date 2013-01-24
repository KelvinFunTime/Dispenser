/****************************************************************************************
*Pseudo Code:
*
*main_thread.c
*
*Create four threads (cup sensing, button sensing, pump controller, and servo controller)
*
*while ( 1 )
*	wait for input from cup or button threads
*	reply to threads as appropriate
*	perform menu changes if needed
*	send commands to pump controller if the program is ready
*	send commands to servo controller if the program is ready
*	break if finished or debug exit
*send kill commands
*return
*
*****************************************************************************************/

#include <stdio.h>
#include <wiringPi.h>
#include <stdlib.h>
#include <stdint.h>