/**
 * GSL Spline Object Declarations
 * Wrapper structures and functions for GSL splines
 */

#ifndef GSL_DECS_H
#define GSL_DECS_H

#include <gsl/gsl_spline.h>
#include <gsl/gsl_spline2d.h>
#include <gsl/gsl_interp.h>
#include <gsl/gsl_interp2d.h>
#include <stdlib.h>

/**
 * 1D GSL Spline Object Structure
 */
struct gsl_spline_object_1D {
    gsl_spline *spline;
    gsl_interp_accel *acc;
    double x_lim[2];  // Limits for integration
};

/**
 * 2D GSL Spline Object Structure
 */
struct gsl_spline_object_2D {
    gsl_spline2d *spline;
    gsl_interp_accel *xacc;
    gsl_interp_accel *yacc;
    const gsl_interp2d_type *type;
    double x_lim[2];  // X limits for integration
    double y_lim[2];  // Y limits for integration
};

/**
 * Create a 1D GSL spline object from arrays
 * @param n Number of data points
 * @param x X data array
 * @param y Y data array
 * @return Initialized gsl_spline_object_1D
 */
static inline gsl_spline_object_1D gsl_so1D(size_t n, const double *x, const double *y) {
    gsl_spline_object_1D so;
    so.acc = gsl_interp_accel_alloc();
    so.spline = gsl_spline_alloc(gsl_interp_linear, n);
    gsl_spline_init(so.spline, x, y, n);
    // Set limits from data
    if (n > 0) {
        so.x_lim[0] = x[0];
        so.x_lim[1] = x[n-1];
    } else {
        so.x_lim[0] = 0.0;
        so.x_lim[1] = 0.0;
    }
    return so;
}

/**
 * Evaluate a 1D GSL spline
 * @param so Spline object
 * @param x Evaluation point
 * @return Interpolated value
 */
static inline double gsl_so1D_eval(const gsl_spline_object_1D so, double x) {
    return gsl_spline_eval(so.spline, x, so.acc);
}

/**
 * Free a 1D GSL spline object
 * @param so Spline object to free
 */
static inline void gsl_so1D_free(gsl_spline_object_1D so) {
    if (so.spline) gsl_spline_free(so.spline);
    if (so.acc) gsl_interp_accel_free(so.acc);
}

/**
 * Create a 2D GSL spline object from arrays
 * @param nx Number of x data points
 * @param ny Number of y data points
 * @param x X data array
 * @param y Y data array
 * @param z Z data array (nx * ny elements)
 * @return Initialized gsl_spline_object_2D
 */
static inline gsl_spline_object_2D gsl_so2D(size_t nx, size_t ny, 
                                             const double *x, const double *y, 
                                             const double *z) {
    gsl_spline_object_2D so;
    so.type = gsl_interp2d_bilinear;
    so.xacc = gsl_interp_accel_alloc();
    so.yacc = gsl_interp_accel_alloc();
    so.spline = gsl_spline2d_alloc(so.type, nx, ny);
    gsl_spline2d_init(so.spline, x, y, z, nx, ny);
    // Set limits from data
    if (nx > 0) {
        so.x_lim[0] = x[0];
        so.x_lim[1] = x[nx-1];
    } else {
        so.x_lim[0] = 0.0;
        so.x_lim[1] = 0.0;
    }
    if (ny > 0) {
        so.y_lim[0] = y[0];
        so.y_lim[1] = y[ny-1];
    } else {
        so.y_lim[0] = 0.0;
        so.y_lim[1] = 0.0;
    }
    return so;
}

/**
 * Evaluate a 2D GSL spline
 * @param so Spline object
 * @param x X evaluation point
 * @param y Y evaluation point
 * @return Interpolated value
 */
static inline double gsl_so2D_eval(const gsl_spline_object_2D so, double x, double y) {
    return gsl_spline2d_eval(so.spline, x, y, so.xacc, so.yacc);
}

/**
 * Free a 2D GSL spline object
 * @param so Spline object to free
 */
static inline void gsl_so2D_free(gsl_spline_object_2D so) {
    if (so.spline) gsl_spline2d_free(so.spline);
    if (so.xacc) gsl_interp_accel_free(so.xacc);
    if (so.yacc) gsl_interp_accel_free(so.yacc);
}

#endif /* GSL_DECS_H */
