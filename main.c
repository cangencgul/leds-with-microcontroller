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
int LEDNumber = 0;
int LEDS[] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04}; 

void flashLED(LEDNumber){
    PORTB = LEDS[LEDNumber];
    __delay_ms(250);
}

void main(void) {
    TRISA = 0x01;
    TRISB = 0x00;
    PORTA = 0x00;
    PORTB = 0x00;
    energy = energyOFF;
    while(1){
        if (RA0 = 1){
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
                    LEDNumber += 1;
                    LEDNumber %= 6;
                }
                if (direction == RIGHT){
                    LEDNumber += 5;
                    LEDNumber %= 6;                    
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
