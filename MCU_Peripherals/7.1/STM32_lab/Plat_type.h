/*
 ******************************************************************************
 * @file           : Plat_type.c
 * @author         : Hassan Samy
 * @brief          : type definition for variables
 ******************************************************************************
 */
#ifndef PLAT_TYPES_H_
#define PLAT_TYPES_H_

#include <stdbool.h>

#ifndef _Bool
#define _Bool unsigned char
#endif

#ifndef FALSE
#define FALSE 							(boolean)false
#endif

#ifndef TRUE
#define TRUE 							(boolean)true
#endif

typedef _Bool 							boolean_t;
typedef signed char 					sint8_t;
typedef unsigned char 					uint8_t;
typedef char							char_t;
typedef signed short 					sint16_t;
typedef unsigned short 					uint16_t;
typedef signed int						sint32_t;
typedef unsigned int					uint32_t;
typedef signed long long 				sint64_t;
typedef unsigned long long				uint64_t;

typedef volatile signed char			vint8_t;
typedef volatile unsigned char			vuint8_t;

typedef volatile signed short 			vint16_t;
typedef volatile unsigned short			vuint16_t;

typedef volatile signed int 			vint32_t;
typedef volatile unsigned int			vuint32_t;

typedef volatile signed long long		vint64_t;
typedef volatile unsigned long long		vuint64_t;

#endif /* PLATFORM_TYPES_H_ */
