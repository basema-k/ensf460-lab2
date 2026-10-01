/*
 * File:   IOs.c
 * Author: Basema Khan, Michelle Yoon and Vincent Fong
 *
 * Created on September 29, 2026, 8:49 PM
 */


#include "xc.h"

void IOinit(){
    AD1PCFG = 0xFFFF; /* keep this line as it sets I/O pins that can also be analog to be digital */

    // inputs
    TRISBbits.TRISB7 = 1; // RB7
    TRISBbits.TRISB4 = 1; // RB4
    TRISAbits.TRISA4 = 1; // RA4
    
    // outputs
    TRISBbits.TRISB9 = 0; // RB9
    TRISAbits.TRISA6 = 0; // RA6
    
}

void IOcheck(){
    
}
