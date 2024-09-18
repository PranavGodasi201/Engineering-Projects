#include<reg51.h>
#include "lcd.h"
//Function declarations
void cct_init(void);

void InitTimer0(void);
void UpdateTimeCounters(void);
void DisplayTimeToLCD(unsigned int,unsigned int,unsigned int);
void Timer0_pause();



sbit res = P1^3;
sbit sw=P3^3;
unsigned int usecCounter = 0;
unsigned int msCounter   = 0;
unsigned int secCounter  = 0;
unsigned int minCounter  = 0;
unsigned int hrCounter   = 0;
void main(void)
{
   cct_init();             
   lcdinit();              
   InitTimer0();           
			
	while(1)
	{
		if( msCounter == 0 )                                      
		{
			DisplayTimeToLCD(hrCounter, minCounter, secCounter);   // Displays time in HH:MM:SS format
		}
		while(sw==0)
		{
			DisplayTimeToLCD(hrCounter, minCounter, secCounter);
			//msCounter=0;
			TR0=0;
		}
		TR0=1;
		 
		if(res==1)
		{                           // msCounter becomes zero after exact one sec
		msCounter=secCounter=minCounter=hrCounter=0;	
			DisplayTimeToLCD(hrCounter, minCounter, secCounter);
		// Displays time in HH:MM:SS format
		
		}
		
		
		UpdateTimeCounters();  
			// Update sec, min, hours counters
  	}
}


void cct_init(void)
{
	P0 = 0x00;   //not used 
	P1 = 0x00;   //not used 
	P2 = 0x00;   //used as data port
	P3 = 0x00;
	sw=1;
//used for generating E and RS
}


void InitTimer0(void)
{
	TMOD &= 0xF0;    // Clear 4bit field for timer0
	TMOD |= 0x02;    // Set timer0 in mode 2
	
	TH0 = 0x05;      // 250 usec reloading time
	TL0 = 0x05;      // First time value
	
	ET0 = 1;         // Enable Timer0 interrupts
	EA  = 1;         // Global interrupt enable
	
	TR0 = 1;         // Start Timer 0
}


void Timer0_ISR (void) interrupt 1     // It is called after every 250usec
{
	usecCounter = usecCounter + 250;   // Count 250 usec
	
	if(usecCounter==1000)              // 1000 usec means 1msec 
	{
		msCounter++;
		usecCounter = 0;
	}

	TF0 = 0;     // Clear the interrupt flag
}



void UpdateTimeCounters(void)
{
	if (msCounter==1000)
	{
		secCounter++;
		msCounter=0;
	}

	if(secCounter==60)
	{
		minCounter++;
		secCounter=0;
	}

	if(minCounter==60)
	{
		hrCounter++;
		minCounter=0;
	}

	if(hrCounter==24)
	{
		hrCounter = 0;
	}
}



void DisplayTimeToLCD( unsigned int h, unsigned int m, unsigned int s )   // Displays time in HH:MM:SS format
{
	ClearLCDScreen();      // Move cursor to zero location and clear screen

	// Display Hour
	WriteDataToLCD( (h/10)+0x30 );
	WriteDataToLCD( (h%10)+0x30 );

	//Display ':'
	WriteDataToLCD(':');

	//Display Minutes
	WriteDataToLCD( (m/10)+0x30 );
	WriteDataToLCD( (m%10)+0x30 );

	//Display ':'
	WriteDataToLCD(':');

	//Display Seconds
	WriteDataToLCD( (s/10)+0x30 );
	WriteDataToLCD( (s%10)+0x30 );
}

