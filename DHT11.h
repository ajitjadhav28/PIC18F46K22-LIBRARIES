
/* 
 * File: DHT11.h   
 * Author: Ajit Jadhav (mr.ajitjadhav@gmail.com)
 * Comments: 
 * Revision history: 1.0.0
 */

 /* DHT11 Library is distributed under GNU GENERAL PUBLIC LICENSE.
  * http://www.gnu.org/licenses/
  * Copyright (c) 2016 Ajit Jadhav.
  */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef DHT11_H
#define	DHT11_H
// Define crystal frequency
#define _XTAL_FREQ 16000000

// Setting timer prescaler bit to increment at every one micro second 
#ifdef _XTAL_FREQ
    #if _XTAL_FREQ == 64000000
        #define TMR0PS 3 
    #elif _XTAL_FREQ == 32000000
        #define TMR0PS 2
    #elif _XTAL_FREQ == 16000000
        #define TMR0PS 1
    #elif _XTAL_FREQ == 8000000
        #define TMR0PS 0
    #elif _XTAL_FREQ == 4000000 
        #define TMR0PS 8
    #endif
#endif
#ifndef _XTAL_FREQ
#error "_XTAL_FREQ not defined !"
#endif

#include <xc.h> // include processor files - each processor file is guarded.  

char readDHT11(void);
unsigned short whichBit(unsigned int);
inline char isCorrectData(void);

#endif	/* XC_HEADER_TEMPLATE_H */

