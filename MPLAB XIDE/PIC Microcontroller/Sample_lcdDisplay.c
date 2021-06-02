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
#include <lcd.h>
#define _XTAL_FREQ 20000000



int main()
{
    unsigned int a;
    TRISD =0x00;
    int i;
    Lcd_Start();
   
    while(1)
    {
        Lcd_Clear();
         Lcd_Set_Cursor(1,1);
        Lcd_Print_String("Door Unlock");
        
        Lcd_Set_Cursor(2,1);
        Lcd_Print_String("Hello");
        
        Lcd_Set_Cursor(1,21);
        Lcd_Print_String("Friends");
        
        Lcd_Set_Cursor(2,21);
        Lcd_Print_String("Love");
        
        __delay_ms(1000);
                       
    }
    return 0;
}








