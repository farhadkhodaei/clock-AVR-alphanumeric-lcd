/*****************************************************
This program was produced by the
CodeWizardAVR V2.05.3 Standard
Automatic Program Generator
© Copyright 1998-2011 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : 
Version : 
Date    : 10/1/2016
Author  : F
Company : 
Comments: 


Chip type               : ATmega48PA
AVR Core Clock frequency: 8.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 128
*****************************************************/

#include <mega48pa.h>

// I2C Bus functions
#include <i2c.h>

// DS1307 Real Time Clock functions
#include <ds1307.h>
#include <delay.h>
#include <stdio.h>
// Alphanumeric LCD functions
#include <alcd.h>

// Declare your global variables here
#define RELEASED 1
#define PUSHED 0
#define KEY0 0
#define KEY1 1
#define KEY2 2
#define BUTTON0 PINC.0
#define BUTTON1 PINC.1
#define BUTTON2 PINC.2
#define NO_SET      0
#define SET_HOUR    1
#define SET_MIN     2
#define SET_SECOND  3
void main(void)
{
int pushing_status[3];
// Declare your local variables here
unsigned char hour, min, sec;
char str[24];
int setting_state=0,wait_to_operate=0;
// Crystal Oscillator division factor: 1
#pragma optsize-
CLKPR=0x80;
CLKPR=0x00;
#ifdef _OPTIMIZE_SIZE_
#pragma optsize+
#endif

// Input/Output Ports initialization
// Port B initialization
// Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
// State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T 
PORTB=0x00;
DDRB=0x00;

// Port C initialization
// Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
// State6=T State5=T State4=T State3=T State2=T State1=T State0=T 
PORTC=0x00;
DDRC=0x00;

// Port D initialization
// Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
// State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T 
PORTD=0x00;
DDRD=0x00;

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: Timer 0 Stopped
// Mode: Normal top=0xFF
// OC0A output: Disconnected
// OC0B output: Disconnected
TCCR0A=0x00;
TCCR0B=0x00;
TCNT0=0x00;
OCR0A=0x00;
OCR0B=0x00;

// Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: Timer1 Stopped
// Mode: Normal top=0xFFFF
// OC1A output: Discon.
// OC1B output: Discon.
// Noise Canceler: Off
// Input Capture on Falling Edge
// Timer1 Overflow Interrupt: Off
// Input Capture Interrupt: Off
// Compare A Match Interrupt: Off
// Compare B Match Interrupt: Off
TCCR1A=0x00;
TCCR1B=0x00;
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x00;
OCR1AL=0x00;
OCR1BH=0x00;
OCR1BL=0x00;

// Timer/Counter 2 initialization
// Clock source: System Clock
// Clock value: Timer2 Stopped
// Mode: Normal top=0xFF
// OC2A output: Disconnected
// OC2B output: Disconnected
ASSR=0x00;
TCCR2A=0x00;
TCCR2B=0x00;
TCNT2=0x00;
OCR2A=0x00;
OCR2B=0x00;

// External Interrupt(s) initialization
// INT0: Off
// INT1: Off
// Interrupt on any change on pins PCINT0-7: Off
// Interrupt on any change on pins PCINT8-14: Off
// Interrupt on any change on pins PCINT16-23: Off
EICRA=0x00;
EIMSK=0x00;
PCICR=0x00;

// Timer/Counter 0 Interrupt(s) initialization
TIMSK0=0x00;

// Timer/Counter 1 Interrupt(s) initialization
TIMSK1=0x00;

// Timer/Counter 2 Interrupt(s) initialization
TIMSK2=0x00;

// USART initialization
// USART disabled
UCSR0B=0x00;

// Analog Comparator initialization
// Analog Comparator: Off
// Analog Comparator Input Capture by Timer/Counter 1: Off
ACSR=0x80;
ADCSRB=0x00;
DIDR1=0x00;

// ADC initialization
// ADC disabled
ADCSRA=0x00;

// SPI initialization
// SPI disabled
SPCR=0x00;

// TWI initialization
// TWI disabled
TWCR=0x00;

// I2C Bus initialization
// I2C Port: PORTC
// I2C SDA bit: 4
// I2C SCL bit: 5
// Bit Rate: 100 kHz
// Note: I2C settings are specified in the
// Project|Configure|C Compiler|Libraries|I2C menu.
i2c_init();

// DS1307 Real Time Clock initialization
// Square wave output on pin SQW/OUT: Off
// SQW/OUT pin state: 0
rtc_init(0,0,0);

// Alphanumeric LCD initialization
// Connections are specified in the
// Project|Configure|C Compiler|Libraries|Alphanumeric LCD menu:
// RS - PORTD Bit 0
// RD - PORTD Bit 1
// EN - PORTD Bit 2
// D4 - PORTD Bit 4
// D5 - PORTD Bit 5
// D6 - PORTD Bit 6
// D7 - PORTD Bit 7
// Characters/line: 16
lcd_init(16);

while (1)
    {  
      
      // Place your code here
       wait_to_operate++;
       if (wait_to_operate==10)wait_to_operate=0;
       if (wait_to_operate==5)
       { 
          rtc_get_time(&hour,&min,&sec); 
          sprintf(str,"%02d:%02d:%02d",hour,min,sec); 
          lcd_clear();
          lcd_puts((char *)str);
       }
       if (BUTTON0==RELEASED)pushing_status[KEY0]=RELEASED;
       if (BUTTON1==RELEASED)pushing_status[KEY1]=RELEASED;
       if (BUTTON2==RELEASED)pushing_status[KEY2]=RELEASED;
      
       switch(setting_state)
       {  
           case NO_SET: 
              if (wait_to_operate==0)
              {
                 rtc_get_time(&hour,&min,&sec);
                 sprintf(str,"%02d:%02d:%02d",hour,min,sec);
                 lcd_clear(); 
                 lcd_puts((char *)str);
              }
              delay_ms(50);
              break;
       
           case SET_HOUR:                
              if (wait_to_operate==0)
              {
                  rtc_get_time(&hour,&min,&sec);
                  sprintf(str,"  :%02d:%02d",min,sec);
                  lcd_clear(); 
                  lcd_puts((char *)str);
              }
              delay_ms(50);
              break;
       
           case SET_MIN:                
              if (wait_to_operate==0)
              {
                   rtc_get_time(&hour,&min,&sec);
                   sprintf(str,"%02d:  :%02d",hour,sec);
                   lcd_clear(); 
                   lcd_puts((char *)str);
              }
              delay_ms(50);
              break;
       
           case SET_SECOND:                
              if (wait_to_operate==0)
              {
                   rtc_get_time(&hour,&min,&sec);
                   sprintf(str,"%02d:%02d:  ",hour,min);  
                   lcd_clear();
                   lcd_puts((char *)str);
              }
              delay_ms(50);
              break;
       
           default:
              break;
       }
    
       if ((BUTTON0==PUSHED)&&(pushing_status[KEY0]==RELEASED))
       {
            pushing_status[KEY0]=PUSHED;
            setting_state++;
            if (setting_state==4)setting_state=0;
       }
       if ((BUTTON1==PUSHED)&&(pushing_status[KEY1]==RELEASED))
       {
            pushing_status[KEY1]=PUSHED;
            if (setting_state!=NO_SET)
            {
                 switch(setting_state)
                 {  
                 case SET_HOUR:
                      rtc_get_time(&hour,&min,&sec);
                      hour++;
                      if (hour>=24)hour=0;
                      rtc_set_time(hour,min,sec);
                      break;
                 case SET_MIN:
                      rtc_get_time(&hour,&min,&sec);
                      min++;
                      if (min>=60)min=0;
                      rtc_set_time(hour,min,sec);
                      break;
                 case SET_SECOND:
                      rtc_get_time(&hour,&min,&sec);
                      sec=0;
                      rtc_set_time(hour,min,sec);
                      break;
                 default:
                      break;
                 }
            }
       }
       if ((BUTTON2==PUSHED)&&(pushing_status[KEY2]==RELEASED)) 
       {
            pushing_status[KEY2]=PUSHED;
            if (setting_state!=NO_SET)
            {
                 switch(setting_state)
                 {  
                 case SET_HOUR:
                      rtc_get_time(&hour,&min,&sec);
                      hour--;
                      if (hour>=24)hour=23;
                      rtc_set_time(hour,min,sec);
                      break;
                 case SET_MIN:
                      rtc_get_time(&hour,&min,&sec);
                      min--;
                      if (min>=60)min=59;
                      rtc_set_time(hour,min,sec);
                      break;
                 case SET_SECOND:
                      rtc_get_time(&hour,&min,&sec);
                      sec=0;
                      rtc_set_time(hour,min,sec);
                      break;
                 default:
                      break;
                 }
            }
       }
    }   
}

