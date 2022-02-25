/*
 * controller.h
 *
 *  Created on: 25 Sep 2020
 *      Author: Amjad yousef Majid
 */

#include <stdint.h>

#ifndef BEHAVIORS_INCLUDE_CONTROLLER_H_
#define BEHAVIORS_INCLUDE_CONTROLLER_H_

//select whether ir (i) or us (u) sensors are used for the robot
extern char sensor_type;

void controller_init(float x_g, float y_g, differential_robot_t *robot_pt, uint32_t p, uint8_t *goal_flag);

#endif /* BEHAVIORS_INCLUDE_CONTROLLER_H_ */
