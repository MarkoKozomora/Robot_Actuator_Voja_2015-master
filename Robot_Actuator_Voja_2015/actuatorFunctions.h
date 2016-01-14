#ifndef ACTUATORFUNCTIONS_H_
#define ACTUATORFUNCTIONS_H_

#include "can.h"

void knockDownTheClapperboards(signed char side, signed char state);
void colectThePopcorn(signed char side, signed char state);
void leftDiafram(signed char state);
void rightDiafram(signed char state);
void liftStates(signed char state);
void action(canMsg msg);

#endif