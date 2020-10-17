/*
 *  Copyright 2010 by Spectrum Digital Incorporated.
 *  All rights reserved. Property of Spectrum Digital Incorporated.
 */

/*
 *  GPIO header file
 *
 */

#ifndef GPIO_
#define GPIO_

#include "usbstk5515.h"

#define GPIO_IN                 0
#define GPIO_OUT                1

#define GPIO0                   0x00
#define GPIO1                   0x01
#define GPIO2                   0x02
#define GPIO3                   0x03
#define GPIO4                   0x04
#define GPIO5                   0x05
#define GPIO6                   0x06
#define GPIO7                   0x07
#define GPIO8                   0x08
#define GPIO9                   0x09

#define GPIO10                  0x0A
#define GPIO11                  0x0B
#define GPIO12                  0x0C
#define GPIO13                  0x0D
#define GPIO14                  0x0E
#define GPIO15                  0x0F
#define GPIO16                  0x10
#define GPIO17                  0x11
#define GPIO18                  0x12
#define GPIO19                  0x13

#define GPIO20                  0x14
#define GPIO21                  0x15
#define GPIO22                  0x16
#define GPIO23                  0x17
#define GPIO24                  0x18
#define GPIO25                  0x19
#define GPIO26                  0x1A
#define GPIO27                  0x1B
#define GPIO28                  0x1C
#define GPIO29                  0x1D

#define GPIO30                  0x1E
#define GPIO31                  0x1F


/* ------------------------------------------------------------------------ *
 *  Prototypes                                                              *
 * ------------------------------------------------------------------------ */
Int16 USBSTK5515_GPIO_init         ( );
Int16 USBSTK5515_GPIO_setDirection ( Uint16 number, Uint16 direction );
Int16 USBSTK5515_GPIO_setOutput    ( Uint16 number, Uint16 output );
Int16 USBSTK5515_GPIO_getInput     ( Uint16 number );

#endif
