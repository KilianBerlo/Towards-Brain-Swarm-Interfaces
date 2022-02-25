/**
 * Date  : 25 Jul 2020
 * Author: Amjad Yousef Majid
 * Email : amjad.y.majid@gmail.com
 */

#ifndef SYSTEM_INCLUDE_TACHOMETER_H_
#define SYSTEM_INCLUDE_TACHOMETER_H_

#define TACHOLEFT BIT5
#define TACHORIGHT BIT4

/** ------------tachometer_init------------
 * Setup the connections between the MCU and the tachometers using interrupts.
 * Inputs: userTaskLeft is the task to perform when the left tachometer gives an interrupt.
           userTaksRight is the task to perform when the right tachometer gives an interrupt.
 * Outputs: none
 */
void tachometer_init(void (*userTaskLeft)(void), void (*userTaskRight)(void));

#endif /* SYSTEM_INCLUDE_TACHOMETER_H_ */
