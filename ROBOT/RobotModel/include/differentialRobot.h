/*
 * Date  : 25 Jul 2020
 * Author: Amjad Yousef Majid
 * Email : amjad.y.majid@gmail.com
 */

#include <stdint.h>

#ifndef DATASTRUCTURE_INCLUDE_ROBOT_H_
#define DATASTRUCTURE_INCLUDE_ROBOT_H_


#define RADIUS .035                    // wheel radius in meter
#define TICKS_PER_REV 360              // ticks per wheel revolution
#define BASE_LENGTH .14                          // distance between the two wheels in meter
// define the distance per tick as a numerator and denominator
// wheel radius in meter is 0.035 meters
// one revolution takes the wheel 360 ticks
// 0.035 * 2 * pi / 360 = 0.00061
#define TICK_DIS_NUMERATOR 61          // to avoid float operation split the fraction
#define TICK_DIS_DENOMINATOR 100000    // consequently you must multiply and then divide

#define ULTRASOUND 1 // 1 if the robot has ultrasound sensors 0 if it has infrared sensors

typedef struct sensor_distances
{
    uint32_t sensor_left;
    uint32_t sensor_center;
    uint32_t sensor_right;
} sensor_distances_t;


typedef struct tachometer
{
    volatile float delta_dis;     // distance crossed between to updates in meter
    volatile int32_t ticks;
    volatile int32_t prev_ticks;
} tachometer_t;

typedef struct pose
{
    volatile float x;
    volatile float y;
    volatile double theta;
} pose_t;

typedef struct wheel
{
    uint32_t dis_per_tick_numerator;
    uint32_t dis_per_tick_denominator;
    tachometer_t *tachometer;
} wheel_t;

typedef struct differential_robot
{
    float base_len;  // the distance between the two wheels in meters
    sensor_distances_t *sensor_distances;
    pose_t *pose;
    wheel_t *right;
    wheel_t *left;
} differential_robot_t;

differential_robot_t* robot_init();
void robot_position_update(differential_robot_t *robot);

#endif /* DATASTRUCTURE_INCLUDE_ROBOT_H_ */
