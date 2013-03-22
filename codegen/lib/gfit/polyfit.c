/*
 * polyfit.c
 *
 * Code generation for function 'polyfit'
 *
 * C source code generated on: Sat Mar 16 18:31:26 2013
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "gfitPDF.h"
#include "gfit_rdfile.h"
#include "meanfile.h"
#include "polyfit.h"
#include "gfit_emxutil.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
static real_T eml_matlab_zlarfg(int32_T n, real_T *alpha1, emxArray_real_T *x,
  int32_T ix0);
static void eml_qrsolve(const emxArray_real_T *A, emxArray_real_T *B, real_T Y[3],
  real_T *rankR);
static real_T eml_xnrm2(int32_T n, const emxArray_real_T *x, int32_T ix0);
static void eml_xscal(int32_T n, real_T a, emxArray_real_T *x, int32_T ix0);
static real_T rt_hypotd_snf(real_T u0, real_T u1);

/* Function Definitions */
static real_T eml_matlab_zlarfg(int32_T n, real_T *alpha1, emxArray_real_T *x,
  int32_T ix0)
{
  real_T tau;
  int32_T nm1;
  real_T xnorm;
  int32_T knt;
  real_T d2;
  tau = 0.0;
  if (n <= 0) {
  } else {
    nm1 = n - 1;
    xnorm = eml_xnrm2(nm1, x, ix0);
    if (xnorm != 0.0) {
      xnorm = rt_hypotd_snf(fabs(*alpha1), xnorm);
      if (*alpha1 >= 0.0) {
        xnorm = -xnorm;
      }

      if (fabs(xnorm) < 1.0020841800044864E-292) {
        knt = 0;
        do {
          knt++;
          eml_xscal(nm1, 9.9792015476736E+291, x, ix0);
          xnorm *= 9.9792015476736E+291;
          *alpha1 *= 9.9792015476736E+291;
        } while (!(fabs(xnorm) >= 1.0020841800044864E-292));

        xnorm = eml_xnrm2(nm1, x, ix0);
        xnorm = rt_hypotd_snf(fabs(*alpha1), xnorm);
        if (*alpha1 >= 0.0) {
          xnorm = -xnorm;
        }

        tau = (xnorm - *alpha1) / xnorm;
        d2 = 1.0 / (*alpha1 - xnorm);
        eml_xscal(nm1, d2, x, ix0);
        for (nm1 = 1; nm1 <= knt; nm1++) {
          xnorm *= 1.0020841800044864E-292;
        }

        *alpha1 = xnorm;
      } else {
        tau = (xnorm - *alpha1) / xnorm;
        d2 = 1.0 / (*alpha1 - xnorm);
        eml_xscal(nm1, d2, x, ix0);
        *alpha1 = xnorm;
      }
    }
  }

  return tau;
}

static void eml_qrsolve(const emxArray_real_T *A, emxArray_real_T *B, real_T Y[3],
  real_T *rankR)
{
  emxArray_real_T *b_A;
  real_T smax;
  int32_T mn;
  int32_T i2;
  int32_T nmip1;
  int32_T m;
  int32_T b_mn;
  real_T tau_data[3];
  int8_T jpvt[3];
  real_T work[3];
  int32_T i;
  real_T vn1[3];
  int32_T k;
  real_T vn2[3];
  int32_T iy;
  int32_T i_i;
  int32_T mmi;
  int32_T pvt;
  int32_T ix;
  real_T atmp;
  int32_T i_ip1;
  int32_T lastv;
  int32_T lastc;
  boolean_T exitg3;
  int32_T exitg2;
  real_T y;
  real_T t;
  boolean_T exitg1;
  uint32_T b_i;
  b_emxInit_real_T(&b_A, 2);
  smax = (real_T)A->size[0];
  if (smax <= 3.0) {
  } else {
    smax = 3.0;
  }

  mn = (int32_T)smax - 1;
  i2 = b_A->size[0] * b_A->size[1];
  b_A->size[0] = A->size[0];
  b_A->size[1] = 3;
  emxEnsureCapacity((emxArray__common *)b_A, i2, (int32_T)sizeof(real_T));
  nmip1 = A->size[0] * A->size[1] - 1;
  for (i2 = 0; i2 <= nmip1; i2++) {
    b_A->data[i2] = A->data[i2];
  }

  m = A->size[0];
  if (m <= 3) {
    b_mn = m;
  } else {
    b_mn = 3;
  }

  for (i2 = 0; i2 < 3; i2++) {
    jpvt[i2] = (int8_T)(1 + i2);
  }

  if (A->size[0] == 0) {
  } else {
    for (i = 0; i < 3; i++) {
      work[i] = 0.0;
    }

    k = 1;
    for (iy = 0; iy < 3; iy++) {
      smax = eml_xnrm2(m, A, k);
      vn2[iy] = smax;
      k += m;
      vn1[iy] = smax;
    }

    for (i = 0; i + 1 <= b_mn; i++) {
      i_i = i + i * m;
      mmi = (m - i) - 1;
      nmip1 = 3 - i;
      pvt = 0;
      if (nmip1 > 1) {
        ix = i;
        smax = fabs(vn1[i]);
        for (k = 2; k <= nmip1; k++) {
          ix++;
          atmp = fabs(vn1[ix]);
          if (atmp > smax) {
            pvt = k - 1;
            smax = atmp;
          }
        }
      }

      pvt += i;
      if (pvt + 1 != i + 1) {
        ix = m * pvt;
        iy = m * i;
        for (k = 1; k <= m; k++) {
          smax = b_A->data[ix];
          b_A->data[ix] = b_A->data[iy];
          b_A->data[iy] = smax;
          ix++;
          iy++;
        }

        nmip1 = jpvt[pvt];
        jpvt[pvt] = jpvt[i];
        jpvt[i] = (int8_T)nmip1;
        vn1[pvt] = vn1[i];
        vn2[pvt] = vn2[i];
      }

      if (i + 1 < m) {
        atmp = b_A->data[i_i];
        tau_data[i] = eml_matlab_zlarfg(mmi + 1, &atmp, b_A, i_i + 2);
      } else {
        smax = b_A->data[i_i];
        atmp = b_A->data[i_i];
        b_A->data[i_i] = smax;
        tau_data[i] = 0.0;
      }

      b_A->data[i_i] = atmp;
      if (i + 1 < 3) {
        atmp = b_A->data[i_i];
        b_A->data[i_i] = 1.0;
        i_ip1 = (i + (i + 1) * m) + 1;
        if (tau_data[i] != 0.0) {
          lastv = mmi;
          nmip1 = i_i + mmi;
          while ((lastv + 1 > 0) && (b_A->data[nmip1] == 0.0)) {
            lastv--;
            nmip1--;
          }

          lastc = 2 - i;
          exitg3 = FALSE;
          while ((exitg3 == 0U) && (lastc > 0)) {
            nmip1 = i_ip1 + (lastc - 1) * m;
            k = nmip1;
            do {
              exitg2 = 0;
              if (k <= nmip1 + lastv) {
                if (b_A->data[k - 1] != 0.0) {
                  exitg2 = 1;
                } else {
                  k++;
                }
              } else {
                lastc--;
                exitg2 = 2;
              }
            } while (exitg2 == 0U);

            if (exitg2 == 1U) {
              exitg3 = TRUE;
            }
          }
        } else {
          lastv = -1;
          lastc = 0;
        }

        if (lastv + 1 > 0) {
          if (lastc == 0) {
          } else {
            for (iy = 1; iy <= lastc; iy++) {
              work[iy - 1] = 0.0;
            }

            iy = 0;
            i2 = i_ip1 + m * (lastc - 1);
            nmip1 = i_ip1;
            while ((m > 0) && (nmip1 <= i2)) {
              ix = i_i;
              smax = 0.0;
              pvt = nmip1 + lastv;
              for (k = nmip1; k <= pvt; k++) {
                smax += b_A->data[k - 1] * b_A->data[ix];
                ix++;
              }

              work[iy] += smax;
              iy++;
              nmip1 += m;
            }
          }

          if (-tau_data[i] == 0.0) {
          } else {
            nmip1 = 0;
            for (iy = 1; iy <= lastc; iy++) {
              if (work[nmip1] != 0.0) {
                smax = work[nmip1] * -tau_data[i];
                ix = i_i;
                i2 = lastv + i_ip1;
                for (pvt = i_ip1; pvt <= i2; pvt++) {
                  b_A->data[pvt - 1] += b_A->data[ix] * smax;
                  ix++;
                }
              }

              nmip1++;
              i_ip1 += m;
            }
          }
        }

        b_A->data[i_i] = atmp;
      }

      for (iy = i + 1; iy + 1 < 4; iy++) {
        if (vn1[iy] != 0.0) {
          atmp = fabs(b_A->data[i + b_A->size[0] * iy]) / vn1[iy];
          y = atmp * atmp;
          atmp = 1.0 - atmp * atmp;
          if (1.0 - y < 0.0) {
            atmp = 0.0;
          }

          smax = vn1[iy] / vn2[iy];
          if (atmp * (smax * smax) <= 1.4901161193847656E-8) {
            if (i + 1 < m) {
              nmip1 = (i + m * iy) + 1;
              y = 0.0;
              if (mmi < 1) {
              } else if (mmi == 1) {
                y = fabs(b_A->data[nmip1]);
              } else {
                smax = 2.2250738585072014E-308;
                pvt = nmip1 + mmi;
                while (nmip1 + 1 <= pvt) {
                  atmp = fabs(b_A->data[nmip1]);
                  if (atmp > smax) {
                    t = smax / atmp;
                    y = 1.0 + y * t * t;
                    smax = atmp;
                  } else {
                    t = atmp / smax;
                    y += t * t;
                  }

                  nmip1++;
                }

                y = smax * sqrt(y);
              }

              vn1[iy] = y;
              vn2[iy] = vn1[iy];
            } else {
              vn1[iy] = 0.0;
              vn2[iy] = 0.0;
            }
          } else {
            vn1[iy] *= sqrt(atmp);
          }
        }
      }
    }
  }

  *rankR = 0.0;
  if (mn + 1 > 0) {
    k = 0;
    exitg1 = FALSE;
    while ((exitg1 == 0U) && (k <= mn)) {
      smax = (real_T)A->size[0];
      if (smax >= 3.0) {
      } else {
        smax = 3.0;
      }

      if (fabs(b_A->data[k + b_A->size[0] * k]) <= smax * fabs(b_A->data[0]) *
          2.2204460492503131E-16) {
        exitg1 = TRUE;
      } else {
        (*rankR)++;
        k++;
      }
    }
  }

  for (i = 0; i < 3; i++) {
    Y[i] = 0.0;
  }

  for (iy = 0; iy <= mn; iy++) {
    if (tau_data[iy] != 0.0) {
      smax = B->data[iy];
      i2 = A->size[0] - iy;
      for (i = 0; i <= i2 - 2; i++) {
        b_i = ((uint32_T)iy + (uint32_T)i) + 2U;
        smax += b_A->data[((int32_T)b_i + b_A->size[0] * iy) - 1] * B->data
          [(int32_T)b_i - 1];
      }

      smax *= tau_data[iy];
      if (smax != 0.0) {
        B->data[iy] -= smax;
        i2 = A->size[0] - iy;
        for (i = 0; i <= i2 - 2; i++) {
          b_i = ((uint32_T)iy + (uint32_T)i) + 2U;
          B->data[(int32_T)b_i - 1] -= b_A->data[((int32_T)b_i + b_A->size[0] *
            iy) - 1] * smax;
        }
      }
    }
  }

  for (i = 0; i <= mn; i++) {
    Y[jpvt[i] - 1] = B->data[i];
  }

  for (iy = 0; iy <= mn; iy++) {
    nmip1 = mn - iy;
    Y[jpvt[nmip1] - 1] /= b_A->data[nmip1 + b_A->size[0] * nmip1];
    for (i = 0; i <= nmip1 - 1; i++) {
      Y[jpvt[i] - 1] -= Y[jpvt[nmip1] - 1] * b_A->data[i + b_A->size[0] * nmip1];
    }
  }

  emxFree_real_T(&b_A);
}

static real_T eml_xnrm2(int32_T n, const emxArray_real_T *x, int32_T ix0)
{
  real_T y;
  real_T scale;
  int32_T kend;
  int32_T k;
  real_T absxk;
  real_T t;
  y = 0.0;
  if (n < 1) {
  } else if (n == 1) {
    y = fabs(x->data[ix0 - 1]);
  } else {
    scale = 2.2250738585072014E-308;
    kend = (ix0 + n) - 1;
    for (k = ix0; k <= kend; k++) {
      absxk = fabs(x->data[k - 1]);
      if (absxk > scale) {
        t = scale / absxk;
        y = 1.0 + y * t * t;
        scale = absxk;
      } else {
        t = absxk / scale;
        y += t * t;
      }
    }

    y = scale * sqrt(y);
  }

  return y;
}

static void eml_xscal(int32_T n, real_T a, emxArray_real_T *x, int32_T ix0)
{
  emxArray_real_T *b_x;
  int32_T i5;
  int32_T k;
  b_emxInit_real_T(&b_x, 2);
  i5 = (ix0 + n) - 1;
  for (k = ix0; k <= i5; k++) {
    x->data[k - 1] *= a;
  }

  emxFree_real_T(&b_x);
}

static real_T rt_hypotd_snf(real_T u0, real_T u1)
{
  real_T y;
  real_T a;
  a = fabs(u0);
  y = fabs(u1);
  if (a < y) {
    a /= y;
    y *= sqrt(a * a + 1.0);
  } else if (a > y) {
    y /= a;
    y = a * sqrt(y * y + 1.0);
  } else if (rtIsNaN(y)) {
  } else {
    y = a * 1.4142135623730951;
  }

  return y;
}

void polyfit(const emxArray_real_T *x, const emxArray_real_T *y, real_T p[3])
{
  emxArray_real_T *V;
  uint32_T unnamed_idx_0;
  int32_T k;
  emxArray_real_T *b_y;
  int32_T loop_ub;
  real_T rr;
  real_T p1[3];
  b_emxInit_real_T(&V, 2);
  unnamed_idx_0 = (uint32_T)x->size[1];
  k = V->size[0] * V->size[1];
  V->size[0] = (int32_T)unnamed_idx_0;
  V->size[1] = 3;
  emxEnsureCapacity((emxArray__common *)V, k, (int32_T)sizeof(real_T));
  if (V->size[0] == 0) {
  } else {
    for (k = 0; k <= x->size[1] - 1; k++) {
      V->data[k + (V->size[0] << 1)] = 1.0;
    }

    for (k = 0; k <= x->size[1] - 1; k++) {
      V->data[k + V->size[0]] = x->data[k];
    }

    for (k = 0; k <= x->size[1] - 1; k++) {
      V->data[k] = x->data[k] * V->data[k + V->size[0]];
    }
  }

  emxInit_real_T(&b_y, 1);
  k = b_y->size[0];
  b_y->size[0] = y->size[1];
  emxEnsureCapacity((emxArray__common *)b_y, k, (int32_T)sizeof(real_T));
  loop_ub = y->size[1] - 1;
  for (k = 0; k <= loop_ub; k++) {
    b_y->data[k] = y->data[k];
  }

  eml_qrsolve(V, b_y, p1, &rr);
  emxFree_real_T(&b_y);
  emxFree_real_T(&V);
  for (k = 0; k < 3; k++) {
    p[k] = p1[k];
  }
}

/* End of code generation (polyfit.c) */
