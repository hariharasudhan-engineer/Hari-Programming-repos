/*
 * File:   Sample_BLDC.c
 * Author: KO
 *
 * Created on July 9, 2020, 9:51 PM
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
#define _XTAL_FREQ 20000000

void main(void) {
    TRISD=0x00;
    TRISC=0xFF;
    while(1)
    {
        if(RC7==1 && RC6==0 && RC5==0)
        {
        RD0=1;RD1=0;
        RD2=0;RD3=0;
        RD4=0;RD5=1;
        __delay_ms(1);
        }
        else if(RC7==0 && RC6==0 && RC5==0)
        {
        RD0=1;RD1=0;
        RD2=0;RD3=1;
        RD4=0;RD5=0;
        __delay_ms(1);
        }
        else if(RC7==1 && RC6==0 && RC5==0)
        {
        RD0=0;RD1=0;
        RD2=0;RD3=1;
        RD4=1;RD5=0;
        __delay_ms(1);
        }
        else if(RC7==0 && RC6==1 && RC5==1)
        {
        RD0=0;RD1=1;
        RD2=0;RD3=0;
        RD4=1;RD5=0;
        __delay_ms(1);
        }
        else if(RC7==1 && RC6==1 && RC5==1)
        {
        RD0=0;RD1=1;
        RD2=1;RD3=0;
        RD4=0;RD5=0;
        __delay_ms(1);
        }
        else if(RC7==1 && RC6==1 && RC5==0)
        {
        RD0=0;RD1=0;
        RD2=1;RD3=0;
        RD4=0;RD5=1;
        __delay_ms(1);
        }
    }  
 
    while(1)
    {
        if(RC7==1 && RC6==1 && RC5==0)
        {
        RD0=0;RD1=0;
        RD2=1;RD3=0;
        RD4=0;RD5=1;
        __delay_ms(1);
        }
        
         else if(RC7==1 && RC6==1 && RC5==1)
        {
        RD0=0;RD1=1;
        RD2=1;RD3=0;
        RD4=0;RD5=0;
        __delay_ms(1);
        }
        
         else if(RC7==0 && RC6==1 && RC5==1)
        {
        RD0=0;RD1=1;
        RD2=0;RD3=0;
        RD4=1;RD5=0;
        __delay_ms(1);
        }
        
        else if(RC7==1 && RC6==0 && RC5==0)
        {
        RD0=0;RD1=0;
        RD2=0;RD3=1;
        RD4=1;RD5=0;
        __delay_ms(1);
        }
        
         else if(RC7==0 && RC6==0 && RC5==0)
        {
        RD0=1;RD1=0;
        RD2=0;RD3=1;
        RD4=0;RD5=0;
        __delay_ms(1);
        }
        
        else if(RC7==1 && RC6==0 && RC5==0)
        {
        RD0=1;RD1=0;
        RD2=0;RD3=0;
        RD4=0;RD5=1;
        __delay_ms(1);
        }
    }  
    
    return;
}
