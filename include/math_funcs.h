/**
 * Math Utility Functions
 */

#ifndef MATH_FUNCS_H
#define MATH_FUNCS_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Create logarithmically spaced array
 * @param n Number of points
 * @param min Minimum value
 * @param max Maximum value
 * @param array Output array (must be pre-allocated with size n)
 * @return 0 on success, 1 on error
 */
static inline int logspace_array(size_t n, double min, double max, double *array) {
    if (n == 0 || min <= 0 || max <= 0 || min >= max || array == NULL) {
        return 1;
    }
    
    double log_min = log10(min);
    double log_max = log10(max);
    double delta = (log_max - log_min) / (n - 1.0);
    
    for (size_t i = 0; i < n; i++) {
        array[i] = pow(10.0, log_min + i * delta);
    }
    
    return 0;
}

/**
 * Create linearly spaced array
 * @param n Number of points
 * @param min Minimum value
 * @param max Maximum value
 * @param array Output array (must be pre-allocated with size n)
 * @return 0 on success, 1 on error
 */
static inline int linspace_array(size_t n, double min, double max, double *array) {
    if (n == 0 || min >= max || array == NULL) {
        return 1;
    }
    
    if (n == 1) {
        array[0] = min;
        return 0;
    }
    
    double delta = (max - min) / (n - 1.0);
    
    for (size_t i = 0; i < n; i++) {
        array[i] = min + i * delta;
    }
    
    return 0;
}

/**
 * Find maximum value in array
 * @param n Array size
 * @param array Input array
 * @return Maximum value
 */
static inline double maxval(size_t n, const double *array) {
    if (n == 0 || array == NULL) return 0.0;
    
    double max = array[0];
    for (size_t i = 1; i < n; i++) {
        if (array[i] > max) max = array[i];
    }
    return max;
}

/**
 * Find minimum value in array
 * @param n Array size
 * @param array Input array
 * @return Minimum value
 */
static inline double minval(size_t n, const double *array) {
    if (n == 0 || array == NULL) return 0.0;
    
    double min = array[0];
    for (size_t i = 1; i < n; i++) {
        if (array[i] < min) min = array[i];
    }
    return min;
}

#endif /* MATH_FUNCS_H */
