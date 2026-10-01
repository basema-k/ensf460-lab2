#include "xc.h"
#include <stdint.h>

#define FCY 250000UL

static volatile uint8_t delayDone = 0;

void delay_ms(uint16_t time_ms){
    if (time_ms == 0) return;

    // 1:8 prescaler -> 31,250 ticks/s = 31.25 ticks/ms
    uint32_t ticks = ((uint32_t)time_ms * (FCY / 8)) / 1000;
    uint32_t PR = ticks - 1;

    T2CON = 0;                      // stop timer, clear T32 and settings
    T3CON = 0;
    TMR2 = 0;
    TMR3 = 0;
    IFS0bits.T2IF = 0;
    IFS0bits.T3IF = 0;
    T2CONbits.TCKPS = 1;            // 1:8, internal clock (TCS = 0)

    if (PR > 0xFFFF) {              // too big for 16 bits -> 32-bit mode
        T2CONbits.T32 = 1;
        PR3 = PR >> 16;             // high word
        PR2 = PR & 0xFFFF;          // low word
        IEC0bits.T2IE = 0;
        IPC2bits.T3IP = 4;
        IEC0bits.T3IE = 1;          // 32-bit mode interrupts on Timer3
    } else {
        PR2 = PR;
        IEC0bits.T3IE = 0;
        IPC1bits.T2IP = 4;
        IEC0bits.T2IE = 1;
    }

    delayDone = 0;
    T2CONbits.TON = 1;              // TON in T2CON starts both modes

    while (!delayDone) {
        Idle();                     // Timer1 also wakes us, so loop
    }
}

void __attribute__((interrupt, no_auto_psv)) _T2Interrupt(void){
    IFS0bits.T2IF = 0;
    T2CONbits.TON = 0;
    delayDone = 1;
}

void __attribute__((interrupt, no_auto_psv)) _T3Interrupt(void){
    IFS0bits.T3IF = 0;
    T2CONbits.TON = 0;              // 32-bit timer is controlled by T2CON
    delayDone = 1;
}
