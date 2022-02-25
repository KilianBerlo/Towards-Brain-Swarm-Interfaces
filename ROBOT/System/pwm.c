/**
 *@brief:  low level DC motor power control
 *@Date:   14 May 2020
 *@Author: Amjad Yousef Majid
 */

#include <stdint.h>
#include "msp.h"
#include "pwm.h"

/** ------------pwm_init------------
 * Assuming the MCLK=48MHz which causes SMCLK=12MHz
 * Timer_A counts up to the `period` (TA0CCR0) and down to zero. 
 * Output signal is toggled when Timer_A matches the duty cycle (TA0CCR3 or TA0CCR4).
 * The PWM signals are output on P2.6 and P2.7
 * Inputs: period is the period of the wave
 *         dutyCycle is the fraction of one period in which a signal or system is active
 * Outputs: none
 */
void pwm_init(uint32_t period, uint32_t dutyCycle)
{
    if (dutyCycle >= period)
        return; //invalid duty cycles

    // selecting timer functionality 
    P2->SEL0 |= (BIT6 + BIT7 );
    P2->SEL1 &= ~(BIT6 + BIT7 );
    //makes it output
    P2->DIR |= (BIT6 + BIT7 );

    // configure Timer_A0 counter
    TIMER_A0->CCTL[0] = 0x0080;  				        //CCI0 toggle (has no effect)
    TIMER_A0->CCR[0] = period;
    TIMER_A0->EX0 = 0x0000;  				            //divide by 1

    // configure capturer and control submodules 3 and 4
    TIMER_A0->CCTL[3] = TIMER_A_CCTLN_OUTMOD_2; 		//CCR3 toggle/reset
    LEFT_MOTOR_POWER= dutyCycle;
    TIMER_A0->CCTL[4] = TIMER_A_CCTLN_OUTMOD_2;  		//CCR4 toggle/reset
    RIGHT_MOTOR_POWER= dutyCycle;

    TIMER_A0->CTL = TIMER_A_CTL_MC__UPDOWN | TIMER_A_CTL_ID__8 | TIMER_A_CTL_SSEL__SMCLK;
}

/** ------------set_left_duty_cycle------------
 * Sets the duty cycle for the left motor
 * Inputs: dutyCycle is the fraction of one period in which the left motor should be active
 * Outputs: none
 */
void set_left_duty_cycle(uint32_t dutyCycle)
{
    if (dutyCycle >= PWM_SIGNAL_PERIOD) return; //invalid duty cycles
    LEFT_MOTOR_POWER = dutyCycle;
}

/** ------------set_right_duty_cycle------------
 * Sets the duty cycle for the right motor
 * Inputs: dutyCycle is the fraction of one period in which the right motor should be active
 * Outputs: none
 */
void set_right_duty_cycle(uint32_t dutyCycle)
{
    if (dutyCycle >= PWM_SIGNAL_PERIOD) return; //invalid duty cycles
    RIGHT_MOTOR_POWER = dutyCycle;
}
