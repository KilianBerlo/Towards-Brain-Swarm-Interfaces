/*
 * us_distance.h
 *
 *  Created on: 29 Oct 2021
 *      Author: Kilian van Berlo
 */

#include <stdint.h>

#ifndef SYSTEM_INCLUDE_US_DISTANCE_H_
#define SYSTEM_INCLUDE_US_DISTANCE_H_

void us_distances(uint32_t *left, uint32_t *center, uint32_t *right);
void ultrasound_init(void);

#endif /* SYSTEM_INCLUDE_US_DISTANCE_H_ */
