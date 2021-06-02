/*
 * File:   I2C_RTC_DS1307.c
 * Author: KO
 *
 * Created on August 20, 2020, 10:12 AM
 */


// PIC16F887 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator: High-speed crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown Out Reset Selection bits (BOR enabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)
#pragma config LVP = ON         // Low Voltage Programming Enable bit (RB3/PGM pin has PGM function, low voltage programming enabled)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

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

int sec=00,min=37,hour=11,date=21,month=8,year=20;


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
    ACKDT = (ack)?0:1;      // 0--> NACK & 1--> ACK  ---> This logic will work only in this program 
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

/****** Functions for RTC module *******/

int  BCD_2_DEC(int to_convert)
{
   return (to_convert >> 4) * 10 + (to_convert & 0x0F); 
}

int DEC_2_BCD (int to_convert)
{
   return ((to_convert / 10) << 4) + (to_convert % 10);
}

void Write_Current_Time_Date()    // Initially set the time and date to RTC module.(Write time and date to RTC module)
{
   I2C_Start();       
   I2C_Write(0xD0);            // Initialize salve address plus write bit
   I2C_Write(0);   //This will indicate where write operation will perform
   I2C_Write(DEC_2_BCD(sec)); //update sec
   I2C_Write(DEC_2_BCD(min)); //update min
   I2C_Write(DEC_2_BCD(hour)); //update hour
   I2C_Write(1); //ignore updating day
   I2C_Write(DEC_2_BCD(date)); //update date
   I2C_Write(DEC_2_BCD(month)); //update month
   I2C_Write(DEC_2_BCD(year)); //update year      
   I2C_Stop();        
}

void Read_Current_Date_Time()  // Read the time and date from the RTC module
{
   //START to Read
   I2C_Start();       
   I2C_Write(0xD0);       // Initialize salve address plus write bit
   I2C_Write(0x00);    //This will indicate where write operation will perform
   I2C_Stop(); 
   
  //READ
   I2C_Start();
   I2C_Write(0xD0);                              // Initialize salve address plus read bit
   I2C_Write(0x00);
   I2C_RepeatedStart();
   I2C_Write(0xD1);
   sec = BCD_2_DEC(I2C_Read(1));    
   min = BCD_2_DEC(I2C_Read(1));   // Read sec from register 
   hour = BCD_2_DEC(I2C_Read(1));  
   I2C_Read(1);
   date = BCD_2_DEC(I2C_Read(1));  
   month = BCD_2_DEC(I2C_Read(1));  
   year = BCD_2_DEC(I2C_Read(0));                  
   I2C_Stop(); 
    
/*  //END Reading  
    I2C_Start();
    I2C_Write(0xD1);                              // Initialize data read
    I2C_Read(1);    
    I2C_Stop(); 
                        **********/
}

void main()
{
    TRISD=0x00;
    TRISE=0x00;
    PORTE=0x00;
    Lcd_Start();
    I2C_Initialize(100000);  // Standard 100khz frequency
    I2C_Busy();
    Write_Current_Time_Date();  
    Lcd_Clear();
    Lcd_Set_Cursor(1,1);
    Lcd_Print_String("  RTC with PIC");
    __delay_ms(2000); //display for 1.5sec
 
    while(1)
    {
      Read_Current_Date_Time(); //Read the current date and time from RTC module
    
    //Split the into char to display on lcd
     char sec_0 = sec%10;
     char sec_1 = (sec/10);
     char min_0 = min%10;
     char min_1 = min/10;
     char hour_0 = hour%10;
     char hour_1 = hour/10;
    char date_0 = date%10;
     char date_1 = date/10;
     char month_0 = month%10;
     char month_1 = month/10;
     char year_0 = year%10;
     char year_1 = year/10;
     
     if(hour_0==1 && hour_1==1 && min_0==7 && min_1==3 && sec_0==5 && sec_1==0)
     {
         RE0=1;
     }
  
       //Display the Time on the LCD screen
        Lcd_Clear();
        Lcd_Set_Cursor(1,1);
        Lcd_Print_String("TIME: ");
        Lcd_Print_Char(hour_1+'0');
        Lcd_Print_Char(hour_0+'0');
        Lcd_Print_Char(':');
        Lcd_Print_Char(min_1+'0');
        Lcd_Print_Char(min_0+'0');
        Lcd_Print_Char(':');
        Lcd_Print_Char(sec_1+'0');
        Lcd_Print_Char(sec_0+'0');
        
        //Display the Date on the LCD screen
        Lcd_Set_Cursor(2,1);
        Lcd_Print_String("DATE: ");
        Lcd_Print_Char(date_1+'0');
        Lcd_Print_Char(date_0+'0');
        Lcd_Print_Char(':');
        Lcd_Print_Char(month_1+'0');
        Lcd_Print_Char(month_0+'0');
        Lcd_Print_Char(':');
        Lcd_Print_Char(year_1+'0');
        Lcd_Print_Char(year_0+'0');         
        __delay_ms(500); //refresh for every 0.5 sec
    
    }
    return;
}
