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

/****************************************/
/*            HELPER MACROS             */
/****************************************/

#define _PT_HELPER_1(dest, x_str, y_str, count) \
    _PT_HELPER_2(dest, x_str, y_str, CONCAT(_x_int, count), CONCAT(_y_int, count))

#define _PT_HELPER_2(dest, x_str, y_str, x_id, y_id) \
    big_uint_t x_id, y_id; \
    big_uint_load(&x_id, x_str); \
    big_uint_load(&y_id, y_str); \
    point_init(dest, &x_id, &y_id);

/****************************************/
/*             INIT MACROS              */
/****************************************/

#define point_create(dest, x_str, y_str) \
    _PT_HELPER_1(dest, x_str, y_str, __COUNTER__)

/****************************************/
/*              INTERFACE               */
/****************************************/

typedef struct {
    big_uint_t *x;
    big_uint_t *y;
} point_t;

/****************************************/
/*          POINT DEFINITIONS           */
/****************************************/

/**
 * @brief Initializes a point type using the given coordinates
 * 
 * @param dest  A pointer to the point to populate
 * @param x     A pointer to the x coordinate to use
 * @param y     A pointer to the y coordinate to use
 */
void point_init(point_t *dest, big_uint_t *x, big_uint_t *y);

/**
 * @brief Prints the given point to stdout
 * 
 * @param pt A pointer to the point to print
 */
void point_print(const point_t *pt);

#endif
