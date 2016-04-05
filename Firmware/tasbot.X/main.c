/* 
 * File:   main.c
 * Author: bocal
 *
 * Created on March 22, 2016, 1:54 PM
 */
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

void    tp3(void)
{
    while (1)
        ;
}

int main(void)
{
    tp2();
    return (0);
}