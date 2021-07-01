/*
 * File:   main.c
 * Author: can
 *
 * Created on 10 ?ubat 2021 Çar?amba, 15:14
 */


#include <xc.h>

#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator)
#pragma config WDTE = OFF       // Watchdog Timer (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (Power-up Timer is disabled)
#pragma config CP = OFF         // Code Protection bit (Code protection disabled)

#define _XTAL_FREQ 4000000

enum {energyOFF, energyON};
enum {LEFT, RIGHT};
int energy = energyOFF;
int direction = LEFT;
unsigned char LEDNumber = 4;

void flashLED(LEDNumber){
    PORTB = LEDNumber;
    __delay_ms(250);
}

void main(void) {
    TRISA = 0x01;
    TRISB = 0x00;
    PORTA = 0x00;
    PORTB = 0x00;
    energy = energyOFF;
    while(1){
        if (RA0 == 1){
            if (energy == energyOFF){
                energy = energyON; 
                PORTB = 0x02;
                __delay_ms(1250);
                PORTB = 0x00;
            }
            else if (energy == energyON){
                energy = energyOFF;
                PORTB = 0x01;
                __delay_ms(1250);
                PORTB = 0x00;
            }
        }
        
        else if (RA1 == 1){
            while(energy == energyON){
                flashLED(LEDNumber); 
                if (direction == LEFT){
                    LEDNumber <<= 1;
                    if (LEDNumber == 0)LEDNumber = 4;
                }
                if (direction == RIGHT){
                    LEDNumber >>= 1;
                    if (LEDNumber == 2)LEDNumber = 128;                
                }
                if (RA0 == 1){
                    break;
                }
                if (RA2 == 1){
                    if(energy == energyON && direction == LEFT){
                    direction = RIGHT;
                    continue;
                    }
                    else if(energy == energyON && direction == RIGHT){
                    direction = LEFT;
                    continue;
                    }
                }

            }
        }
    }
}
