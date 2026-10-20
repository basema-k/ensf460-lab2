
/*
 * File:   TimeDelay.c
 * Author: Basema Khan, Michelle Yoon, Vincent Fong
 *
 * Created on September 25, 2026, 9:47 AM
*/


#include "xc.h"
#define FCY 250000UL
#define TCY (1.0/FCY)

static volatile int T2_done = 1;

void delay_ms(uint16_t time_ms){
    double time_s = time_ms / 1000.0;
     // newClk(500);
    
    // prescaler is 1:8
    
    unsigned int new_FCY = FCY/8;
    double new_TCY = 1.0/new_FCY;
    
    unsigned long PR = (unsigned long)((time_s/new_TCY)-1);
    
    // timer setup
    if(time_s > 2.1){
        T2CONbits.T32 = 1;
        PR3 = (PR >> 16) & 0xFFFF;
        PR2 = PR & 0xFFFF;
        IPC2bits.T3IP = 4; // priority
        IFS0bits.T3IF = 0; // clear flag
        IEC0bits.T2IE = 0; // enable Timer2 interrupt
        IEC0bits.T3IE = 1;
    } else {
        T2CONbits.T32 = 0;
        PR2 = PR;
        IPC1bits.T2IP = 4; // priority
        IFS0bits.T2IF = 0; // clear flag
        IEC0bits.T2IE = 1; // enable Timer2 interrupt
        IEC0bits.T3IE = 0;
    }
    T2CONbits.TCKPS = 1; // select the prescaler (1:8)
    T2CONbits.TCS = 0; // select internal clock

   
    
    TMR2 = 0;
    TMR3 = 0;
    
    T2CONbits.TON = 1;
    
    while(T2_done){
        Idle(); // idle here till interrupt triggers
    }
    T2_done = 1;
    
}

void __attribute__((interrupt, no_auto_psv)) _T2Interrupt(void){
    IFS0bits.T2IF = 0;     // clear flag
    T2CONbits.TON = 0;     // stop timer
    T2_done = 0;
}

void __attribute__((interrupt, no_auto_psv)) _T3Interrupt(void){
    IFS0bits.T3IF = 0;     // clear flag
    T2CONbits.TON = 0;     
    T2_done = 0;
}

