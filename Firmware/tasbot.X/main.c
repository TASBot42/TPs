/* 
 * File:   main.c
 * Author: bocal
 *
 * Created on March 22, 2016, 1:54 PM
 */
#include <sys/attribs.h>
#include <xc.h>
#include <p32xxxx.h>
#include <stdbool.h>
#include "types.h"

void    tp1(void)
{
    LATFbits.LATF1 = 0;
    TRISFbits.TRISF1 = 0;
    int was_press = 0;
    while (true) {
        if (!PORTDbits.RD8) {
            if (!was_press) {
                was_press = 1;
                LATFbits.LATF1 = !LATFbits.LATF1;
            }
        }
        else
            was_press = 0;
    }
}

void    tp2(void)
{
    bool was_press = 0;
    LATFbits.LATF1 = 0;
    TRISFbits.TRISF1 = 0;
    T2CONbits.TCKPS = 6;
    T2CONbits.ON = 1;
    PR2 = 15625;
    while (1) {
        if (IFS0bits.T2IF) {
            IFS0bits.T2IF = 0;
            LATFbits.LATF1 = !LATFbits.LATF1;
        }
        if (!PORTDbits.RD8) {
            if (!was_press) {
                was_press = 1;
                if (T2CONbits.TCKPS == 2)
                    T2CONbits.TCKPS = 6;
                else
                    T2CONbits.TCKPS--;
            }
        }
        else
            was_press = 0;
    }
}

void    __ISR(7, IPL1AUTO)  button_change_timer(void)
{
            if (T2CONbits.TCKPS == 2)
                T2CONbits.TCKPS = 6;
            else
                T2CONbits.TCKPS--;
            IFS0bits.INT1IF = 0;
}

void    __ISR (8, IPL2AUTO) timer()
{
    IFS0bits.T2IF = 0;
    LATFbits.LATF1 = !LATFbits.LATF1;
}

void    tp3(void)
{

    LATFbits.LATF1 = 0;
    TRISFbits.TRISF1 = 0;
    T2CONbits.TCKPS = 6;
    T2CONbits.ON = 1;
    PR2 = 15625;
    
//    asm volatile("ei");     //enable interrupt
    __builtin_enable_interrupts(); // same as above
    INTCONbits.MVEC = 1;    // enables multi-vector mode

    INTCONbits.INT1EP = 0;  // detect le rising edge
    IEC0bits.INT1IE = 1;    // enables external interrupt from BUT
    IPC1bits.INT1IP = 1;    // Priority level same as sub priority
    IPC1bits.INT1IS = 1;    // SubPriority level

    IEC0bits.T2IE = 1;    // enables external interrupt from BUT
    IPC2bits.T2IP = 2;    // Priority level same as sub priority
    IPC2bits.T2IS = 2;    // SubPriority level

    while (1) {
        WDTCONbits.WDTCLR = 1;
    }
}

int main(void)
{
    tp3();
    return (0);
}