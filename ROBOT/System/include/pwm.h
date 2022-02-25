/**
 * Date	 : 25 Jul 2020
 * Author: Amjad Yousef Majid
 * Email : amjad.y.majid@gmail.com
 */

#include <stdint.h>

#ifndef SYSTEM_INCLUDE_PWM_H_
#define SYSTEM_INCLUDE_PWM_H_

#define LEFT_MOTOR_POWER        TIMER_A0->CCR[3]
#define RIGHT_MOTOR_POWER       TIMER_A0->CCR[4]
#define PWM_SIGNAL_PERIOD       TIMER_A0->CCR[0]

/** ------------pwm_init------------
 * Sets up the pulse width modulation timer
 * Inputs: period is the period of the wave
 *         dutyCycle is the fraction of one period in which a signal or system is active
 * Outputs: none
 */
void pwm_init(uint32_t period, uint32_t dutyCycle);

/** ------------set_left_duty_cycle------------
 * Sets the duty cycle for the left motor
 * Inputs: dutyCycle is the fraction of one period in which the left motor should be active
 * Outputs: none
 */
void set_left_duty_cycle(uint32_t leftDutyCycle);

/** ------------set_right_duty_cycle------------
 * Sets the duty cycle for the right motor
 * Inputs: dutyCycle is the fraction of one period in which the right motor should be active
 * Outputs: none
 */
void set_right_duty_cycle(uint32_t rightDutyCycle);

#endif /* SYSTEM_INCLUDE_PWM_H_ */
