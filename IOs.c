/*
 * File:   IOs.c
 * Author: Basema Khan, Michelle Yoon, Vincent Fong
 *
 * Created on September 30, 2026, 8:49 PM
 */


#include "xc.h"

void blinkLED(uint16_t time_ms){
    LATBbits.LATB9 = 1;
    delay_ms(time_ms);
    LATBbits.LATB9 = 0;
    delay_ms(time_ms);
}

void IOinit(){
    AD1PCFG = 0xFFFF; /* keep this line as it sets I/O pins that can also be analog to be digital */

    // inputs
    TRISBbits.TRISB7 = 1; // RB7
    TRISBbits.TRISB4 = 1; // RB4
    TRISAbits.TRISA4 = 1; // RA4
    
    // outputs
    TRISBbits.TRISB9 = 0; // RB9
    TRISAbits.TRISA6 = 0; // RA6
    
    CNPU2bits.CN23PUE = 1; // RB7 pull up low active (if pressed it is 0))
    CNPU1bits.CN1PUE = 1; // RB4 pull up low active (if pressed it is 0))
    CNPU1bits.CN0PUE = 1; // RA4 pull up low active (if pressed it is 0))
    
    LATBbits.LATB9 = 0;
    LATAbits.LATA6 = 0;
}

void IOcheck(){
    if (PORTBbits.RB7 == 0 && PORTBbits.RB4 == 0){
        blinkLED(1);
    }
    else if (PORTBbits.RB7 == 0){
        blinkLED(250);
    }
    else if (PORTBbits.RB4 == 0) {
        blinkLED(1000);
    }
    else if (PORTAbits.RA4 == 0){
        blinkLED(6000);
    }
    else {
        LATBbits.LATB9 = 0;
    }
    
}
