/*
 * Date  : 25 Jul 2020
 * Author: Amjad Yousef Majid
 * Email : amjad.y.majid@gmail.com
 */

#ifndef SYSTEM_INCLUDE_TIMER_A1_H_
#define SYSTEM_INCLUDE_TIMER_A1_H_

/** -------------- TimerA1_Init ---------------
 * Initialize Timer A1 to run user task periodically
 * Inputs:  task is a pointer to a user define function
 *          period specifies the interrupt frequency (every period/SMCLK sec)
 * Outputs: none
 */
void timerA1_init(void (*task)(void), uint32_t period);

/** --------------timerA1_stop---------------
 * Deactivate the interrupt running a user task periodically.
 * Inputs: none
 * Outputs: none
 */
void timerA1_stop(void);

#endif /* SYSTEM_INCLUDE_TIMER_A1_H_ */
