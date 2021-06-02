/*
 * File:   7 segment 2digit.c
 * Author: KO
 *
 * Created on April 30, 2020, 12:15 PM
 */



// PIC16F877A Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = ON         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include<pic.h>
#define _XTAL_FREQ 8000000

void main()
{   
    TRISC = 0x00;
    PORTC = 0x00;
    TRISD = 0x00;
   
    int LED[10]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
    //            0    1    2    3    4     5   6    7    8    9
    // Give LOW for 1pin 2pin of 7 segment 
    
    for(int k=0;k<10;k++)
    {                      
        for(int i=0;i<10;i++)
        {  
            for(int j=0;j<100;j++)
            {
                RD0=0;
                PORTC=LED[k];
                __delay_ms(5);RD0=1;
                RD1=0;
                PORTC=LED[i];
                __delay_ms(5);RD1=1;
            }    
        }
        
    }
}

  