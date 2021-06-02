// PIC16F877A Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = EXTRC     // Oscillator Selection bits (RC oscillator)
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

#define s0 PORTDbits.RD0
#define s1 PORTDbits.RD1
#define s2 PORTDbits.RD2
#define s3 PORTDbits.RD3
#define RS RD6
#define EN RD7
#define D4 RC0
#define D5 RC1
#define D6 RC2
#define D7 RC3

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
    TRISC=0x00;
    PORTC=0x00;
    TRISA=0XFF;
    TRISD=0x00;
    PORTD=0x00;
    TRISB=0X00;
    PORTB=0x00;
   ADC_Initialize();
   Lcd_Start();
   /* unsigned int seg[]={0X3F, //Hex value to display the number 0
                    0X06, //Hex value to display the number 1
                    0X5B, //Hex value to display the number 2
                    0X4F, //Hex value to display the number 3
                    0X66, //Hex value to display the number 4
                    0X6D, //Hex value to display the number 5
                    0X7C, //Hex value to display the number 6
                    0X07, //Hex value to display the number 7
                    0X7F, //Hex value to display the number 8
                    0X6F  //Hex value to display the number 9
                   }; //End of Array for displaying numbers from 0 to 9           */
    int a,b,c,d,e,f,g,h,adc;
    int i;
   // s0=1;s1=1;s2=1;s3=1;
    
    while(1)
    {
        Lcd_Clear();
        i=ADC_Read(4);
        //i=adc;
        
        a=i%10;
        b=i/10;
        c=b%10;
        d=b/10;
        e=d%10;
        f=d/10;
        g=f%10;
        h=f/10;
        
       Lcd_Set_Cursor(1,1);
       Lcd_Print_String("ADC Value:");
       Lcd_Set_Cursor(1,11);
       Lcd_Print_Char(g+'0');
       Lcd_Set_Cursor(1,12);
       Lcd_Print_Char(e+'0');
       Lcd_Set_Cursor(1,13);
      // Lcd_Print_Char('.');
      // Lcd_Set_Cursor(1,14);
       Lcd_Print_Char(c+'0');
       Lcd_Set_Cursor(1,14);
       Lcd_Print_Char(a+'0');
       __delay_ms(3000);
         
    }
   /* while(1)
    {
         adc=ADC_Read(4);
        i=adc*0.48828;
        
        a=i%10;
        b=i/10;
        c=b%10;
        d=b/10;
        e=d%10;
        f=d/10;
        g=f%10;
        h=f/10;
        PORTB = seg[g];s0=0;
        __delay_ms(5);s0=1;
        PORTB = seg[e];RB7=1;s1=0;
        __delay_ms(5);s1=1;
        PORTB = seg[c];s2=0;
        __delay_ms(5);s2=1;
        PORTB = seg[a];s3=0;
        __delay_ms(5);s3=1;
       
       __delay_ms(5);
    }*/
   
}
