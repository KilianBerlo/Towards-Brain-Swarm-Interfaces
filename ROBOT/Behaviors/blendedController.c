/*
 * blendingController.c
 *
 *  Created on: 28 Sep 2020
 *      Author: Amjad Yousef Majid
 */

#include <math.h>
#include <stdint.h>

#include "vectorTranslation.h"
#include "differentialRobot.h"
#include "motor.h"

extern void duty_check(int32_t *left_duty_cycle, int32_t *right_duty_cycle);

extern float _x_goal;
extern float _y_goal;
extern differential_robot_t *_robot;
extern uint32_t linear_velocity;
extern int32_t left_duty_cycle;
extern int32_t right_duty_cycle;

#define LEN_BC_DEBUG 300
uint16_t cntr_bc_debug = 0;

uint32_t sensor_left_bc[LEN_BC_DEBUG] = { 0 };
uint32_t sensor_right_bc[LEN_BC_DEBUG] = { 0 };
vector_2d left_sensor_rf;
vector_2d center_sensor_rf;
vector_2d right_sensor_rf;

double static E_i = 0;
float static K_i = 2.6;
float static K_p = 330;

void blended_controller()
{
    // 90 degress in radians is 0.785
    left_sensor_rf = convert2rf(50, 50, 0.785, _robot->sensor_distances->sensor_left);
    center_sensor_rf = convert2rf(70, 0, 0, _robot->sensor_distances->sensor_center);
    right_sensor_rf = convert2rf(50, -50, -0.785, _robot->sensor_distances->sensor_right);

    vector_2d left_sensor_wf = convert2wf(left_sensor_rf, _robot->pose->x, _robot->pose->y, _robot->pose->theta);
    vector_2d center_sensor_wf = convert2wf(center_sensor_rf, _robot->pose->x, _robot->pose->y, _robot->pose->theta);
    vector_2d right_sensor_wf = convert2wf(right_sensor_rf, _robot->pose->x, _robot->pose->y, _robot->pose->theta);

    float x_dir = left_sensor_wf.x + right_sensor_wf.x + center_sensor_wf.x;
    float y_dir = left_sensor_wf.y + right_sensor_wf.y + center_sensor_wf.y;

    float x_o = x_dir - _robot->pose->x;
    float y_o = y_dir - _robot->pose->y;

    float x_g = _x_goal - _robot->pose->x;
    float y_g = _y_goal - _robot->pose->y;

    // vector normalization
    float denominator = sqrt((x_o * x_o) + (y_o * y_o));
    float x_o_n = x_o / denominator;
    float y_o_n = y_o / denominator;

    denominator = sqrt((x_g * x_g) + (y_g * y_g));
    float x_g_n = x_g / denominator;
    float y_g_n = y_g / denominator;

    float alpha = 0.3;

    x_dir = alpha * x_g_n + (1 - alpha) * x_o_n;
    y_dir = alpha * y_g_n + (1 - alpha) * y_o_n;

    float theta_g = atan2(y_dir, x_dir);

    float heading_error = theta_g - _robot->pose->theta;
    float err = atan2(sin(heading_error), cos(heading_error));

    E_i += err;
    float U_i = (K_i * E_i);
    float U_p = (K_p * err);
    float w = U_p + U_i;

    left_duty_cycle = (linear_velocity - w * 14) / 7;
    right_duty_cycle = (linear_velocity + w * 14) / 7;

    duty_check(&left_duty_cycle, &right_duty_cycle);

    motor_forward(right_duty_cycle, left_duty_cycle);
    robot_position_update(_robot);
}

