/*
 * convn.h
 *
 * Code generation for function 'convn'
 *
 * C source code generated on: Wed Apr 01 19:44:30 2015
 *
 */

#ifndef __CONVN_H__
#define __CONVN_H__
/* Include files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "rtwtypes.h"
#include "gen_feature_types.h"

/* Function Declarations */
extern void b_convn(const real_T A[3136], real_T C_data[3025], int32_T C_size[2]);
extern void c_convn(const real_T A[784], const real_T B[25], real_T C[576]);
extern void convn(const real_T A[3600], const real_T B[25], real_T C[3136]);
extern void d_convn(const real_T A[576], real_T C_data[529], int32_T C_size[2]);
extern void e_convn(const real_T A[144], const real_T B[25], real_T C[64]);
extern void f_convn(const real_T A[64], real_T C_data[49], int32_T C_size[2]);
#endif
/* End of code generation (convn.h) */
