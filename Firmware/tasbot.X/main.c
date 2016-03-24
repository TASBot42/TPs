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
    u16 freq = 31250 / 8, start = freq, was_press = 0;
    LATFbits.LATF1 = 0;
    TRISFbits.TRISF1 = 0;
    T1CONbits.TCKPS = 3;
    T1CONbits.ON = 1;
    while (1) {
        if (TMR1 >= freq) {
            TMR1 = 0;
            LATFbits.LATF1 = !LATFbits.LATF1;
        }
        if (!PORTDbits.RD8) {
            if (!was_press) {
                was_press = 1;
                if (freq < start / 8)
                    freq = start;
                else
                    freq /= 2;
            }
        }
        else
            was_press = 0;
    }

}

int main(void)
{
    tp2();
    return (0);
}