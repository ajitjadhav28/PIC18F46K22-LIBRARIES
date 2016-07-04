/* 
 * File: eepromRW.h  
 * Author: Ajit Jadhav
 * Comments: Function definations for eepromRW.c    
 * Revision history: 1.0.0
 */
 
 /* PIC18F46K22-LIBRARIES is distributed under GNU GENERAL PUBLIC LICENSE.
 * http://www.gnu.org/licenses/
 * Copyright (c) 2016 Ajit Jadhav.
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef EEPROMRW_H
#define	EEPROMRW_H

#include <xc.h> // include processor files - each processor file is guarded.  

char eepromRead(unsigned int);
char eepromWrite(unsigned int, char);

#endif	/* XC_HEADER_TEMPLATE_H */

