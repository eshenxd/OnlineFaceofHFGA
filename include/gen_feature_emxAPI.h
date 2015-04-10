/*
 * gen_feature_emxAPI.h
 *
 * Code generation for function 'gen_feature_emxAPI'
 *
 * C source code generated on: Wed Apr 01 19:44:30 2015
 *
 */

#ifndef __GEN_FEATURE_EMXAPI_H__
#define __GEN_FEATURE_EMXAPI_H__
/* Include files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "rtwtypes.h"
#include "gen_feature_types.h"

/* Function Declarations */
extern emxArray_real_T *emxCreateND_real_T(int32_T numDimensions, int32_T *size);
extern emxArray_real_T *emxCreateWrapperND_real_T(real_T *data, int32_T numDimensions, int32_T *size);
extern emxArray_real_T *emxCreateWrapper_real_T(real_T *data, int32_T rows, int32_T cols);
extern emxArray_real_T *emxCreate_real_T(int32_T rows, int32_T cols);
extern void emxDestroyArray_real_T(emxArray_real_T *emxArray);
#endif
/* End of code generation (gen_feature_emxAPI.h) */
