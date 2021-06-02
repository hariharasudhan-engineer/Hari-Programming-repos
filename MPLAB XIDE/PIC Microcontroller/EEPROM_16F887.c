/*
 * File:   EEPROM_16F887.c
 * Author: KO
 *
 * Created on September 25, 2020, 5:11 PM
 */


// PIC16F887 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FOSC = INTRC_CLKOUT// Oscillator Selection bits (INTOSC oscillator: CLKOUT function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = ON         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown Out Reset Selection bits (BOR enabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <stdint.h>
#define _XTAL_FREQ 8000000

int valve_time[15]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int Address, Data;

//void EEPROM_Write(long int,long int);

void EEPROM_Write(Address,Data)
{
    //valve_time[Address]=Data;
EEADR = Address; // Writes The Addres To Which We'll Wite Our Data
EEDAT = Data; // Write The Data To Be Saved
EECON1bits.EEPGD = 0; // Cleared To Point To EEPROM Data Memory
EECON1bits.WREN = 1; // Enable The Operation !
INTCONbits.GIE = 0; // Disable All Interrupts Untill Writting Data Is Done
EECON2 = 0x55; // Part Of Writing Mechanism..
EECON2 = 0xAA; // Part Of Writing Mechanism..
EECON1bits.WR = 1; // Part Of Writing Mechanism..
__delay_ms(100);
if(PIR2bits.EEIF==1)
{
    PIR2bits.EEIF=0;
EECON1bits.WREN = 0; // Disable The Operation
EECON1bits.WR = 0; // Ready For Next Writting Operation
}
INTCONbits.GIE = 1; 
}


void main() 
{
    OSCCON=0x70; // SELECT INTERNAL 8MHz OSCILLATOR
 
  
    for(int arr=0;arr<15;arr++)
    {
        EEPROM_Write(arr,0);
        EEPROM_Write(arr+15,01);
    }  
    EEPROM_Write(121,0);
   // EEPROM_Write(31,7);
   // EEPROM_Write(32,8);
   // EEPROM_Write(33,7);
    //EEPROM_Write(34,1);
}
