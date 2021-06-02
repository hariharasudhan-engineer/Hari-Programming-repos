/*
 * File:   Smaple_LM35 Temp Sensor.c
 * Author: KO
 *
 * Created on June 23, 2020, 12:26 PM
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

void ADC_Initialize()
{
 ADCON0=0b01100001;
 ADCON1=0b11000000;
}
unsigned int ADC_Read(unsigned char channel)
{
  ADCON0 &= 0b11000101; //Clearing the Channel Selection Bits
  ADCON0 |= channel<<3; //Setting the required Bits
  __delay_ms(2); //Acquisition time to charge hold capacitor
  GO_nDONE = 1; //Initializes A/D Conversion
  while(GO_nDONE); //Wait for A/D Conversion to complete
  return ((ADRESH<<8)+ADRESL); //Returns Result
}

int main() {
    TRISBbits.TRISB0=0;
    TRISA=0XFF;
    TRISD=0x00;
    PORTD=0x00;
    
   ADC_Initialize();
   Lcd_Start();
   int adc,i,a,b,c,d,e,f,g,h;
     while(1)
    {
        Lcd_Clear();
        adc=ADC_Read(4);
        i=adc*0.48828*100;
        if(i<=32)
        {
            RB0=1;
        }
        else
        {
            RB0=0;
        }
     /*   a=i%10;
        b=i/10;
        c=b%10;
        d=b/10;
        e=d%10;
        f=d/10;
        g=f%10;
        h=f/10;
        
       Lcd_Set_Cursor(1,1);
       Lcd_Print_String("TempValue:");
       Lcd_Set_Cursor(1,11);
       Lcd_Print_Char(g+'0');
       Lcd_Set_Cursor(1,12);
       Lcd_Print_Char(e+'0');
       Lcd_Set_Cursor(1,14);
       Lcd_Print_Char('C');
       __delay_ms(3000);
       */  
    }
}
