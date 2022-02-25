/*
 * Date: 25 Jul 2020
 * Author: Amjad Yousef Majid
 * Email : amjad.y.majid@gmail.com
 */

#ifndef SYSTEM_INCLUDE_MOTOR_H_
#define SYSTEM_INCLUDE_MOTOR_H_

#define SLEEP P3->OUT
#define POWER P2->OUT
#define DIRECTION P5->OUT

/** ------------motor_init------------
 *@brief : setup the connections between the MCU and the DC motors
 *@params: none
 *@return: none
 */
void motor_init(void);

/** ------------stop_motor------------
 *@brief : stop the two DC motors from spinning
 *@params: none
 *@return: none
 */
void motor_stop(void);

/** ------------motor_forward------------
 *@brief : move the robot forward on a straight line or curve.
 *@params: leftDutyCycle sets the duty cycle for the left motor.
 *@params: rightDutyCycle sets the duty cycle for the right motor.
 *@return: none
 */
void motor_forward(int32_t leftDutyCycle, int32_t rightDutyCycle);

/** ------------motor_right------------
 *@brief : make the robot do a hard right turn by spinning the motors in a 
 * 		   reversed direction
 *@params: leftDutyCycle sets the duty cycle of the left motor.
 *@params: rightDutyCycle sets the duty cycle of the right motor.
 *@return: none
 */
void motor_right(uint32_t leftDutyCycle, uint32_t rightDutyCycle);

/** ------------motor_left------------
 *@brief : make the robot do a hard left turn by spinning the motors in a 
 * 		   reversed direction
 *@params: leftDutyCycle sets the duty cycle of the left motor.
 *@params: rightDutyCycle sets the duty cycle of the right motor.
 *@return: none
 */
void motor_left(uint32_t leftDutyCycle, uint32_t rightDutyCycle);

/** ------------motor_backward------------
 *@brief : move the robot backward on a straight line or curve.
 *@params: leftDutyCycle sets the duty cycle for the left motor.
 *@params: rightDutyCycle sets the duty cycle for the right motor.
 *@return: none
 */
void motor_backward(uint32_t leftDutyCycle, uint32_t rightDutyCycle);

#endif /* SYSTEM_INCLUDE_MOTOR_H_ */

