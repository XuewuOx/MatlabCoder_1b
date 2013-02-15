/*
 * rdivide.c
 *
 * Code generation for function 'rdivide'
 *
 * C source code generated on: Thu Feb 14 17:57:51 2013
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "gfit_rdfile.h"
#include "meanfile.h"
#include "rdivide.h"
#include "gfit_emxutil.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */

/* Function Definitions */
void rdivide(const emxArray_real_T *x, real_T y, emxArray_real_T *z)
{
  int32_T i0;
  int32_T loop_ub;
  i0 = z->size[0];
  z->size[0] = x->size[0];
  emxEnsureCapacity((emxArray__common *)z, i0, (int32_T)sizeof(real_T));
  loop_ub = x->size[0] - 1;
  for (i0 = 0; i0 <= loop_ub; i0++) {
    z->data[i0] = x->data[i0] / y;
  }
}

/* End of code generation (rdivide.c) */
