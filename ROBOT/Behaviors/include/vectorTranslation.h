/*
 * vectorTranslation.h
 *
 *  Created on: 28 Sep 2020
 *      Author: Amjad Yousef Majid
 */

#include <stdint.h>

#ifndef BEHAVIORS_INCLUDE_VECTORTRANSLATION_H_
#define BEHAVIORS_INCLUDE_VECTORTRANSLATION_H_

typedef struct
{
    float x;
    float y;
} vector_2d;

//vector_2d convert2rf(float x_s, float y_s, float theta, uint32_t ir_distance);
vector_2d convert2rf(float x_s, float y_s, float theta, uint32_t us_distance);
vector_2d convert2wf(vector_2d robot_sensor, float x_r, float y_r, float theta);

#endif /* BEHAVIORS_INCLUDE_VECTORTRANSLATION_H_ */
