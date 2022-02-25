/*
 * vectorTranslation.c
 *
 *  Created on: 28 Sep 2020
 *      Author: Amjad Yousef Majid
 */

#include <stdint.h>
#include <math.h>

#include "vectorTranslation.h"

// convert the sensor measurement to the robot frame of reference
vector_2d convert2rf(float x_s, float y_s, float theta, uint32_t sensor_distance)
{
    vector_2d sensor_vec;
    sensor_vec.x = cos(theta) * sensor_distance + x_s;
    sensor_vec.y = sin(theta) * sensor_distance + y_s;

    return sensor_vec;
}

// convert to the world frame of reference
vector_2d convert2wf(vector_2d robot_sensor, float x_r, float y_r, float theta)
{

    vector_2d robot_vec;

    robot_vec.x = cos(theta) * robot_sensor.x - sin(theta) * robot_sensor.y + x_r;
    robot_vec.y = sin(theta) * robot_sensor.x + cos(theta) * robot_sensor.y + y_r;

    return robot_vec;
}
