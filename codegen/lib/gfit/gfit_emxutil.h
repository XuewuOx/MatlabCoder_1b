/*
 * gfit_emxutil.h
 *
 * Code generation for function 'gfit_emxutil'
 *
 * C source code generated on: Thu Feb 14 17:57:51 2013
 *
 */

#ifndef __GFIT_EMXUTIL_H__
#define __GFIT_EMXUTIL_H__
/* Include files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"

#include "rtwtypes.h"
#include "gfit_types.h"
/* Custom Header Code */
#include <stdio.h>


/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
extern void b_emxInit_real_T(emxArray_real_T **pEmxArray, int32_T numDimensions);
extern void emxEnsureCapacity(emxArray__common *emxArray, int32_T oldNumel, int32_T elementSize);
extern void emxFree_real_T(emxArray_real_T **pEmxArray);
extern void emxInit_real_T(emxArray_real_T **pEmxArray, int32_T numDimensions);
#endif
/* End of code generation (gfit_emxutil.h) */
