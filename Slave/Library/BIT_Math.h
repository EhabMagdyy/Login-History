/******************************************************************
**********************  Author: Ehab Magdy       ******************
**********************	File  : BIT_MATH.h       ******************
**********************	Date  : 06 Sep, 2023     ******************
*******************************************************************/

#ifndef BIT_MATH_H
#define BIT_MATH_H

#define SET_BIT(ADDRESS, BIT_POS)		(ADDRESS |= (1 << BIT_POS))
#define CLEAR_BIT(ADDRESS, BIT_POS)	    (ADDRESS &= ~(1 << BIT_POS))
#define TOGGLE_BIT(ADDRESS, BIT_POS)	(ADDRESS ^= (1 << BIT_POS))
#define READ_BIT(ADDRESS, BIT_POS)		((ADDRESS >> BIT_POS) & 1)

#endif /* BIT_MATH_H */
