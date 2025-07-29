/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2018
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 
***************************************************************************/
/*
  * Utils.h
 *
 *  Created on: Feb 6, 2018
 *      Author: DShilonie
 *      
 *  Prototypes for various utilities and quick type safe useful macros that are used
 *  for all components, should be here.
 *  
 */

#ifndef UTILS_H_
#define UTILS_H_
#include <cmath>

// helper macros for boundary checking
#define _CHECKMAX(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })
     
#define _CHECKMIN(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })

// helper macros for function entry conditions 
#define _CHECK(expr) \
    if (!(expr)) \
		return;

#define _CHECKRETURN(expr,rtn) \
    if (!(expr)) \
		return rtn;

#define BIT_MASK(x)		(1<<x)
//helper to compare the float values
const float FLOAT_TOLERANCE = 0.0001f;
#define ARE_FLOATS_EQUAL(a, b) (fabs((a) - (b)) < FLOAT_TOLERANCE)

#endif
