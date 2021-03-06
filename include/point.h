/**
 * @file point.h
 * @author Anshul Kamath
 * @brief An point library
 * @version 0.1
 * @date 2022-04-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef POINT_H
#define POINT_H

#include <assert.h>
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

#define _PT_HELPER_3(dest, src, count) \
    _PT_HELPER_4(dest, src, CONCAT(_x_int, count), CONCAT(_y_int, count))

#define _PT_HELPER_4(dest, src, x_id, y_id) \
    big_uint_t x_id, y_id; \
    big_uint_create(&x_id, (src)->x->len); \
    big_uint_create(&y_id, (src)->y->len); \
    big_uint_copy(&x_id, (src)->x); \
    big_uint_copy(&y_id, (src)->y); \
    point_init(dest, &x_id, &y_id);

#define _PT_HELPER_5(dest, size, count) \
    _PT_HELPER_6(dest, size, CONCAT(_x_int, count), CONCAT(_y_int, count))

#define _PT_HELPER_6(dest, size, x_id, y_id) \
    big_uint_t x_id, y_id; \
    big_uint_create(&x_id, (size)); \
    big_uint_create(&y_id, (size)); \
    point_init(dest, &x_id, &y_id);

/****************************************/
/*             INIT MACROS              */
/****************************************/

#define point_load(dest, x_str, y_str) \
    _PT_HELPER_1(dest, x_str, y_str, __COUNTER__)

/* Copies into an unintialized point_t */
#define point_copyi(dest, src) \
    _PT_HELPER_3(dest, src, __COUNTER__)

#define point_create(dest, size) \
    _PT_HELPER_5(dest, size, __COUNTER__)

/****************************************/
/*              INTERFACE               */
/****************************************/

typedef struct point {
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

/**
 * @brief Returns 1 or 0 if p1 == p2 or not (respectively)
 * 
 * @param p1 The first point to compare
 * @param p2 The second point to compare
 * @return uint8_t 
 */
uint8_t point_equals(const point_t *p1, const point_t *p2);

/**
 * @brief Copies the contents of `src` to `dest`.
 * NOTE:  `dest` must be initialized. If it is not, consider using `point_copyi`,
 *        but note that this initializes a point ONLY in the current stack frame
 * 
 * @param dest  An initialized point where we can store the `src` point
 * @param src   A pointer to the point we want to copy
 */
void point_copy(point_t *dest, const point_t *src);

/**
 * @brief Returns true if and only if the point `p` is identity (0, 0)
 * 
 * @param p The point `p` to check
 * @return uint8_t 
 */
uint8_t point_is_identity(const point_t *p);

/**
 * @brief Returns a constant pointer to the identity element
 * 
 * @return point_t* 
 */
const point_t* point_get_identity();

#endif
