/*
 * File:   Sample_Bluetooth.c
 * Author: KO
 *
 * Created on June 30, 2020, 9:09 PM
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

void UART_BT_Initialize()
{
    TRISC6=0;
    TRISC7=1;
    BRGH=1;
    SPBRG=129; // for setting baud rate 9600(refer the formulae in UART project)
    SYNC=0;  //select asynchronous bit
    SPEN=1;  // serial port enable bit
    TXEN=1;
    CREN=1; // enbale continuous receive enable bit
    TX9=0;  // 8 bit mode
    RX9=0;  // 8 bit mode
    // enable global and pheripheral bit 
    GIE=1;
    PEIE=1;
    //Enable Tx and Rx interrupt
    RCIE=1;  // Enable USART receive interrupt
    TXIE=1;  // Enable USART transmit interrupt
}
// To load one bit of data into bluetooth RX buffer, from this broadcaster will send to mobile or computer
void UART_BT_Char(unsigned char bt)
{
    TXREG=bt;
    while(!TXIF);
    while(!TRMT);
}
// To load string of data into bluetooth RX buffer, from this broadcaster will send to mobile or computer
void UART_BT_String(unsigned char *data)
{
    while(*data)
        UART_BT_Char(*data++);
}

// To broadcast data from Rx Buffer via air which is already stored by PIC using above 2 functions
void UART_BT_Broadcast()
{
    TXREG=13; // ASCII value for carriage return(check ASCII vlaue 13)
    __delay_ms(500); // delay to start the broadcaster
}

// Get data from Rx buffer of BT to PIC
unsigned char UART_BT_GetChar()
{
    if(OERR==1)
    {
        CREN=0;
        CREN=1;
    }
    if(RCIF==1)
    {
        while(!RCIF);
        return RCREG;
    }
    else
        return 0;
}
void main(void) {
    TRISB0=0;
    UART_BT_Initialize();
    UART_BT_String("Bluetooth has activated");
    UART_BT_Broadcast();
    char value = UART_BT_GetChar(); //Read the character which is received via BT
    while(1)
    {
        if(value==1)
        {
            RB0=1;
            UART_BT_String("LED turned ON");
        }
        if(value==0)
        {
            RB0=0;
            UART_BT_String("LED turned OFF");
        }
    }
    return;
}
