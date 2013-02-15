/*
 * gfit_types.h
 *
 * Code generation for function 'gfit_rdfile'
 *
 * C source code generated on: Thu Feb 14 17:57:51 2013
 *
 */

#ifndef __GFIT_TYPES_H__
#define __GFIT_TYPES_H__

/* Type Definitions */
#ifndef struct_emxArray__common
#define struct_emxArray__common
typedef struct emxArray__common
{
    void *data;
    int32_T *size;
    int32_T allocatedSize;
    int32_T numDimensions;
    boolean_T canFreeData;
} emxArray__common;
#endif
#ifndef struct_emxArray_real_T
#define struct_emxArray_real_T
typedef struct emxArray_real_T
{
    real_T *data;
    int32_T *size;
    int32_T allocatedSize;
    int32_T numDimensions;
    boolean_T canFreeData;
} emxArray_real_T;
#endif
#ifndef struct_emxArray_real_T_3
#define struct_emxArray_real_T_3
typedef struct emxArray_real_T_3
{
    real_T data[3];
    int32_T size[1];
} emxArray_real_T_3;
#endif

#endif
/* End of code generation (gfit_types.h) */
