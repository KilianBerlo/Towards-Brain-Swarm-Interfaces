/*
 * Date  : 25 Jul 2020
 * Author: Amjad Yousef Majid
 * Email : amjad.y.majid@gmail.com
 */

#ifndef SYSTEM_INCLUDE_INTERRUPTHANDLER_H_
#define SYSTEM_INCLUDE_INTERRUPTHANDLER_H_

void disableInterrupts(void);

void enableInterrupts(void);

// save the interrupt status and then disable interrupts
// this function returns a value, PRIMASK register, through R0
long startCritical(void);

// restore the interrupt status and enable interrupts
// this function takes an argument through R0 to restore the state of the PRIMASK register
void endCritical(long);

void waitForInterrupt(void);

#endif /* SYSTEM_INCLUDE_INTERRUPTHANDLER_H_ */
