/***************************************************************
* Header for #defines and other macros that may be needed in
* other files.
*
*
****************************************************************/

//Calculated debounce for button and cup
#define USER_PRESS_DEBOUNCE_LENGTH	437500	// needs to be in seconds!
#define CUP_SENSE_DEBOUNCE_LENGTH 	10000 // 10 ms
#define PI_CLOCK 					700000000

//Number of pins available on the RPI
#define	NUM_PINS 	17

//Pins
#define CUP_PIN_1 	0
#define CUP_PIN_2	6
#define CUP_PIN_3	3

#define PUMP_PIN_1	4
#define PUMP_PIN_2	5

//Pin modes available
#define	WPI_MODE_PINS		 0
#define	WPI_MODE_GPIO		 1
#define	WPI_MODE_GPIO_SYS	 2
#define	WPI_MODE_PIFACE		 3

//Pin I/O settings available
#define	INPUT		0
#define	OUTPUT		1
#define	PWM_OUTPUT	2

//Pin output levels
#define	LOW		 	0
#define	HIGH		1

//Pin pull up and down registers for voltages
#define	PUD_OFF		0
#define	PUD_DOWN	1
#define	PUD_UP		2

//Pin PWM modes
#define	PWM_MODE_MS		0
#define	PWM_MODE_BAL	1