/*
 * gen_feature_emxutil.h
 *
 * Code generation for function 'gen_feature_emxutil'
 *
 * C source code generated on: Wed Apr 01 19:44:30 2015
 *
 */

#ifndef __GEN_FEATURE_EMXUTIL_H__
#define __GEN_FEATURE_EMXUTIL_H__
/* Include files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "rtwtypes.h"
#include "gen_feature_types.h"

/* Function Declarations */
extern void emxEnsureCapacity(emxArray__common *emxArray, int32_T oldNumel, int32_T elementSize);
extern void emxFree_real_T(emxArray_real_T **pEmxArray);
extern void emxInit_real_T(emxArray_real_T **pEmxArray, int32_T numDimensions);
#endif
/* End of code generation (gen_feature_emxutil.h) */
