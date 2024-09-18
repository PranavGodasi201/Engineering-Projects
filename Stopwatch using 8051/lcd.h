#include<reg51.h>
void delay(int);
void lcdinit(void);
void WriteCommandToLCD(int);
void WriteDataToLCD(char);
void ClearLCDScreen(void);
sbit RS = P1^0;
sbit E  = P1^1;
void delay(int a)
{
   int i;
   for(i=0;i<a;i++);   //null statement
}

void WriteDataToLCD(char t)
{
   RS = 1;             // This is data

   P2 &= 0x0F;		   // Make P2.4 to P2.7 zero
   P2 |= (t&0xF0);     // Write Upper nibble of data

   E  = 1;             // => E = 1
   delay(5);
   E  = 0;             // => E = 0
   delay(5);

   P2 &= 0x0F;		   // Make P2.4 to P2.7 zero
   P2 |= ((t<<4)&0xF0);// Write Lower nibble of data

   E  = 1;             // => E = 1
   delay(5);
   E  = 0;             // => E = 0
   delay(5);
}


void WriteCommandToLCD(int z)
{
   RS = 0;             // This is command

   P2 &= 0x0F;		   // Make P2.4 to P2.7 zero
   P2 |= (z&0xF0);     // Write Upper nibble of data

   E  = 1;             // => E = 1
   delay(150);
   E  = 0;             // => E = 0
   delay(150);

   P2 &= 0x0F;		   // Make P2.4 to P2.7 zero
   P2 |= ((z<<4)&0xF0);// Write Lower nibble of data

   E  = 1;             // => E = 1
   delay(150);
   E  = 0;             // => E = 0
   delay(150);
}

void lcdinit(void)
{
  ///////////// Reset process from datasheet /////////
     delay(15000);

	 P2 &= 0x0F;		   // Make P2.4 to P2.7 zero
	 P2 |= (0x30&0xF0);    // Write 0x3
	
	 E  = 1;               // => E = 1
	 delay(150);
	 E  = 0;               // => E = 0
	 delay(150);

     delay(4500);

	 P2 &= 0x0F;		   // Make P2.4 to P2.7 zero
	 P2 |= (0x30&0xF0);    // Write 0x3
	
	 E  = 1;               // => E = 1
	 delay(150);
	 E  = 0;               // => E = 0
	 delay(150);

     delay(300);

	 P2 &= 0x0F;		   // Make P2.4 to P2.7 zero
	 P2 |= (0x30&0xF0);    // Write 0x3
	
	 E  = 1;               // => E = 1
	 delay(150);
	 E  = 0;               // => E = 0
	 delay(150);

     delay(650);

	 P2 &= 0x0F;		   // Make P2.4 to P2.7 zero
	 P2 |= (0x20&0xF0);    // Write 0x2
	
	 E  = 1;               // => E = 1
	 delay(150);
	 E  = 0;               // => E = 0
	 delay(150);

	 delay(650);

  /////////////////////////////////////////////////////
   WriteCommandToLCD(0x28);    //function set
   WriteCommandToLCD(0x0c);    //display on,cursor off,blink off
   WriteCommandToLCD(0x01);    //clear display
   WriteCommandToLCD(0x06);    //entry mode, set increment
}

void ClearLCDScreen(void)
{
	WriteCommandToLCD(0x01);   // Clear screen command
	delay(1000);
}