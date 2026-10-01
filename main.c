/*
 * File:   main.c
 * Author: Basema Khan, Michelle Yoon, Vincent Fong
 *
 * Created on September 25, 2026, 8:49 AM
 */

// FBS
#pragma config BWRP = OFF               // Table Write Protect Boot (Boot segment may be written)
#pragma config BSS = OFF                // Boot segment Protect (No boot program Flash segment)

// FGS
#pragma config GWRP = OFF               // General Segment Code Flash Write Protection bit (General segment may be written)
#pragma config GCP = OFF                // General Segment Code Flash Code Protection bit (No protection)

// FOSCSEL
#pragma config FNOSC = FRC              // Oscillator Select (Fast RC oscillator (FRC))
#pragma config IESO = OFF               // Internal External Switch Over bit (Internal External Switchover mode disabled (Two-Speed Start-up disabled))

// FOSC
#pragma config POSCMOD = NONE           // Primary Oscillator Configuration bits (Primary oscillator disabled)
#pragma config OSCIOFNC = ON            // CLKO Enable Configuration bit (CLKO output disabled; pin functions as port I/O)
#pragma config POSCFREQ = HS            // Primary Oscillator Frequency Range Configuration bits (Primary oscillator/external clock input frequency greater than 8 MHz)
#pragma config SOSCSEL = SOSCHP         // SOSC Power Selection Configuration bits (Secondary oscillator configured for high-power operation)
#pragma config FCKSM = CSECMD           // Clock Switching and Monitor Selection (Clock switching is enabled, Fail-Safe Clock Monitor is disabled)

// FWDT
#pragma config WDTPS = PS32768          // Watchdog Timer Postscale Select bits (1:32,768)
#pragma config FWPSA = PR128            // WDT Prescaler (WDT prescaler ratio of 1:128)
#pragma config WINDIS = OFF             // Windowed Watchdog Timer Disable bit (Standard WDT selected; windowed WDT disabled)
#pragma config FWDTEN = OFF             // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))

// FPOR
#pragma config BOREN = BOR3             // Brown-out Reset Enable bits (Brown-out Reset enabled in hardware; SBOREN bit disabled)
#pragma config PWRTEN = ON              // Power-up Timer Enable bit (PWRT enabled)
#pragma config I2C1SEL = PRI            // Alternate I2C1 Pin Mapping bit (Default location for SCL1/SDA1 pins)
#pragma config BORV = V18               // Brown-out Reset Voltage bits (Brown-out Reset set to lowest voltage (1.8V))
#pragma config MCLRE = ON               // MCLR Pin Enable bit (MCLR pin enabled; RA5 input pin disabled)

// FICD
#pragma config ICS = PGx2               // ICD Pin Placement Select bits (PGC2/PGD2 are used for programming and debugging the device)

// FDS
#pragma config DSWDTPS = DSWDTPSF       // Deep Sleep Watchdog Timer Postscale Select bits (1:2,147,483,648 (25.7 Days))
#pragma config DSWDTOSC = LPRC          // DSWDT Reference Clock Select bit (DSWDT uses LPRC as reference clock)
#pragma config RTCOSC = SOSC            // RTCC Reference Clock Select bit (RTCC uses SOSC as reference clock)
#pragma config DSBOREN = ON             // Deep Sleep Zero-Power BOR Enable bit (Deep Sleep BOR enabled in Deep Sleep)
#pragma config DSWDTEN = ON             // Deep Sleep Watchdog Timer Enable bit (DSWDT enabled)

// #pragma config statements should precede project file includes.

#include <xc.h>
#include "clkChange.h"
#include "IOs.h"
#include "delay_ms.h"

// Remember, you can use the "extern" keyword to access global variables defined in other files
/**
 * extern int16_t flag_from_other_file;
 */

/**
 * You might find it useful to add your own #defines to improve readability here
 */

int main(void) {
    AD1PCFG = 0xFFFF; /* keep this line as it sets I/O pins that can also be analog to be digital */
    
    IOinit(); // call initialization function
    newClk(500);
    /*
    
    
    // clock 1 initialization (only for led2)
    T1CONbits.TCKPS = 3; // prescaler
    T1CONbits.TCS = 0; // internal clock
    
    IPC0bits.T1IP = 3;
    IFS0bits.T1IF = 0;
    IEC0bits.T1IE = 1;
    
    PR1 = 487;
    TMR1 = 0;
    
    T1CONbits.TON = 1; // start the timer
           
    
    LATBbits.LATB9 = 0; // led1 off
    LATAbits.LATA6 = 0; // led2 off
     */
    
    while(1) {
        IOcheck();
        /*
        if (PORTBbits.RB7 == 1) {
            if(PORTBbits.RB4 == 0){
                LATBbits.LATB9 = 1;
                delay_ms(1);
                LATBbits.LATB9 = 0;
                delay_ms(1);
            } else {
            LATBbits.LATB9 = 1;
            delay_ms(250);
            LATBbits.LATB9 = 0;
            delay_ms(250);
            }
        } 
        else if (PORTBbits.RB4 == 1) {
            LATBbits.LATB9 = 1;
            delay_ms(1000);   
            LATBbits.LATB9 = 0;
            delay_ms(1000); 
        }
        else if (PORTAbits.RA4 == 1){
            LATBbits.LATB9 = 1;
            delay_ms(6000);
            LATBbits.LATB9 = 0;
            delay_ms(6000);
        }
        else {
            LATBbits.LATB9 = 0;
        }
         */
    }
    
    return 0;
}

void __attribute__((interrupt, no_auto_psv)) _T1Interrupt(void){
    LATAbits.LATA6 = !LATAbits.LATA6; // set led2
    IFS0bits.T1IF = 0; // clear flag

}

