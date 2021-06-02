/*
 * File:   Sample_I2C_Temperature.c
 * Author: KO
 *
 * Created on June 16, 2020, 11:13 AM
 */


// PIC16F877A Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF      // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>

#define _XTAL_FREQ 10000000
//************************* LCD Programs ***************************//

#define RS RD2
#define EN RD3
#define D4 RD4
#define D5 RD5
#define D6 RD6
#define D7 RD7
void Lcd_SetBit(char data_bit)
{
    if(data_bit&1)
        D4=1;
    else
        D4=0;
    if(data_bit&2)
        D5=1;
    else
        D5=0;
    if(data_bit&4)
        
        D6=1;
    else
        D6=0;
    if(data_bit&8)
        D7=1;
    else
        D7=0;
}
void Lcd_Cmd(char a)
{
    RS=0;
    Lcd_SetBit(a);
    EN=1;
    __delay_ms(4);
    EN=0;
}
void Lcd_Clear()
{
    Lcd_Cmd(0);
    Lcd_Cmd(1);
}
void Lcd_Set_Cursor(char a,char b)
{
    char temp,z,y;
    if(a==1)
    {
        temp=0x80+b-1;
        z=temp>>4;
        y=temp&0x0F;
       Lcd_Cmd(z);
        Lcd_Cmd(y);
    }
    else if(a==2)
    {
        temp=0xC0+b-1;
        z=temp>>4;
        y=temp&0x0F;
        Lcd_Cmd(z);
        Lcd_Cmd(y);
    }
}
void Lcd_Start()
{
    Lcd_SetBit(0x00);
   // for(int i=1065244;i<=0;i--) NOP();
   __delay_ms(5);
   /* Lcd_Cmd(0x03);
    __delay_ms(5);
    Lcd_Cmd(0x03);
    __delay_ms(11);
    Lcd_Cmd(0x03);    */
    Lcd_Cmd(0x02);
    Lcd_Cmd(0x02);
    Lcd_Cmd(0x08);
    Lcd_Cmd(0x00);
    Lcd_Cmd(0x0C);
    Lcd_Cmd(0x00);
    Lcd_Cmd(0x06);
}

void Lcd_Print_Char(char data)
{
    char Lower_Nibble,Upper_Nibble;
    Lower_Nibble=data&0x0F;
    Upper_Nibble=data&0xF0;
    RS=1;
    Lcd_SetBit(Upper_Nibble>>4);
    EN=1;
 //  for(unsigned int i=213048;i<=0;i--) NOP();
    __delay_ms(0.01);
    EN=0;
    Lcd_SetBit(Lower_Nibble);
    EN=1;
    //for(unsigned int i=213048;i<=0;i--) NOP();
    __delay_ms(0.01);
    EN=0;
}

void Lcd_Print_String(char *a)
{
    int i;
    for(i=0;a[i]!='\0';i++)
        Lcd_Print_Char(a[i]);
    
}


void I2C_Initialize(long int freq)
{
    TRISC3=TRISC4=1;
    SSPCON = 0b00101000;       // Set SSPEN and SSPM3:SSPM0(1000 = I2C Master mode, clock = FOSC/(4 * (SSPADD + 1)) )
    SSPCON2 = 0x00;
    SSPADD = (_XTAL_FREQ/(4*freq))-1; //When it is in master mode freq is store into SSPADD
    SSPSTAT = 0x00;
}
void I2C_Busy()
{
    while((SSPCON2 & 0b00011111) || (SSPSTAT & 0b00000100)); // Check whether I2C is in progress
}
void I2C_Start()
{
    I2C_Busy();
    SEN = 1;     // SEN--->start enable bit
}
void I2C_RepeatedStart()
{
    I2C_Busy(); 
    RSEN = 1;          // RSEN--->repeated start enable bit
}
void I2C_Stop()
{
    I2C_Busy();
    PEN = 1;         // PEN--->stop enable bit
}
void I2C_Write(unsigned char data)
{
    I2C_Busy();
    SSPBUF = data;  // Store the data into SSPBUF
}
unsigned char I2C_Read(unsigned char ack)
{
    unsigned char temp;
    I2C_Busy();
    RCEN=1;      // Enable Receive Mode for I2cC
    I2C_Busy();
    temp = SSPBUF;            // Store data into temp from SSPBUF
    I2C_Busy();
    ACKDT = (ack);      // 0--> NACK & 1--> ACK
    ACKEN = 1;          // Send Acknowledge
    return temp;  
    /*In this function uses unsigned char datatype 
     * because void doesn't return
     *  but this function must return a value      */
}

/****** Write data to slave---> START -> WRITE SLAVE ADDRESS -> WRITE REGISTER ADDRESS
 *  -> WRITE DATA -> STOP.*******/

/**** Read data from slave---> START -> WRITE SLAVE ADDRESS -> WRITE REGISTER ADDRESS ->
 *   REPEATED START ->WRITE SLAVE ADDRESS + 0x01 -> READ DATA -> STOP****/
void main()
{
    TRISD =0x00;
    Lcd_Start();
    I2C_Initialize(100000);  // Standard 100khz frequency
    unsigned char data;
    while(1)
    {
        I2C_Start();
        I2C_Write(0xA0);  // EEPROM 24AA00 slave address 
        I2C_Write(0x01);  // EEPROM command byte where data should write
        I2C_Write('H');   // Write data into 0x01 register
        I2C_Stop();
        
        __delay_ms(1000);  
           I2C_Start();
        I2C_Write(0xA0);  // EEPROM 24AA00 slave address 
        I2C_Write(0x01);  // EEPROM command byte where data should write
        I2C_RepeatedStart();
        I2C_Write(0xA0|0x01);  // EEPROM 24AA00 slave address with read bit 
        data = I2C_Read(1);    // Read data and send acknowledge
        I2C_Stop();
         __delay_ms(2000); 
        Lcd_Clear();
        Lcd_Set_Cursor(1,1);
        Lcd_Print_String("EEPROM");
        Lcd_Set_Cursor(1,7);  
        Lcd_Print_Char('-');
        Lcd_Set_Cursor(1,8);  
        Lcd_Print_Char(data);
        __delay_ms(3000);
    }
    return;
    
}