/*
 * gfit_rdfile.c
 *
 * Code generation for function 'gfit_rdfile'
 *
 * C source code generated on: Sat Mar 16 18:31:26 2013
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "gfitPDF.h"
#include "gfit_rdfile.h"
#include "meanfile.h"
#include "gfit_emxutil.h"
#include "polyfit.h"
#include "log.h"
#include "mean.h"
#include "gfit_rtwutil.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
static void gfit(const emxArray_real_T *x, const emxArray_real_T *y, real_T
                 *sigma, real_T *mu, real_T *A);

/* Function Definitions */
static void gfit(const emxArray_real_T *x, const emxArray_real_T *y, real_T
                 *sigma, real_T *mu, real_T *A)
{
  int32_T ixstart;
  int32_T n;
  real_T mtmp;
  int32_T ix;
  boolean_T exitg1;
  emxArray_real_T *xnew;
  emxArray_real_T *ynew;
  emxArray_real_T *b_xnew;
  emxArray_real_T *b_ynew;
  real_T p[3];

  /*  [sigma,mu,A]=gfit(x,y) */
  /*  [sigma,mu,A]=gfit(x,y,h) */
  /*  */
  /*  this function is doing fit to the function */
  /*  y=A * exp( -(x-mu)^2 / (2*sigma^2) ) */
  /*  */
  /*  the fitting is been done by a polyfit */
  /*  the lan of the data. */
  /*  */
  /*  h is the threshold which is the fraction */
  /*  from the maximum y height that the data */
  /*  is been taken from. */
  /*  h should be a number between 0-1. */
  /*  if h have not been taken it is set to be 0.2 */
  /*  as default. */
  /*  */
  /* % threshold */
  /* % cutting */
  ixstart = 1;
  n = y->size[0];
  mtmp = y->data[0];
  if (n > 1) {
    if (rtIsNaN(y->data[0])) {
      ix = 2;
      exitg1 = FALSE;
      while ((exitg1 == 0U) && (ix <= n)) {
        ixstart = ix;
        if (!rtIsNaN(y->data[ix - 1])) {
          mtmp = y->data[ix - 1];
          exitg1 = TRUE;
        } else {
          ix++;
        }
      }
    }

    if (ixstart < n) {
      while (ixstart + 1 <= n) {
        if (y->data[ixstart] > mtmp) {
          mtmp = y->data[ixstart];
        }

        ixstart++;
      }
    }
  }

  b_emxInit_real_T(&xnew, 2);
  b_emxInit_real_T(&ynew, 2);
  ixstart = xnew->size[0] * xnew->size[1];
  xnew->size[0] = 1;
  xnew->size[1] = 0;
  emxEnsureCapacity((emxArray__common *)xnew, ixstart, (int32_T)sizeof(real_T));
  ixstart = ynew->size[0] * ynew->size[1];
  ynew->size[0] = 1;
  ynew->size[1] = 0;
  emxEnsureCapacity((emxArray__common *)ynew, ixstart, (int32_T)sizeof(real_T));
  n = 0;
  b_emxInit_real_T(&b_xnew, 2);
  b_emxInit_real_T(&b_ynew, 2);
  while (n <= x->size[0] - 1) {
    if (y->data[n] > mtmp * 0.2) {
      ixstart = b_xnew->size[0] * b_xnew->size[1];
      b_xnew->size[0] = 1;
      b_xnew->size[1] = xnew->size[1] + 1;
      emxEnsureCapacity((emxArray__common *)b_xnew, ixstart, (int32_T)sizeof
                        (real_T));
      ix = xnew->size[1] - 1;
      for (ixstart = 0; ixstart <= ix; ixstart++) {
        b_xnew->data[b_xnew->size[0] * ixstart] = xnew->data[xnew->size[0] *
          ixstart];
      }

      b_xnew->data[b_xnew->size[0] * xnew->size[1]] = x->data[n];
      ixstart = xnew->size[0] * xnew->size[1];
      xnew->size[0] = 1;
      xnew->size[1] = b_xnew->size[1];
      emxEnsureCapacity((emxArray__common *)xnew, ixstart, (int32_T)sizeof
                        (real_T));
      ix = b_xnew->size[1] - 1;
      for (ixstart = 0; ixstart <= ix; ixstart++) {
        xnew->data[xnew->size[0] * ixstart] = b_xnew->data[b_xnew->size[0] *
          ixstart];
      }

      ixstart = b_ynew->size[0] * b_ynew->size[1];
      b_ynew->size[0] = 1;
      b_ynew->size[1] = ynew->size[1] + 1;
      emxEnsureCapacity((emxArray__common *)b_ynew, ixstart, (int32_T)sizeof
                        (real_T));
      ix = ynew->size[1] - 1;
      for (ixstart = 0; ixstart <= ix; ixstart++) {
        b_ynew->data[b_ynew->size[0] * ixstart] = ynew->data[ynew->size[0] *
          ixstart];
      }

      b_ynew->data[b_ynew->size[0] * ynew->size[1]] = y->data[n];
      ixstart = ynew->size[0] * ynew->size[1];
      ynew->size[0] = 1;
      ynew->size[1] = b_ynew->size[1];
      emxEnsureCapacity((emxArray__common *)ynew, ixstart, (int32_T)sizeof
                        (real_T));
      ix = b_ynew->size[1] - 1;
      for (ixstart = 0; ixstart <= ix; ixstart++) {
        ynew->data[ynew->size[0] * ixstart] = b_ynew->data[b_ynew->size[0] *
          ixstart];
      }
    }

    n++;
  }

  emxFree_real_T(&b_ynew);
  emxFree_real_T(&b_xnew);

  /* % fitting */
  b_log(ynew);
  polyfit(xnew, ynew, p);
  *sigma = sqrt(-1.0 / (2.0 * p[0]));
  *mu = p[1] * rt_powd_snf(*sigma, 2.0);
  *A = exp(p[2] + rt_powd_snf(*mu, 2.0) / (2.0 * rt_powd_snf(*sigma, 2.0)));
  emxFree_real_T(&ynew);
  emxFree_real_T(&xnew);
}

void gfit_rdfile(const char_T filename_data[200], const int32_T filename_size[2],
                 real_T gfir[3], real_T gfuv[3])
{
  int32_T tempvar;
  int32_T i0;
  char_T tmp_data[201];
  char_T cv0[2];
  static const char_T cv1[2] = { 'r', '\x00' };

  FILE * f;
  char_T bufline[65536];
  int32_T nStep;
  uint8_T char100;
  int32_T posA;
  int32_T posB;
  int32_T nSam;
  int32_T nFs;
  int32_T k4step;
  char_T cv2[51];
  static const char_T cv3[51] = { '%', 'c', 'S', 'W', 'N', ' ', 'p', 'o', 's',
    'A', '=', '%', 'd', ',', ' ', 'p', 'o', 's', 'B', '=', '%', 'd', ',', ' ',
    'n', 'S', 't', 'e', 'p', 's', '=', '%', 'd', ',', ' ', 'n', 'S', 'a', 'm',
    '=', '%', 'd', ',', ' ', 'F', 's', '=', '%', 'd', '\x0d', '\x0a' };

  emxArray_real_T *dataMS;
  emxArray_real_T *dataIR;
  emxArray_real_T *dataUV;
  int32_T k;
  emxArray_real_T *dataIR_mean;
  emxArray_real_T *dataUV_mean;
  int32_T exitg2;
  char_T cv4[3];
  static const char_T cv5[3] = { '%', 'd', ' ' };

  int32_T exitg1;
  int32_T kChar;
  int32_T xir;
  int32_T ii;
  int32_T q0;
  real_T sigmaUV;
  uint32_T qY;
  real_T AUV;
  real_T muUV;
  real_T AIR;
  real_T muIR;
  real_T sigmaIR;

  /*  version: .\work_readfile\readfile_v5.m */
  /*  The 'fprintf' function will not be compiled and instead passed */
  /*  to the MATLAB runtime. If we choose to generate code for this example, */
  /*  all calls to extrinsic functions are automatically eliminated. */
  /*  Put class and size constraints on function input. */
  /*  Define a new opaque variable 'f' which will be of type 'FILE *' */
  /*  in the generated C code initially with the value NULL. */
  /*  Call fopen(filename 'r'), but we need to convert the MATLAB */
  /*  string into a C type string (which is the same string with the */
  /*  NUL (\0) string terminator). */
  /*  Create a NUL terminated C string given a MATLAB string */
  tempvar = filename_size[1] - 1;
  for (i0 = 0; i0 <= tempvar; i0++) {
    tmp_data[i0] = filename_data[filename_size[0] * i0];
  }

  tmp_data[filename_size[1]] = '\x00';
  for (i0 = 0; i0 < 2; i0++) {
    cv0[i0] = cv1[i0];
  }

  f = fopen(&tmp_data[0], cv0);
  tempvar = (int)(f);
  if (tempvar == 0) {
    for (i0 = 0; i0 < 3; i0++) {
      gfir[i0] = -1.0;
      gfuv[i0] = -1.0;
    }
  } else {
    /*  Call fseek(f, 0, SEEK_END) to set file position to the end of */
    /*  the file. */
    fseek(f, 0, SEEK_END);

    /*  We need to initialize the variable 'filelen' to the proper type */
    /*  as custom C functions are not analyzed. */
    /*  Call ftell(f) which will return the length of the file in bytes */
    /*  (as current file position is at the end of the file). */
    ftell(f);

    /*  Reset current file position */
    fseek(f, 0, SEEK_SET);

    /*  Initialize a buffer */
    /*  buffer = zeros(1,bufSIZE,'uint8'); */
    memset(&bufline[0], 0, sizeof(uint8_T) << 16);

    /*  NOTE: bufline will be define as uint8_T type in generated C code */
    /*  manually change its type to char_T in the generated c codes,  */
    /*  like char_T bufline[65536]; */
    /*  strline=zeros(1,1024,'uint8'); */
    nStep = 0;

    /*  Remaining is the number of bytes to read (from the file) */
    /*  Index is the current position to read into the buffer */
    char100 = 0;
    posA = 0;
    posB = 0;
    nSam = 0;
    nFs = 0;
    k4step = 0;

    /*  a temp variable to keep the value of current steps */
    fgets(&bufline[0], 1024, f);
    strlen(&bufline[0]);
    for (i0 = 0; i0 < 51; i0++) {
      cv2[i0] = cv3[i0];
    }

    tempvar = fscanf(f, cv2, &char100, &posA, &posB, &nStep, &nSam, &nFs);
    if (tempvar != 6) {
      fclose(f);
      for (i0 = 0; i0 < 3; i0++) {
        gfir[i0] = -2.0;
        gfuv[i0] = -2.0;
      }
    } else {
      for (tempvar = 0; tempvar < 3; tempvar++) {
        fgets(&bufline[0], 8192, f);
        strlen(&bufline[0]);
      }

      emxInit_real_T(&dataMS, 1);

      /*  read data from 7-th line now */
      i0 = dataMS->size[0];
      dataMS->size[0] = nStep;
      emxEnsureCapacity((emxArray__common *)dataMS, i0, (int32_T)sizeof(real_T));
      tempvar = nStep - 1;
      for (i0 = 0; i0 <= tempvar; i0++) {
        dataMS->data[i0] = 0.0;
      }

      b_emxInit_real_T(&dataIR, 2);

      /*  k=nStep; */
      i0 = dataIR->size[0] * dataIR->size[1];
      dataIR->size[0] = nStep;
      dataIR->size[1] = nSam;
      emxEnsureCapacity((emxArray__common *)dataIR, i0, (int32_T)sizeof(real_T));
      tempvar = nStep * nSam - 1;
      for (i0 = 0; i0 <= tempvar; i0++) {
        dataIR->data[i0] = 0.0;
      }

      b_emxInit_real_T(&dataUV, 2);
      i0 = dataUV->size[0] * dataUV->size[1];
      dataUV->size[0] = nStep;
      dataUV->size[1] = nSam;
      emxEnsureCapacity((emxArray__common *)dataUV, i0, (int32_T)sizeof(real_T));
      tempvar = nStep * nSam - 1;
      for (i0 = 0; i0 <= tempvar; i0++) {
        dataUV->data[i0] = 0.0;
      }

      /*  read data line-by-line */
      k = 0;
      emxInit_real_T(&dataIR_mean, 1);
      emxInit_real_T(&dataUV_mean, 1);
      do {
        exitg2 = 0;
        if (k + 1 <= nStep) {
          /*  fprintf('line %d, ',nline); */
          tempvar = mul_s32_s32_s32_sat(nSam, 10);
          posA = 7 + tempvar;
          if ((tempvar > 0) && (posA <= 0)) {
            posA = MAX_int32_T;
          }

          tempvar = posA + 2;
          if ((posA > 0) && (tempvar <= 0)) {
            tempvar = MAX_int32_T;
          }

          fgets(&bufline[0], tempvar, f);
          posB = strlen(&bufline[0]);

          /*  fprintf('(%d)="%s',nChar,bufline(1:nChar));  % to debug if fgets ok */
          /*   % read motor step data */
          for (i0 = 0; i0 < 3; i0++) {
            cv4[i0] = cv5[i0];
          }

          sscanf(&bufline[0], cv4, &k4step);

          /*  fprintf(' nStep=%d \n', k4step); */
          dataMS->data[k] = (double)(k4step);

          /*   % read IR UV data */
          nFs = 1;
          do {
            exitg1 = 0;
            if (nFs <= nSam) {
              /*  nVar=coder.ceval('sscanf',coder.ref(bufline(7+10*(i-1))), ['%d %d'],coder.ref(xir), coder.ref(xuv)); */
              posA = nFs - 1;
              if ((nFs < 0) && (posA >= 0)) {
                posA = MIN_int32_T;
              }

              tempvar = mul_s32_s32_s32_sat(10, posA);
              kChar = 7 + tempvar;
              if ((tempvar > 0) && (kChar <= 0)) {
                kChar = MAX_int32_T;
              }

              xir = 0;
              posA = 0;

              /*  fprintf('bufline=%s,  ',bufline(kChar:kChar+9)); */
              for (ii = 0; ii < 4; ii++) {
                /*  x4Char(ii)=bufline(kChar+ii-1)-30; */
                q0 = mul_s32_s32_s32_sat(xir, 10);
                sigmaUV = rt_roundd_snf((real_T)kChar + (1.0 + (real_T)ii));
                if (sigmaUV < 2.147483648E+9) {
                  i0 = (int32_T)sigmaUV;
                } else {
                  i0 = MAX_int32_T;
                }

                tempvar = bufline[i0 - 2];
                qY = (uint32_T)tempvar - 48U;
                if (qY > (uint32_T)tempvar) {
                  qY = 0U;
                }

                tempvar = (int32_T)qY;
                xir = q0 + tempvar;
                if ((q0 > 0) && ((tempvar > 0) && (xir <= 0))) {
                  xir = MAX_int32_T;
                }

                q0 = mul_s32_s32_s32_sat(posA, 10);
                posA = kChar + 5;
                if ((kChar > 0) && (posA <= 0)) {
                  posA = MAX_int32_T;
                }

                sigmaUV = rt_roundd_snf((real_T)posA + (1.0 + (real_T)ii));
                if (sigmaUV < 2.147483648E+9) {
                  i0 = (int32_T)sigmaUV;
                } else {
                  i0 = MAX_int32_T;
                }

                tempvar = bufline[i0 - 2];
                qY = (uint32_T)tempvar - 48U;
                if (qY > (uint32_T)tempvar) {
                  qY = 0U;
                }

                tempvar = (int32_T)qY;
                posA = q0 + tempvar;
                if ((q0 > 0) && ((tempvar > 0) && (posA <= 0))) {
                  posA = MAX_int32_T;
                }
              }

              if (kChar > posB) {
                /*  ERROR: no enough chars for reading,  */
                fclose(f);
                for (i0 = 0; i0 < 3; i0++) {
                  gfir[i0] = -2.0;
                  gfuv[i0] = -2.0;
                }

                exitg1 = 1;
              } else {
                /*  fprintf (' %04d %04d', xir, xuv); */
                dataIR->data[k + dataIR->size[0] * (nFs - 1)] = (double)(xir);
                dataUV->data[k + dataUV->size[0] * (nFs - 1)] = (double)(posA);
                nFs++;
              }
            } else {
              /*  fprintf ('\n'); */
              /*       % display the dataIR and dataUV */
              /*       fprintf('  dataIR(%d,:)=%s\n',k,num2str(dataIR(k,1:nSam))); */
              /*       fprintf('  dataUV(%d,:)=%s\n',k,num2str(dataUV(k,1:nSam))); */
              /*      % move to the end of line for next reading  */
              /*      % coder.ceval('fgets',coder.ref(bufline(1)), int32(1024),f);  */
              /*      coder.ceval('fgets',coder.ref(bufline(1)), int32(1024),f);   */
              /*      nChar=coder.ceval('strlen',coder.ref(bufline(1))); */
              /*      % fprintf('left %d chars="%s',nChar,bufline(1:nChar));  */
              /*      fprintf('   left %d chars ="',nChar); */
              /*      for i=1:nChar */
              /*             fprintf(' %02H',bufline(i)); */
              /*      end; */
              /*      fprintf('"\n'); */
              /*  %     [n strline]=readLine(bufline,f); */
              /*  %     if (n<=0) */
              /*  %         y=-1; */
              /*  %         return; */
              /*  %     end; */
              /*  %     fprintf(' (%d left = "%s")\n',n, strline(1:n)); */
              k++;
              exitg1 = 2;
            }
          } while (exitg1 == 0U);

          if (exitg1 == 1U) {
            exitg2 = 1;
          }
        } else {
          /*  Close file */
          fclose(f);

          /*  % data processing */
          mean(dataIR, dataIR_mean);
          mean(dataUV, dataUV_mean);

          /*    % % plot mean data  */
          /*  % gaussian fitting over UV */
          gfit(dataMS, dataUV_mean, &sigmaUV, &muUV, &AUV);

          /*  plot gaussian fitting results */
          /*  % gaussian fitting over IR */
          gfit(dataMS, dataIR_mean, &sigmaIR, &muIR, &AIR);

          /*  plot gaussian fitting results */
          /*  title(sprintf('IR/UV vs steps \n opt(UV)=%d, opt(IR)=%d',round(muUV), round(muIR)), 'fontsize', 14); */
          /*  return the optimal step  */
          gfir[0] = rt_roundd_snf(muIR);
          gfir[1] = AIR;
          gfir[2] = sigmaIR;
          gfuv[0] = rt_roundd_snf(muUV);
          gfuv[1] = AUV;
          gfuv[2] = sigmaUV;

          /*  save('instData', 'dataIR', 'dataUV','dataIR_mean','dataUV_mean'); */
          exitg2 = 1;
        }
      } while (exitg2 == 0U);

      emxFree_real_T(&dataUV_mean);
      emxFree_real_T(&dataIR_mean);
      emxFree_real_T(&dataUV);
      emxFree_real_T(&dataIR);
      emxFree_real_T(&dataMS);
    }
  }
}

/* End of code generation (gfit_rdfile.c) */
