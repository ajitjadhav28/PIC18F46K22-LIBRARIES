/*
 * File: eepromRW.c
 * Author: Ajit Jadhav
 * Comment: This library is created to reaad and write data from internal eeprom of PIC 
 * Version: 1.0.0
 * Created on 17 June, 2016, 8:55 PM
 */

/* PIC18F46K22-LIBRARIES is distributed under GNU GENERAL PUBLIC LICENSE.
 * http://www.gnu.org/licenses/
 * Copyright (c) 2016 Ajit Jadhav.
 */

#include <xc.h>
#include "eepromRW.h"

char eepromRead(unsigned int adr) {
    char db;
    EEADR = (char)(0x00ff & adr);
    EEADRH = (char)((0xff00 & adr) >> 8);
    EECON1bits.EEPGD = 0;
    EECON1bits.CFGS = 0;
    EECON1bits.RD = 1;
    db = EEDATA;
    return db;
}

char eepromWrite(unsigned int addr, char dataByte) {
    EEADR = (char) (0x00ff & addr);
    EEADRH = (char) ((0xff00 & addr) >> 8);
    EEDATA = dataByte;
    EECON1bits.EEPGD = 0;
    EECON1bits.CFGS = 0;
    EECON1bits.WREN = 1;
    INTCONbits.GIE = 0;
    EECON2 = 0x55;
    EECON2 = 0xAA;
    EECON1bits.WR = 1;
    INTCONbits.GIE = 1;
    __delay_ms(1);
    if (PIR2bits.EEIF) {
        PIR2bits.EEIF = 0;
        return 1;
    } else
        return 0;
}
