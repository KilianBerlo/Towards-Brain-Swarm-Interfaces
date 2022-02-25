/*
 * irDistance.h
 *
 *  Created on: 29 Jul 2020
 *      Author: an
 */

#include <stdint.h>

#ifndef SYSTEM_INCLUDE_IRDISTANCE_H_
#define SYSTEM_INCLUDE_IRDISTANCE_H_

#define IR_MAX_DISTANCE 800             // maximum ir distance in mm

void ir_distances(uint32_t *left, uint32_t *center, uint32_t *right);
void read_adc_14_16_17(void);
void adc_init_channel_14_16_17(void);

#endif /* SYSTEM_INCLUDE_IRDISTANCE_H_ */
