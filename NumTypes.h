#pragma once
#ifndef _GCPP18_NUM_TYPES_H_
#define _GCPP18_NUM_TYPES_H_

#ifdef EMBARCADERO_XE7
#include <stdint.h>
#include <float.h>
#define FLOAT_MIN   FLT_MIN
#define FLOAT_MAX   FLT_MAX
#define DOUBLE_MIN  DBL_MIN
#define DOUBLE_MAX  DBL_MAX
#endif
#ifndef EMBARCADERO_XE7
#include <inttypes.h>
//  #include <math.h>
//  #define FLOAT_MAX  MAXFLOAT
#define FLOAT_MAX  3.40282347e+38F
#define FLOAT_MIN  1.1755e-38
#endif

#ifdef FLOAT_PREC_SINGLE
typedef float float_t;
//  #define FLOAT_T_MIN  FLOAT_MIN
//  #define FLOAT_T_MAX  FLOAT_MAX
#endif
#ifndef FLOAT_PREC_SINGLE
typedef double float_t;

//  #define FLOAT_T_MIN  DOUBLE_MIN
//  #define FLOAT_T_MAX  DOUBLE_MAX
#endif

#define FLOAT_PI  3.14159265358979323846

#ifndef INT_MAX
#define INT_MAX    (2147483647L)
#endif
#ifndef INT_MIN
#define INT_MIN    (-2147483647L-1)
#endif

#endif