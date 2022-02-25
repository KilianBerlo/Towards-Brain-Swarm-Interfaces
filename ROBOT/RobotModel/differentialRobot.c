/*
 * Date: 25 Jul 2020
 * Author: Amjad Yousef Majid
 * Email: amjad.y.majid@gmail.com
 */

#include "differentialRobot.h"
#include "ir_distance.h"
#include <math.h>
#include "UART1.h"
#define MAX_SENSOR 800 // max sensor distances in mm


// initialize the robot data structure
tachometer_t right_tachometer = { 0, 0, 0 };
tachometer_t left_tachometer = { 0, 0, 0 };
pose_t pose = { 0, 0, 0 };                      // initial position of the robot
sensor_distances_t sensor_distances = { MAX_SENSOR, MAX_SENSOR, MAX_SENSOR };

wheel_t right_wheel;
wheel_t left_wheel;
differential_robot_t robot;

differential_robot_t* robot_init()
{
    // initialize right wheel
    right_wheel.dis_per_tick_numerator = TICK_DIS_NUMERATOR;
    right_wheel.dis_per_tick_denominator = TICK_DIS_DENOMINATOR;
    right_wheel.tachometer = &right_tachometer;
    // initialize left wheel
    left_wheel.dis_per_tick_numerator = TICK_DIS_NUMERATOR;
    left_wheel.dis_per_tick_denominator = TICK_DIS_DENOMINATOR;
    left_wheel.tachometer = &left_tachometer;

    robot.base_len = BASE_LENGTH;
    robot.right = &right_wheel;
    robot.left = &left_wheel;
    robot.pose = &pose;
    robot.sensor_distances = &sensor_distances;

    return &robot;
}

float _robot_distance_update_mm(float d_r, float d_l)
{
    return (d_r + d_l) / 2;
}

void _wheel_distance_update_mm(wheel_t *wheel)
{
    // calculate the distance traveled since the last update
    int32_t ticks = wheel->tachometer->ticks;
    float delta_ticks = ticks - wheel->tachometer->prev_ticks;
    // update the previous tachometer ticks
    wheel->tachometer->prev_ticks = ticks;
    wheel->tachometer->delta_dis = (wheel->dis_per_tick_numerator * delta_ticks) / wheel->dis_per_tick_denominator;  //distance in meter
}

void robot_position_update(differential_robot_t *robot)
{
    _wheel_distance_update_mm(robot->right);
    _wheel_distance_update_mm(robot->left);

    float d_r = robot->right->tachometer->delta_dis;
    float d_l = robot->left->tachometer->delta_dis;
    float d_c = _robot_distance_update_mm(d_r, d_l);

    float x = robot->pose->x;
    float y = robot->pose->y;
    float theta = robot->pose->theta;

    x += d_c * cosf(theta);
    y += d_c * sinf(theta);
    float delta_theta = (float) (d_r - d_l) / robot->base_len;
    theta += delta_theta;

    robot->pose->x = x;
    robot->pose->y = y;
    robot->pose->theta = atan2f(sinf(theta), cosf(theta));
}
