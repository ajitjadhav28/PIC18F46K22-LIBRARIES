/*
 * File:   DHT11.c
 * Author: Ajit Jadhav
 *
 * Created on June 20, 2016, 11:14 PM
 */

 /* DHT11 library is distributed under GNU GENERAL PUBLIC LICENSE.
  * http://www.gnu.org/licenses/
  * Copyright (c) 2016 Ajit Jadhav.
  */

/* Library currently doesn't support crystal frequency below 16MHz but will support in next update. */

#include <xc.h>

#include "DHT11.h"

// Define DHT11 sensor data pin here 
#define DHT11_RD PORTBbits.RB4
#define DHT11_WR LATBbits.LATB4
#define DHT11_DIR TRISBbits.TRISB4

/* Variables for parity, Humidity and Temperature */ 
volatile unsigned int par = 0, humC = 0, humF = 0, tempC = 0, tempF = 0;
unsigned int bitCounter = 0;    // Bit Counter
unsigned int rBuf[42];

/* Function to decide bit from pulse time given */
unsigned short whichBit(unsigned int bDelay) {
    if ((bDelay > 75 && bDelay < 95) || bDelay < 30)
        return 0;
    else
        return 1;
}

/* Function to read data from DHT11 sensor */
char readDHT11(void) {    
    unsigned int regL,regH;
    T0CON = TMR0PS; /* Timer 0 prescale 16 to increment timer 0 at 1 micro sec   */
    INTCON2bits.RBPU = 0; /* PortB pull up enable */
    WPUBbits.WPUB4 = 1; /* RB4 pull-up enable  */
    bitCounter = 41;
    DHT11_DIR = 0;
    DHT11_WR = 0; /* pulling wire low to initiate communication */
    __delay_ms(10);
    __delay_ms(10);
    DHT11_DIR = 1;
    while (bitCounter != -1) {
        TMR0H = 0;
        TMR0L = 0;
        par = tempC = tempF = humC = humF = 0;
        while (!DHT11_RD); /* measuring high pulse duration */
        T0CONbits.TMR0ON = 1;
        while (DHT11_RD) {
            if (INTCONbits.TMR0IF) { /* if timer overflows */
                INTCONbits.TMR0IF = 0;
                delay(2000);
                return 0;
            }
        }
        T0CONbits.TMR0ON = 0;
        regL = TMR0L;
        regH = TMR0H;
        rBuf[bitCounter--] = (regH << 8) | regL; /* reading timer 0 and buffering */
    }
    /* decoding data bits from buffered time array */
    for (bitCounter = 0; bitCounter != 42; bitCounter++) {
        rBuf[bitCounter] = whichBit(rBuf[bitCounter]);
        if (bitCounter < 8)
            par |= (rBuf[bitCounter] << bitCounter);
        if (bitCounter < 16 && bitCounter > 7)
            tempF |= (rBuf[bitCounter] << (bitCounter - 8));
        if (bitCounter < 24 && bitCounter > 15)
            tempC |= (rBuf[bitCounter] << (bitCounter - 16));
        if (bitCounter < 32 && bitCounter > 23)
            humF |= (rBuf[bitCounter] << (bitCounter - 24));
        if (bitCounter < 40 && bitCounter > 31)
            humC |= (rBuf[bitCounter] << (bitCounter - 32));
    }
    if(isCorrectData())
        return 1;
    else
        return 0;
}

// Checking if received data is correct
inline char isCorrectData(void){
    if(par == (tempC+tempF+humF+humC))
        return 1;
    else
        return 0;
}
