/*
 * File:   Sample_Interrupt_LED.c
 * Author: KO
 *
 * Created on May 18, 2020, 10:25 AM
 */
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = ON         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.


#include <xc.h>
#define _XTAL_FREQ 20000000

#include<pic16f877A.h>
//This program is for run the program from void main after make an interrupt

unsigned int i,Interruptflag;
unsigned char Interruptret1,Interruptret2;
void __interrupt() myIsr(void)
{
    if(INTF==1)
    {
    INTF=0;
    Interruptflag=1;
    //unsigned char temp_PORTB = PORTB;
    RC1=0;
    RC2=1;
    __delay_ms(4000);
    RC2=0;
    __delay_ms(1000);
    }
    else if(RBIF==1)
    {
        RC0=RC1=RC2=0;
        RC3=1;
        __delay_ms(4000);
        RC3=0;
    }
}
void main(void)
{
    TRISB=0xFF;/*Port B as a Input */    
    TRISC=0x00;
    PORTC=0x00;
            /* Register PORTB interrupt */    //OPTION_REG = 0b00000000;
    INTCON = 0b10011000;
   Interruptret1=PCLATH;
    Interruptret2=PCL;
    RC1=0;
    RC0=1;
    __delay_ms(1000);
    RC0=0;
    __delay_ms(1000);
    while(1) 
    {
     RC1=1;  
     if(Interruptflag==1)
     {
     Interruptflag=0;
     PCLATH=Interruptret1;
     PCL=Interruptret2;
     }
     else
     {
         
     }
}
}

