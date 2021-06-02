/*
 * File:   Sample_UART.c
 * Author: KO
 *
 * Created on June 30, 2020, 4:31 PM
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
#define Baudrate 9600

void UART_Initialize()
{
    TRISC6=0;//Make this pin as '0' for Tx
    TRISC7=1;// make this pin as'1' for Rx
    SPBRG=((_XTAL_FREQ/16)/Baudrate)-1; //Generate baud rate generator and store it into SPBRG
    BRGH=1; //Make BRGH high for enable high speed baud rate
    SYNC=0; // This id for ebale asynchronous bit
    SPEN=1; // Enable Tx and Rx pin
    TXEN=1;  //Enable Tx pin
    CREN=1;  //Enable Continuous receive 
    TX9=0; //Enable for selecting 8bit mode for Tx
    RX9=0; //Enable for selecting 8bit mode for Rx
}
//  function to send one bit to UART
void UART_TxChar(unsigned char bt ) // PIC to computer
{
    while(!TXIF); //Wait till flag bit as low( for confirm there is no transmission)
    TXREG=bt;  // load data into TXREG and TXREG will automatically load data into TSR register(it not available in config side)
}
// function to send byte of data to UART
void UART_TxString(unsigned char *data) // PIC to computer
{
    int i;
    for(i=0;data[i]!='\0';i++)
    {
        UART_TxChar(data[i]);
    }
}
//function to get one bit from UART
char UART_RxChar()  //Computer to PIC
{
    if(OERR)
    {
        CREN=0;
        CREN=1;
    }
    while(!RCIF);
    return RCREG;
}
void main(void) {
    TRISB0=0;
    RB0=0;
    UART_Initialize();
    UART_TxString("UART is ready to send and receive data");
    while(1)
    {
        int value = UART_RxChar();
        if(value=='1')
        {
            RB0=1;
            UART_TxString("-->LED ON\n");
            UART_TxChar(10);  // ASCII value 10 is used to carriage return( to print in new line)
        }
        else if(value=='0')
        {
            RB0=0;
            UART_TxString("-->LED OFF\n");
            UART_TxChar(10);   // ASCII value 10 is used to carriage return( to print in new line)
        }
    }
    
    return;
}
