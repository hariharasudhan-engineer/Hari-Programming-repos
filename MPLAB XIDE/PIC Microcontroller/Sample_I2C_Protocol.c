/*
 * File:   Sample_I2C_Protocol.c
 * Author: KO
 *
 * Created on June 8, 2020, 10:08 AM
 */

// PIC16F877A Configuration Bit Settings

// 'C' source line config statements

// CONFIG
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

#define SDA RC4
#define SCL RC3


void I2C_Initialize(long long int freq)
{
    TRISC3=TRISC4=1;
    SSPCON = 0b00101000;   // Set SSPEN and SSPM3:SSPM0(1000 = I2C Master mode, clock = FOSC/(4 * (SSPADD + 1)) )
    SSPCON2 = 0x00;
    SSPADD = (_XTAL_FREQ/(4*freq))-1;    //When it is in master mode freq is store into SSPADD
    SSPSTAT = 0x00;
}
void I2C_Busy()
{
    while((SSPCON2 & 0b00011111) || (SSPSTAT & 0b00000100));     // Check whether I2C is in progress
}
void I2C_Start()
{
    I2C_Busy();
    SEN = 1;            // SEN--->start enable bit
}
void I2C_RepeatedStart()
{
    I2C_Busy();
    RSEN = 1;             // RSEN--->repeated start enable bit
}
void I2C_Stop()
{
    I2C_Busy();
    PEN = 1;                   // PEN--->stop enable bit
}
void I2C_Write(unsigned char data)
{
    I2C_Busy();
    SSPBUF = data;             // Store the data into SSPBUF
    __delay_ms(100);
    PORTD = SSPBUF;
    __delay_ms(100);
}
void I2C_Read(unsigned char a)
{
      unsigned char temp;
    I2C_Busy();
    RCEN=1;      // Enable Receive Mode for I2cC
    I2C_Busy();
    temp = SSPBUF;            // Store data into temp from SSPBUF
    I2C_Busy();
    ACKDT = (ack)?0:1;      // 0--> NACK & 1--> ACK
    ACKEN = 1;          // Send Acknowledge
    return temp;  
    /*In this function uses unsigned char datatype 
     * because void doesn't return
     *  but this function must return temp value      */
}

/****** Write data to slave---> START -> WRITE SLAVE ADDRESS -> WRITE REGISTER ADDRESS
 *  -> WRITE DATA -> STOP.*******/

/**** Read data from slave---> START -> WRITE SLAVE ADDRESS -> WRITE REGISTER ADDRESS ->
 *   REPEATED START ->WRITE SLAVE ADDRESS + 0x01 -> READ DATA -> STOP****/
void main()
{
    TRISB = 0XFF;
    TRISD = 0X00;
    PORTB = PORTD = 0X00;
    
    I2C_Initialize(100000);       //I2C standard speed 100kHz
    I2C_Start();
    //I2C_Write(0x30); // Slave address with write bit(If u wanna to communicate with pic to pic)
    I2C_Write(PORTB);
    I2C_Stop();
    __delay_ms(200);
    
}