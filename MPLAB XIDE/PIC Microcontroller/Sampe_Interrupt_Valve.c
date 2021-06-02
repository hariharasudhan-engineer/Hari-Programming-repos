/*
 * File:   Gate_VlaveTimer2_16F877A.c
 * Author: KO
 *
 * Created on September 18, 2020, 2:44 PM
 */


#include <xc.h>
#include "lcd.h"
#include <stdlib.h>

#define _XTAL_FREQ 20000000

void CountDown(int);
void Break();
void CountINT();
void NumCompute(int);
void LcdDisplay(int);

int True=0,flag=0,ValveCount=0,arr=0,k=4,check=1;
long int m=0,n=0,l=0;
int a_ValveCount,b_ValveCount,c_ValveCount,d_ValveCount,vt;

int valve_time[15]={5,5,5,5,5,5,5,5,5,5,5,5,5,5,5};
int a_Num,b_Num,c_Num,d_Num;

int ValCount=0;
unsigned int i,Interruptflag=0;
unsigned int Interruptret1,Interruptret2;


void LcdDisplay(int a)
{
    a_ValveCount=a%10; //This seperate the double digit numbers
    b_ValveCount=a/10;
    //c_ValveCount=b_ValveCount%10;
    //d_ValveCount=b_ValveCount/10;                    
                    Lcd_Clear();
                    Lcd_Set_Cursor(1,4);
                    Lcd_Print_String("Valve");
                    Lcd_Set_Cursor(1,10);
                    Lcd_Print_Char(b_ValveCount+'0');
                    Lcd_Set_Cursor(1,11);
                    Lcd_Print_Char(a_ValveCount+'0');
                    Lcd_Set_Cursor(2,3);
                    Lcd_Print_String("Set = 05 Min");
                    __delay_ms(1000);
                    Lcd_Shift_Left();
                    __delay_ms(2000);
                    Lcd_Set_Cursor(2,3);
                    Lcd_Print_String("Press  Count");
}
void Break()
{
    ValCount=0;
    INTCON=0x90;
    Interruptflag=1;
}

void NumCompute(int a)
{
    a_Num=a%10; //This seperate the double digit numbers
    b_Num=a/10;
}
                    
void CountINT()
{
       int a,b;
       
       while(RB2==1 && flag==1)// This loop used for getting time from user by pressing the RB1 button 
    {
        flag=0,m=0;
        k+=1;//Initially 5min ON time set and it will increase whenever RB1 press
        
        a=k%10; //This seperate the double digit numbers
        b=k/10;
        NumCompute(ValCount);
        
        Lcd_Clear();
        Lcd_Set_Cursor(1,4);
        Lcd_Print_String("Valve");
        Lcd_Set_Cursor(1,10);
        Lcd_Print_Char(b_Num+'0');
        Lcd_Set_Cursor(1,11);
        Lcd_Print_Char(a_Num+'0');
        Lcd_Set_Cursor(2,1);
        Lcd_Print_String("Set = ");
        Lcd_Set_Cursor(2,6);
        Lcd_Print_Char(b+'0');// This is the syntax for displaying number in the stored value
        Lcd_Set_Cursor(2,7);
        Lcd_Print_Char(a+'0');
        Lcd_Set_Cursor(2,9);
        Lcd_Print_String("Min");
        Lcd_Set_Cursor(2,13);
        Lcd_Print_String("OK");
        }
    }

            
        
void CountDown(int valve_time1)  //After set the time individually, it will move on CountDown function
{
    int a_Min,b_Min;
    int a_Sec,b_Sec;
    int i,j;
    
        for(j=valve_time1-5;j>=0;j--) //This loop for minute
        {
        for(i=9;i>=0;i--) //This loop for seconds
        {
            a_Min=j%10;
            b_Min=j/10;
                        
            Lcd_Set_Cursor(2,9);
            Lcd_Print_Char(b_Min+'0');
            Lcd_Set_Cursor(2,10);
            Lcd_Print_Char(a_Min+'0');
            Lcd_Set_Cursor(2,11);
            Lcd_Print_String(":");
              
            a_Sec=i%10;
            b_Sec=i/10;
                        
            Lcd_Set_Cursor(2,12);
            Lcd_Print_Char(b_Sec+'0');
            Lcd_Set_Cursor(2,13);
            Lcd_Print_Char(a_Sec+'0');
            __delay_ms(1000);
        }
        }
    }
        



void __interrupt() myIsr(void)   //This is special function for interrupt
{
    if(INTF==1) //This will check whether interrupt occurred or not if occurred means it will proceed next else display selkon...
        { 
            INTF=0;
            INTE=0;
            //CorrectSwitch=1;
            PORTC=0xFF;
            ValCount=0;
            ValCount+=1;
            LcdDisplay(ValCount);
        while(ValCount<16)
        {
            check=0;
        while(check<2)
            {
            if(RB0==0)
            {
                ValCount+=1;
                if(ValCount<16)
                    {
                    LcdDisplay(ValCount);
                    }
                if(ValCount>=16)
                    {
                    ValCount=1;
                    LcdDisplay(ValCount);
                    }
            }
            else
            {
                if(RB1==0)
                {
                    check=2;
                }
            }
        }
        check=0;
        while(check<2)
        { 
            if(RB2==0)
            {
                flag=1;
                CountINT();
            }
            else
            {
                if(RB1==0)
                {
                    valve_time[ValCount-1]=k;
                    ValCount+=1;   
                    check=2;
                }
            }
        }
        
        }
Break();
    }
}     
       

void main() 
{
    TRISD=0x00;//LCD Connected
    PORTD=0x00;
    TRISC=0x00;//Decoder for Valve Switching
    PORTC=0xFF;// Initially No VALVE to be SET to ON
    TRISB2=1;
    TRISB1=1;
    TRISB0=1;
    
    INTCON=0x90;
    while(1)
    {
        
    }
    
    Interruptret1=PCLATH;
    Interruptret2=PCL;
    
    Lcd_Start();
    Lcd_Clear();
        Lcd_Set_Cursor(1,1);
        Lcd_Print_String("Selkon GateValve");
        Lcd_Set_Cursor(2,1);
        Lcd_Print_String("Controller Erode");    //Display 'Selkon' until make an interrupt so that infinite for loop used
        __delay_ms(2000);
        
        Lcd_Clear(); 
        Lcd_Set_Cursor(1,2);
        Lcd_Print_String("Call 09655321216");
        __delay_ms(3000);
        
        
        
        
    while(1)
    {
        for(int x=1;x<=15;x++)
            {
                if(Interruptflag==1)
                {
                    Interruptflag=0;
                    PCLATH=Interruptret1;
                    PCL=Interruptret2;
                }
                else
                {
                }
                PORTC=x-1;
                Lcd_Clear();
                Lcd_Set_Cursor(1,4);
                Lcd_Print_String("Valve ");
                NumCompute(x);
                Lcd_Set_Cursor(1,11);
                Lcd_Print_Char(b_Num+'0');
                Lcd_Set_Cursor(1,12);
                Lcd_Print_Char(a_Num+'0');
                Lcd_Set_Cursor(2,3);
                Lcd_Print_String("Run = ");
                
                NumCompute(valve_time[x-1]);
                Lcd_Set_Cursor(2,9);
                Lcd_Print_Char(b_Num+'0');
                Lcd_Set_Cursor(2,10);
                Lcd_Print_Char(a_Num+'0');
                Lcd_Set_Cursor(2,11);
                Lcd_Print_String("Min");
                CountDown(valve_time[x-1]);
            
            
        }
    }
}
