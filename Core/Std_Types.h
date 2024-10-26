#ifndef STD_TYPES_H
#define STD_TYPES_H

/* Include standard libraries if needed */
#include <stdint.h>

/* AUTOSAR standard types */
typedef uint8_t     uint8;
typedef uint16_t    uint16;
typedef uint32_t    uint32;
typedef uint64_t    uint64;

typedef int8_t      sint8;
typedef int16_t     sint16;
typedef int32_t     sint32;
typedef int64_t     sint64;

typedef uint8_t     Std_ReturnType; /* Return Type for standard functions */

/* Standard Return Values */
#define E_OK        0x00U   /* Function completed successfully */
#define E_NOT_OK    0x01U   /* Function encountered an error */

/* Null pointer definition */
#ifndef NULL_PTR
    #define NULL_PTR ((void*)0)
#endif

#endif /* STD_TYPES_H */
