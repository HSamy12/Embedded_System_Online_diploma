/*
 ******************************************************************************
 * @file           : Plat_type.c
 * @author         : Hassan Samy
 * @brief          : type definition for variables
 ******************************************************************************
 */
#ifndef PLAT_TYPE_H_
#define PLAT_TYPE_H_

/* bool type vectors */
typedef unsigned char 		_bool;

/* integer types*/
typedef unsigned char 		uint8;
typedef signed 	 char 		sint8;
typedef unsigned short 		uint16;
typedef signed 	 short 		sint16;
typedef unsigned int 		uint32;
typedef signed 	 int 		sint32;
typedef unsigned long long 	uint64;
typedef signed 	 long long 	sint64;

/* volatile variables type */
typedef volatile unsigned  char 	v_uint8;
typedef volatile signed	   char 	v_sint8;
typedef volatile unsigned  short 	v_uint16;
typedef volatile signed    short 	v_sint16;
typedef volatile unsigned  int	 	v_uint32;
typedef volatile signed    int 		v_sint32;
typedef volatile unsigned long long	v_uint64;
typedef volatile signed   long long	v_sint64;

/* _bool values */
#define True  (_bool)1
#define False (_bool)0

#endif
