#ifndef HAL_H
#define HAL_H

#include <stdint.h>

/* map
 * x      : the value to map
 * in_min : the lowest value x can be
 * in_max : the highest value x can be
 * out_min: the lowest value of the output range
 * out_max: the highest value of the output range
 */
uint32_t map(uint32_t x, uint32_t in_min, uint32_t in_max, uint32_t out_min, uint32_t out_max);

#endif