/*
 * gen_feature_types.h
 *
 * Code generation for function 'gen_feature'
 *
 * C source code generated on: Wed Apr 01 19:44:30 2015
 *
 */

#ifndef __GEN_FEATURE_TYPES_H__
#define __GEN_FEATURE_TYPES_H__

/* Include files */
#include "rtwtypes.h"

/* Type Definitions */
#ifndef struct_emxArray__common
#define struct_emxArray__common
struct emxArray__common
{
    void *data;
    int32_T *size;
    int32_T allocatedSize;
    int32_T numDimensions;
    boolean_T canFreeData;
};
#endif /*struct_emxArray__common*/
#ifndef struct_emxArray_b_real_T_56x56
#define struct_emxArray_b_real_T_56x56
struct emxArray_b_real_T_56x56
{
    real_T data[3136];
    int32_T size[2];
};
#endif /*struct_emxArray_b_real_T_56x56*/
#ifndef struct_emxArray_real_T
#define struct_emxArray_real_T
struct emxArray_real_T
{
    real_T *data;
    int32_T *size;
    int32_T allocatedSize;
    int32_T numDimensions;
    boolean_T canFreeData;
};
#endif /*struct_emxArray_real_T*/
#ifndef struct_emxArray_real_T_12x12
#define struct_emxArray_real_T_12x12
struct emxArray_real_T_12x12
{
    real_T data[144];
    int32_T size[2];
};
#endif /*struct_emxArray_real_T_12x12*/
#ifndef struct_emxArray_real_T_24x24
#define struct_emxArray_real_T_24x24
struct emxArray_real_T_24x24
{
    real_T data[576];
    int32_T size[2];
};
#endif /*struct_emxArray_real_T_24x24*/
#ifndef struct_emxArray_real_T_28x28
#define struct_emxArray_real_T_28x28
struct emxArray_real_T_28x28
{
    real_T data[784];
    int32_T size[2];
};
#endif /*struct_emxArray_real_T_28x28*/
#ifndef struct_emxArray_real_T_4x4
#define struct_emxArray_real_T_4x4
struct emxArray_real_T_4x4
{
    real_T data[16];
    int32_T size[2];
};
#endif /*struct_emxArray_real_T_4x4*/
#ifndef struct_emxArray_real_T_8x8
#define struct_emxArray_real_T_8x8
struct emxArray_real_T_8x8
{
    real_T data[64];
    int32_T size[2];
};
#endif /*struct_emxArray_real_T_8x8*/
typedef struct
{
    real_T a[10800];
} struct_T;
typedef struct
{
    struct_T lay;
} b_struct_T;
typedef struct
{
    char_T type;
    real_T b[4];
    real_T outputmaps;
    real_T kernelsize;
    real_T a[12544];
    real_T k[300];
} c_struct_T;
typedef struct
{
    c_struct_T lay;
} d_struct_T;
typedef struct
{
    char_T type;
    real_T scale;
    real_T b[4];
    real_T a[3136];
} e_struct_T;
typedef struct
{
    e_struct_T lay;
} f_struct_T;
typedef struct
{
    char_T type;
    real_T b[8];
    real_T outputmaps;
    real_T kernelsize;
    real_T a[4608];
    real_T k[800];
} g_struct_T;
typedef struct
{
    g_struct_T lay;
} h_struct_T;
typedef struct
{
    char_T type;
    real_T scale;
    real_T b[8];
    real_T a[1152];
} i_struct_T;
typedef struct
{
    i_struct_T lay;
} j_struct_T;
typedef struct
{
    char_T type;
    real_T b[16];
    real_T outputmaps;
    real_T kernelsize;
    real_T a[1024];
    real_T k[3200];
} k_struct_T;
typedef struct
{
    k_struct_T lay;
} l_struct_T;
typedef struct
{
    char_T type;
    real_T scale;
    real_T b[16];
    real_T a[256];
} m_struct_T;
typedef struct
{
    m_struct_T lay;
} n_struct_T;
typedef struct
{
    b_struct_T net1;
    d_struct_T net2;
    f_struct_T net3;
    h_struct_T net4;
    j_struct_T net5;
    l_struct_T net6;
    n_struct_T net7;
} o_struct_T;

#endif
/* End of code generation (gen_feature_types.h) */
