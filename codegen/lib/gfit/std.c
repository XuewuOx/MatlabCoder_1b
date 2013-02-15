/*
 * std.c
 *
 * Code generation for function 'std'
 *
 * C source code generated on: Thu Feb 14 17:57:51 2013
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "gfit_rdfile.h"
#include "meanfile.h"
#include "std.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */

/* Function Definitions */
real_T b_std(const emxArray_real_T *varargin_1)
{
  real_T y;
  int32_T d;
  int32_T ix;
  real_T xbar;
  int32_T k;
  real_T r;
  if (varargin_1->size[1] > 1) {
    d = varargin_1->size[1] - 1;
  } else {
    d = varargin_1->size[1];
  }

  if (varargin_1->size[1] == 0) {
    y = rtNaN;
  } else {
    ix = 0;
    xbar = varargin_1->data[0];
    for (k = 0; k <= varargin_1->size[1] - 2; k++) {
      ix++;
      xbar += varargin_1->data[ix];
    }

    xbar /= (real_T)varargin_1->size[1];
    ix = 0;
    r = varargin_1->data[0] - xbar;
    y = r * r;
    for (k = 0; k <= varargin_1->size[1] - 2; k++) {
      ix++;
      r = varargin_1->data[ix] - xbar;
      y += r * r;
    }

    y /= (real_T)d;
  }

  return sqrt(y);
}

/* End of code generation (std.c) */
