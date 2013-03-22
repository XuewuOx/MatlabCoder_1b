/*
 * meanfile.c
 *
 * Code generation for function 'meanfile'
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
#include "std.h"
#include "mean.h"
#include "gfit_rtwutil.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */

/* Function Definitions */
void meanfile(const char_T filename_data[200], const int32_T filename_size[2],
              real_T IRgf[3], real_T UVgf[3], real_T IRavg[2], real_T UVavg[2])
{
  int32_T i3;
  int32_T posA;
  char_T tmp_data[201];
  char_T cv6[2];
  static const char_T cv7[2] = { 'r', '\x00' };

  FILE * f;
  int32_T tempvar;
  static char_T bufline[1048576];
  int32_T nStep;
  uint8_T char100;
  int32_T posB;
  int32_T nSam;
  int32_T nFs;
  int32_T k4step;
  char_T cv8[51];
  static const char_T cv9[51] = { '%', 'c', 'S', 'W', 'N', ' ', 'p', 'o', 's',
    'A', '=', '%', 'd', ',', ' ', 'p', 'o', 's', 'B', '=', '%', 'd', ',', ' ',
    'n', 'S', 't', 'e', 'p', 's', '=', '%', 'd', ',', ' ', 'n', 'S', 'a', 'm',
    '=', '%', 'd', ',', ' ', 'F', 's', '=', '%', 'd', '\x0d', '\x0a' };

  emxArray_real_T *dataIR;
  emxArray_real_T *dataUV;
  char_T cv10[3];
  static const char_T cv11[3] = { '%', 'd', ' ' };

  int32_T q0;
  real_T dataIR_std;
  uint32_T qY;
  emxArray_real_T *dataIR_mean;
  emxArray_real_T *dataUV_mean;
  emxArray_real_T *b_dataIR;
  emxArray_real_T *b_dataUV;
  real_T dataUV_std;
  emxArray_real_T *c_dataIR;
  emxArray_real_T *c_dataUV;
  real_T aIR;
  real_T aUV;
  real_T muUV;
  real_T sigUV;

  /*  Calcuate stastistics of IR and UV signals */
  /*  */
  /*  version: .\work_gfit_rdfile\meanfile_v3.m */
  /*  Return values: IRgf=[muIR, sigIR, aIR] for mean, width and amplitude of */
  /*                        Gaussian fitting over hist(IR) */
  /*                 UVgf=[muUV, sigUV, aUV] for mean, width and amplitude of */
  /*                        Gaussian fitting over hist(IR) */
  /*          IRavg=[meanIR, stdIR] for mean and std of IR by mean() and std() */
  /*          UVavg=[meanUV, stdUV] for mean and std of UV by mean() and std() */
  /*   */
  /*  The 'fprintf' function will not be compiled and instead passed */
  /*  to the MATLAB runtime. If we choose to generate code for this example, */
  /*  all calls to extrinsic functions are automatically eliminated. */
  /*  Put class and size constraints on function input. */
  for (i3 = 0; i3 < 2; i3++) {
    IRavg[i3] = 0.0;
    UVavg[i3] = 0.0;
  }

  /*  Define a new opaque variable 'f' which will be of type 'FILE *' */
  /*  in the generated C code initially with the value NULL. */
  /*  Call fopen(filename 'r'), but we need to convert the MATLAB */
  /*  string into a C type string (which is the same string with the */
  /*  NUL (\0) string terminator). */
  /*  Create a NUL terminated C string given a MATLAB string */
  posA = filename_size[1] - 1;
  for (i3 = 0; i3 <= posA; i3++) {
    tmp_data[i3] = filename_data[filename_size[0] * i3];
  }

  tmp_data[filename_size[1]] = '\x00';
  for (i3 = 0; i3 < 2; i3++) {
    cv6[i3] = cv7[i3];
  }

  f = fopen(&tmp_data[0], cv6);
  tempvar = (int)(f);
  if (tempvar == 0) {
    for (i3 = 0; i3 < 3; i3++) {
      IRgf[i3] = -1.0;
      UVgf[i3] = -1.0;
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
    memset(&bufline[0], 0, sizeof(uint8_T) << 20);

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
    for (i3 = 0; i3 < 51; i3++) {
      cv8[i3] = cv9[i3];
    }

    tempvar = fscanf(f, cv8, &char100, &posA, &posB, &nStep, &nSam, &nFs);
    if (tempvar != 6) {
      fclose(f);
      for (i3 = 0; i3 < 3; i3++) {
        IRgf[i3] = -2.0;
        UVgf[i3] = -2.0;
      }
    } else {
      for (tempvar = 0; tempvar < 3; tempvar++) {
        fgets(&bufline[0], 8192, f);
        strlen(&bufline[0]);
      }

      b_emxInit_real_T(&dataIR, 2);

      /*  read data from 7-th line now */
      /*  k=nStep; */
      i3 = dataIR->size[0] * dataIR->size[1];
      dataIR->size[0] = nStep;
      dataIR->size[1] = nSam;
      emxEnsureCapacity((emxArray__common *)dataIR, i3, (int32_T)sizeof(real_T));
      posA = nStep * nSam - 1;
      for (i3 = 0; i3 <= posA; i3++) {
        dataIR->data[i3] = 0.0;
      }

      b_emxInit_real_T(&dataUV, 2);
      i3 = dataUV->size[0] * dataUV->size[1];
      dataUV->size[0] = nStep;
      dataUV->size[1] = nSam;
      emxEnsureCapacity((emxArray__common *)dataUV, i3, (int32_T)sizeof(real_T));
      posA = nStep * nSam - 1;
      for (i3 = 0; i3 <= posA; i3++) {
        dataUV->data[i3] = 0.0;
      }

      /*  read data line-by-line */
      if (nStep != 1) {
        /*  refir.txt, refuv.txt, wtrir.txt, wtruv.txt should contain */
        /*  ONE data line ONLY. */
        for (i3 = 0; i3 < 3; i3++) {
          IRgf[i3] = -3.0;
          UVgf[i3] = -3.0;
        }
      } else {
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
        strlen(&bufline[0]);

        /*  to debug if fgets ok */
        /*   % read motor step data */
        for (i3 = 0; i3 < 3; i3++) {
          cv10[i3] = cv11[i3];
        }

        sscanf(&bufline[0], cv10, &k4step);

        /*  fprintf(' nStep=%d \n', k4step); */
        (double)(k4step);

        /*   % read IR UV data */
        for (posB = 1; posB <= nSam; posB++) {
          /*  nVar=coder.ceval('sscanf',coder.ref(bufline(7+10*(i-1))), ['%d %d'],coder.ref(xir), coder.ref(xuv)); */
          posA = posB - 1;
          if ((posB < 0) && (posA >= 0)) {
            posA = MIN_int32_T;
          }

          tempvar = mul_s32_s32_s32_sat(10, posA);
          nFs = 7 + tempvar;
          if ((tempvar > 0) && (nFs <= 0)) {
            nFs = MAX_int32_T;
          }

          nStep = 0;
          posA = 0;

          /*  fprintf('bufline=%s,  ',bufline(kChar:kChar+9)); */
          for (k4step = 0; k4step < 4; k4step++) {
            /*  x4Char(ii)=bufline(kChar+ii-1)-30; */
            q0 = mul_s32_s32_s32_sat(nStep, 10);
            dataIR_std = rt_roundd_snf((real_T)nFs + (1.0 + (real_T)k4step));
            if (dataIR_std < 2.147483648E+9) {
              i3 = (int32_T)dataIR_std;
            } else {
              i3 = MAX_int32_T;
            }

            tempvar = bufline[i3 - 2];
            qY = (uint32_T)tempvar - 48U;
            if (qY > (uint32_T)tempvar) {
              qY = 0U;
            }

            tempvar = (int32_T)qY;
            nStep = q0 + tempvar;
            if ((q0 > 0) && ((tempvar > 0) && (nStep <= 0))) {
              nStep = MAX_int32_T;
            }

            q0 = mul_s32_s32_s32_sat(posA, 10);
            posA = nFs + 5;
            if ((nFs > 0) && (posA <= 0)) {
              posA = MAX_int32_T;
            }

            dataIR_std = rt_roundd_snf((real_T)posA + (1.0 + (real_T)k4step));
            if (dataIR_std < 2.147483648E+9) {
              i3 = (int32_T)dataIR_std;
            } else {
              i3 = MAX_int32_T;
            }

            tempvar = bufline[i3 - 2];
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

          /*           if (i<5) */
          /*               fprintf ('xir=%04d xuv=%04d \r\n', xir, xuv); */
          /*           end; */
          /*          dataIR(k,i)=coder.ceval('(double)',xir); */
          /*          dataUV(k,i)=coder.ceval('(double)',xuv); */
          dataIR->data[dataIR->size[0] * (posB - 1)] = (real_T)nStep;
          dataUV->data[dataUV->size[0] * (posB - 1)] = (real_T)posA;
        }

        emxInit_real_T(&dataIR_mean, 1);
        emxInit_real_T(&dataUV_mean, 1);
        b_emxInit_real_T(&b_dataIR, 2);

        /*  Close file */
        fclose(f);

        /* % data processing */
        /*  calculating by mean() and std()  */
        mean(dataIR, dataIR_mean);
        mean(dataUV, dataUV_mean);
        i3 = dataIR->size[1];
        tempvar = b_dataIR->size[0] * b_dataIR->size[1];
        b_dataIR->size[0] = 1;
        b_dataIR->size[1] = i3;
        emxEnsureCapacity((emxArray__common *)b_dataIR, tempvar, (int32_T)sizeof
                          (real_T));
        posA = i3 - 1;
        for (i3 = 0; i3 <= posA; i3++) {
          b_dataIR->data[b_dataIR->size[0] * i3] = dataIR->data[dataIR->size[0] *
            i3];
        }

        b_emxInit_real_T(&b_dataUV, 2);
        dataIR_std = b_std(b_dataIR);
        i3 = dataUV->size[1];
        tempvar = b_dataUV->size[0] * b_dataUV->size[1];
        b_dataUV->size[0] = 1;
        b_dataUV->size[1] = i3;
        emxEnsureCapacity((emxArray__common *)b_dataUV, tempvar, (int32_T)sizeof
                          (real_T));
        emxFree_real_T(&b_dataIR);
        posA = i3 - 1;
        for (i3 = 0; i3 <= posA; i3++) {
          b_dataUV->data[b_dataUV->size[0] * i3] = dataUV->data[dataUV->size[0] *
            i3];
        }

        dataUV_std = b_std(b_dataUV);

        /*  set return values of IRavg, UVavg  */
        tempvar = dataIR_mean->size[0];
        emxFree_real_T(&b_dataUV);
        i3 = 0;
        while (i3 <= 0) {
          posA = tempvar - 1;
          for (i3 = 0; i3 <= posA; i3++) {
            IRavg[i3] = dataIR_mean->data[i3];
          }

          i3 = 1;
        }

        emxFree_real_T(&dataIR_mean);
        IRavg[1] = dataIR_std;
        tempvar = dataUV_mean->size[0];
        i3 = 0;
        while (i3 <= 0) {
          posA = tempvar - 1;
          for (i3 = 0; i3 <= posA; i3++) {
            UVavg[i3] = dataUV_mean->data[i3];
          }

          i3 = 1;
        }

        emxFree_real_T(&dataUV_mean);
        b_emxInit_real_T(&c_dataIR, 2);
        UVavg[1] = dataUV_std;

        /*  calculalting by Gaussian fitting over hist() */
        i3 = dataIR->size[1];
        tempvar = c_dataIR->size[0] * c_dataIR->size[1];
        c_dataIR->size[0] = 1;
        c_dataIR->size[1] = i3;
        emxEnsureCapacity((emxArray__common *)c_dataIR, tempvar, (int32_T)sizeof
                          (real_T));
        posA = i3 - 1;
        for (i3 = 0; i3 <= posA; i3++) {
          c_dataIR->data[c_dataIR->size[0] * i3] = dataIR->data[dataIR->size[0] *
            i3];
        }

        b_emxInit_real_T(&c_dataUV, 2);
        b_gfitPDF(c_dataIR, &dataIR_std, &dataUV_std, &aIR);

        /*  sigUV=0; muUV=0; aUV=0; */
        i3 = dataUV->size[1];
        tempvar = c_dataUV->size[0] * c_dataUV->size[1];
        c_dataUV->size[0] = 1;
        c_dataUV->size[1] = i3;
        emxEnsureCapacity((emxArray__common *)c_dataUV, tempvar, (int32_T)sizeof
                          (real_T));
        emxFree_real_T(&c_dataIR);
        posA = i3 - 1;
        for (i3 = 0; i3 <= posA; i3++) {
          c_dataUV->data[c_dataUV->size[0] * i3] = dataUV->data[dataUV->size[0] *
            i3];
        }

        b_gfitPDF(c_dataUV, &sigUV, &muUV, &aUV);

        /*  return the optimal step  */
        IRgf[0] = dataUV_std;
        IRgf[1] = dataIR_std;
        IRgf[2] = aIR;
        UVgf[0] = muUV;
        UVgf[1] = sigUV;
        UVgf[2] = aUV;

        /*    % % plot mean data  */
        /*  title(sprintf('IR/UV vs steps \n opt(UV)=%d, opt(IR)=%d',round(muUV), round(muIR)), 'fontsize', 14); */
        /*  save('instData', 'dataIR', 'dataUV','dataIR_mean','dataUV_mean'); */
        emxFree_real_T(&c_dataUV);
      }

      emxFree_real_T(&dataUV);
      emxFree_real_T(&dataIR);
    }
  }
}

/* End of code generation (meanfile.c) */
