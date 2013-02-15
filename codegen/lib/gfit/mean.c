/*
 * mean.c
 *
 * Code generation for function 'mean'
 *
 * C source code generated on: Thu Feb 14 17:57:51 2013
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "gfit_rdfile.h"
#include "meanfile.h"
#include "mean.h"
#include "gfit_emxutil.h"
#include "rdivide.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */

/* Function Definitions */
void mean(const emxArray_real_T *x, emxArray_real_T *y)
{
  uint32_T sz[2];
  int32_T vstride;
  int32_T vlen;
  int32_T iy;
  int32_T ixstart;
  int32_T j;
  int32_T ix;
  real_T s;
  int32_T k;
  emxArray_real_T *b_y;
  for (vstride = 0; vstride < 2; vstride++) {
    sz[vstride] = (uint32_T)x->size[vstride];
  }

  sz[1] = 1U;
  vstride = y->size[0];
  y->size[0] = (int32_T)sz[0];
  emxEnsureCapacity((emxArray__common *)y, vstride, (int32_T)sizeof(real_T));
  if ((x->size[0] == 0) || (x->size[1] == 0)) {
    vlen = y->size[0];
    vstride = y->size[0];
    y->size[0] = vlen;
    emxEnsureCapacity((emxArray__common *)y, vstride, (int32_T)sizeof(real_T));
    vlen--;
    for (vstride = 0; vstride <= vlen; vstride++) {
      y->data[vstride] = 0.0;
    }
  } else {
    vlen = x->size[1];
    vstride = x->size[0];
    iy = -1;
    ixstart = -1;
    for (j = 1; j <= vstride; j++) {
      ixstart++;
      ix = ixstart;
      s = x->data[ixstart];
      for (k = 2; k <= vlen; k++) {
        ix += vstride;
        s += x->data[ix];
      }

      iy++;
      y->data[iy] = s;
    }
  }

  emxInit_real_T(&b_y, 1);
  vstride = b_y->size[0];
  b_y->size[0] = y->size[0];
  emxEnsureCapacity((emxArray__common *)b_y, vstride, (int32_T)sizeof(real_T));
  vlen = y->size[0] - 1;
  for (vstride = 0; vstride <= vlen; vstride++) {
    b_y->data[vstride] = y->data[vstride];
  }

  rdivide(b_y, (real_T)x->size[1], y);
  emxFree_real_T(&b_y);
}

/* End of code generation (mean.c) */
