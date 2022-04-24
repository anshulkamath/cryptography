/**
 * @file ec.h
 * @author Anshul Kamath
 * @brief An elliptic curve library
 * @version 0.1
 * @date 2022-04-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef EC_H
#define EC_H

#include "big-uint.h"

typedef struct {
    big_uint_t *x;
    big_uint_t *y;
} point_t;

/**
 * @brief Initializes a point type using the given coordinates
 * 
 * @param dest  A pointer to the point to populate
 * @param x     A pointer to the x coordinate to use
 * @param y     A pointer to the y coordinate to use
 */
void point_init(point_t *dest, big_uint_t *x, big_uint_t *y);

#endif
