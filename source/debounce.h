#ifndef DEBOUNCE_H
#define DEBOUNCE_H

#include <wiringPi.h>
#include "defs.h"

int debounce (int button, int button_debounce_length, int direction);

#endif