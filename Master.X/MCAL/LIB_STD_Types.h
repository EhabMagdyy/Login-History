/******************************************************************
**********************  Author: Ehab Magdy       ******************
**********************	File  : LIB_STD_Types.h  ******************
**********************	Date  : 06 Sep, 2023     ******************
*******************************************************************/

#ifndef LIB_STD_TYPES_H
#define	LIB_STD_TYPES_H

/* --------------------------- Includes ---------------------------- */
#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/* ---------------------- Macro Declarations ----------------------- */
#define _XTAL_FREQ  4000000

#define E_OK            0x01
#define E_NOT_OK        0x00

/*-------------------- Macro Function Declarations --------------------*/

/*---------------------- Data Types Declarations --------------------- */
typedef unsigned char   uint8;
typedef unsigned short  uint16;
typedef unsigned long   uint32;
typedef signed char     sint8;
typedef signed short    sint16;
typedef signed long     sint32;

typedef uint8   Std_ReturnType;

/*----------------------- Function Declarations ---------------------- */


#endif	/* LIB_STD_TYPES_H */

