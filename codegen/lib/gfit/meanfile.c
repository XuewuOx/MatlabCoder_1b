/*
 * meanfile.c
 *
 * Code generation for function 'meanfile'
 *
 * C source code generated on: Thu Feb 14 17:57:51 2013
 *
 */

/* Include files */
#include "rt_nonfinite.h"
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
void meanfile(const char_T filename_data[100], const int32_T filename_size[2],
              real_T dIR[2], real_T dUV[2])
{
  int32_T posB;
  int32_T nVar;
  char_T tmp_data[101];
  char_T cv8[2];
  static const char_T cv9[2] = { 'r', '\x00' };

  FILE * f;
  int32_T tempvar;
  char_T bufline[65536];
  int32_T nStep;
  uint8_T char100;
  int32_T nSam;
  int32_T nFs;
  int32_T k4step;
  char_T cv10[51];
  static const char_T cv11[51] = { '%', 'c', 'S', 'W', 'N', ' ', 'p', 'o', 's',
    'A', '=', '%', 'd', ',', ' ', 'p', 'o', 's', 'B', '=', '%', 'd', ',', ' ',
    'n', 'S', 't', 'e', 'p', 's', '=', '%', 'd', ',', ' ', 'n', 'S', 'a', 'm',
    '=', '%', 'd', ',', ' ', 'F', 's', '=', '%', 'd', '\x0d', '\x0a' };

  emxArray_real_T *dataIR;
  emxArray_real_T *dataUV;
  int32_T xir;
  int32_T xuv;
  emxArray_real_T *dataIR_mean;
  emxArray_real_T *dataUV_mean;
  emxArray_real_T *b_dataUV;
  emxArray_real_T *b_dataIR;
  int32_T exitg2;
  char_T cv12[3];
  static const char_T cv13[3] = { '%', 'd', ' ' };

  int32_T exitg1;
  char_T cv14[5];
  static const char_T cv15[5] = { '%', 'd', ' ', '%', 'd' };

  char_T cv16[26];
  static const char_T cv17[26] = { 'r', 'e', 'a', 'd', 'i', 'n', 'g', ' ', 'f',
    'i', 'l', 'e', ' ', 's', 'u', 'c', 'c', 'e', 's', 's', 'e', 's', '\\', 'r',
    '\\', 'n' };

  real_T dataIR_std;
  real_T dataUV_std;

  /*  version: .\work_readfile\meanfile_v1.m */
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
  posB = filename_size[1] - 1;
  for (nVar = 0; nVar <= posB; nVar++) {
    tmp_data[nVar] = filename_data[filename_size[0] * nVar];
  }

  tmp_data[filename_size[1]] = '\x00';
  for (nVar = 0; nVar < 2; nVar++) {
    cv8[nVar] = cv9[nVar];
  }

  f = fopen(&tmp_data[0], cv8);
  tempvar = (int)(f);
  if (tempvar == 0) {
    for (nVar = 0; nVar < 2; nVar++) {
      dIR[nVar] = -1.0;
      dUV[nVar] = -1.0;
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
    tempvar = 0;
    posB = 0;
    nSam = 0;
    nFs = 0;
    k4step = 0;

    /*  a temp variable to keep the value of current steps */
    fgets(&bufline[0], 1024, f);
    strlen(&bufline[0]);
    for (nVar = 0; nVar < 51; nVar++) {
      cv10[nVar] = cv11[nVar];
    }

    nVar = fscanf(f, cv10, &char100, &tempvar, &posB, &nStep, &nSam, &nFs);
    if (nVar != 6) {
      fclose(f);
      for (nVar = 0; nVar < 2; nVar++) {
        dIR[nVar] = -2.0;
        dUV[nVar] = -2.0;
      }
    } else {
      for (tempvar = 0; tempvar < 3; tempvar++) {
        fgets(&bufline[0], 8192, f);
        strlen(&bufline[0]);
      }

      b_emxInit_real_T(&dataIR, 2);

      /*  read data from 7-th line now */
      /*  k=nStep; */
      nVar = dataIR->size[0] * dataIR->size[1];
      dataIR->size[0] = nStep;
      dataIR->size[1] = nSam;
      emxEnsureCapacity((emxArray__common *)dataIR, nVar, (int32_T)sizeof(real_T));
      posB = nStep * nSam - 1;
      for (nVar = 0; nVar <= posB; nVar++) {
        dataIR->data[nVar] = 0.0;
      }

      b_emxInit_real_T(&dataUV, 2);
      nVar = dataUV->size[0] * dataUV->size[1];
      dataUV->size[0] = nStep;
      dataUV->size[1] = nSam;
      emxEnsureCapacity((emxArray__common *)dataUV, nVar, (int32_T)sizeof(real_T));
      posB = nStep * nSam - 1;
      for (nVar = 0; nVar <= posB; nVar++) {
        dataUV->data[nVar] = 0.0;
      }

      xir = 0;
      xuv = 0;

      /*  read data line-by-line */
      if (nStep != 1) {
        /*  refir.txt, refuv.txt, wtrir.txt, wtruv.txt should contain */
        /*  ONE data line ONLY. */
        for (nVar = 0; nVar < 2; nVar++) {
          dIR[nVar] = -3.0;
          dUV[nVar] = -3.0;
        }
      } else {
        tempvar = 1;
        emxInit_real_T(&dataIR_mean, 1);
        emxInit_real_T(&dataUV_mean, 1);
        b_emxInit_real_T(&b_dataUV, 2);
        b_emxInit_real_T(&b_dataIR, 2);
        do {
          exitg2 = 0;
          if (tempvar <= 1) {
            /*  fprintf('line %d, ',nline); */
            tempvar = mul_s32_s32_s32_sat(nSam, 10);
            posB = 7 + tempvar;
            if ((tempvar > 0) && (posB <= 0)) {
              posB = MAX_int32_T;
            }

            tempvar = posB + 2;
            if ((posB > 0) && (tempvar <= 0)) {
              tempvar = MAX_int32_T;
            }

            fgets(&bufline[0], tempvar, f);
            strlen(&bufline[0]);

            /*  fprintf('(%d)="%s',nChar,bufline(1:nChar));  % to debug if fgets ok */
            /*   % read motor step data */
            for (nVar = 0; nVar < 3; nVar++) {
              cv12[nVar] = cv13[nVar];
            }

            sscanf(&bufline[0], cv12, &k4step);

            /*  fprintf(' nStep=%d \n', k4step); */
            (double)(k4step);

            /*   % read IR UV data */
            nFs = 1;
            do {
              exitg1 = 0;
              if (nFs <= nSam) {
                for (nVar = 0; nVar < 5; nVar++) {
                  cv14[nVar] = cv15[nVar];
                }

                posB = nFs - 1;
                if ((nFs < 0) && (posB >= 0)) {
                  posB = MIN_int32_T;
                }

                tempvar = mul_s32_s32_s32_sat(10, posB);
                posB = 7 + tempvar;
                if ((tempvar > 0) && (posB <= 0)) {
                  posB = MAX_int32_T;
                }

                nVar = sscanf(&bufline[posB - 1], cv14, &xir, &xuv);
                if (nVar != 2) {
                  fclose(f);
                  for (nVar = 0; nVar < 2; nVar++) {
                    dIR[nVar] = -2.0;
                    dUV[nVar] = -2.0;
                  }

                  exitg1 = 1;
                } else {
                  /*  fprintf (' %04d %04d', xir, xuv); */
                  dataIR->data[dataIR->size[0] * (nFs - 1)] = (double)(xir);
                  dataUV->data[dataUV->size[0] * (nFs - 1)] = (double)(xuv);
                  nFs++;
                }
              } else {
                tempvar = 2;
                exitg1 = 2;
              }
            } while (exitg1 == 0U);

            if (exitg1 == 1U) {
              exitg2 = 1;
            }
          } else {
            /*  Close file */
            fclose(f);
            for (nVar = 0; nVar < 26; nVar++) {
              cv16[nVar] = cv17[nVar];
            }

            printf(cv16);

            /*  % data processing */
            mean(dataIR, dataIR_mean);
            mean(dataUV, dataUV_mean);
            nVar = dataIR->size[1];
            tempvar = b_dataIR->size[0] * b_dataIR->size[1];
            b_dataIR->size[0] = 1;
            b_dataIR->size[1] = nVar;
            emxEnsureCapacity((emxArray__common *)b_dataIR, tempvar, (int32_T)
                              sizeof(real_T));
            posB = nVar - 1;
            for (nVar = 0; nVar <= posB; nVar++) {
              b_dataIR->data[b_dataIR->size[0] * nVar] = dataIR->data
                [dataIR->size[0] * nVar];
            }

            dataIR_std = b_std(b_dataIR);
            nVar = dataUV->size[1];
            tempvar = b_dataUV->size[0] * b_dataUV->size[1];
            b_dataUV->size[0] = 1;
            b_dataUV->size[1] = nVar;
            emxEnsureCapacity((emxArray__common *)b_dataUV, tempvar, (int32_T)
                              sizeof(real_T));
            posB = nVar - 1;
            for (nVar = 0; nVar <= posB; nVar++) {
              b_dataUV->data[b_dataUV->size[0] * nVar] = dataUV->data
                [dataUV->size[0] * nVar];
            }

            dataUV_std = b_std(b_dataUV);

            /*    % % plot mean data  */
            /*  xtime=[1/nFs:1/nFs:nSam/nFs]; */
            /*  % gaussian fitting over UV */
            /*  fprintf('Gaussian fit over dataUV'); */
            /*  [sigmaUV, muUV, AUV] = gfit(dataMS,dataUV_mean,0.2); */
            /*  % plot gaussian fitting results */
            /*  fprintf('... OK.\n optimal postion of UV(step) is %04d (mu=%f, sigma=%f, A=%f)\n',... */
            /*      round(muUV),muUV, sigmaUV, AUV); */
            /*  y_gf=AUV*exp(-(dataMS-muUV).^2/(2*sigmaUV^2)); */
            /*  plot(dataMS,y_gf,'.-m'); */
            /*  stem(round(muUV),AUV,'sk'); */
            /*  % gaussian fitting over IR */
            /*     fprintf('Gaussian fit over dataIR'); */
            /*      [sigmaIR, muIR, AIR] = gfit(dataMS,dataIR_mean,0.2); */
            /*      % plot gaussian fitting results */
            /*      fprintf('... OK.\n optimal postion of IR(step) is %04d (mu=%f, sigma=%f, A=%f)\n',... */
            /*           round(muIR),muIR, sigmaIR, AIR); */
            /*      y_gf=AIR*exp(-(dataMS-muIR).^2/(2*sigmaIR^2)); */
            /*      plot(dataMS,y_gf,'.-g'); */
            /*      stem(round(muIR),AIR,'sg'); */
            /*  title(sprintf('IR/UV vs steps \n opt(UV)=%d, opt(IR)=%d',round(muUV), round(muIR)), 'fontsize', 14); */
            /*  return the optimal step  */
            tempvar = dataIR_mean->size[0];
            nVar = 0;
            while (nVar <= 0) {
              posB = tempvar - 1;
              for (nVar = 0; nVar <= posB; nVar++) {
                dIR[nVar] = dataIR_mean->data[nVar];
              }

              nVar = 1;
            }

            dIR[1] = dataIR_std;
            tempvar = dataUV_mean->size[0];
            nVar = 0;
            while (nVar <= 0) {
              posB = tempvar - 1;
              for (nVar = 0; nVar <= posB; nVar++) {
                dUV[nVar] = dataUV_mean->data[nVar];
              }

              nVar = 1;
            }

            dUV[1] = dataUV_std;

            /*  save('instData', 'dataIR', 'dataUV','dataIR_mean','dataUV_mean'); */
            exitg2 = 1;
          }
        } while (exitg2 == 0U);

        emxFree_real_T(&b_dataIR);
        emxFree_real_T(&b_dataUV);
        emxFree_real_T(&dataUV_mean);
        emxFree_real_T(&dataIR_mean);
      }

      emxFree_real_T(&dataUV);
      emxFree_real_T(&dataIR);
    }
  }
}

/* End of code generation (meanfile.c) */
