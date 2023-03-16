#include "lpc214x.h"
#include "image.h"
#define LCD_D0  1<<24
#define LCD_D1  1<<25
#define LCD_D2  1<<26
#define LCD_D3  1<<27
#define LCD_D4  1<<28
#define LCD_D5  1<<29
#define LCD_D6  1<<30
#define LCD_D7  1<<31
#define RS	(1<<16)
#define RW	(1<<17)
#define EN 	(1<<18)
#define CS1 	(1<<19)
#define CS2 	(1<<20)
#define TotalPage   8
#define FOSC	12000000
void delay(int k) ;



void GLCD_Command(int Command)		/* GLCD command function */
{
	IOCLR1= (LCD_D0|LCD_D1|LCD_D2|LCD_D3|LCD_D4|LCD_D5|LCD_D6|LCD_D7); /* These bits are set to '1', rest are zeros*/
	Command = Command<<24;
	IOSET1 = Command;		/* Copy command on data pin */
	IOCLR1 = RS; /* Make RS LOW to select command register */
	IOCLR1 = RW; 		/* Make RW LOW to select write operation */
	IOSET1 = EN;/* Make HIGH to LOW transition on Enable pin */
	delay(5);
	IOCLR1 = EN;
}

void GLCD_Data(int Data)		/* GLCD data function */
{
	IOCLR1= (LCD_D0|LCD_D1|LCD_D2|LCD_D3|LCD_D4|LCD_D5|LCD_D6|LCD_D7);
	Data = Data << 24;
	IOSET1 = Data;		/* Copy data on data pin */
	IOSET1 = RS;	/* Make RS HIGH to select data register */
	IOCLR1 = RW;	/* Make RW LOW to select write operation */
	IOSET1 = EN;/* Make HIGH to LOW transition on Enable pin */
	delay(5);
	IOCLR1 = EN;
}

void GLCD_Init()			/* GLCD initialize function */
{

	PINSEL1=0x00000000;
	IODIR1= (LCD_D0|LCD_D1|LCD_D2|LCD_D3|LCD_D4|LCD_D5|LCD_D6|LCD_D7|RS|RW|EN|CS1|CS2); /* Configure all pins as output*/ 
	
	IOSET1 = (CS1 | CS2);		/* Select both left & right half of display */
	delay(20);
	GLCD_Command(0x3E);				/* Display OFF */
	GLCD_Command(0x40);				/* Set Y address (column=0) */
	GLCD_Command(0xB8);				/* Set x address (page=0) */
	GLCD_Command(0xC0);				/* Set z address (start line=0) */
	GLCD_Command(0x3F);				/* Display ON */
}

void GLCD_ClearAll()				/* GLCD all display clear function */
{
	int column,page;

	for(page=0;page<8;page++)		/* Print 16 pages i.e. 8 page of each half of display */
	{
	 IOSET1 = CS1;				/* If yes then change segment controller */
	 IOCLR1 = CS2;
	 GLCD_Command(0x40);				/* Set Y address (column=0) */
         GLCD_Command((0xB8+page));			/* Increment page address */
		for(column=0;column<128;column++)
		{
			if (column == 64)
			{
			IOCLR1 = CS1;			/* If yes then change segment controller */
		    	IOSET1 = CS2;
			GLCD_Command(0x40);		/* Set Y address (column=0) */
     			GLCD_Command((0xB8+page));	/* Increment page address */
			}
			GLCD_Data(0);		/* Print 64 column of each page */
		}
	}
}

void GLCD_String(const char image)	/ GLCD string write function */
{
	int column,page;

	for(page=0;page<8;page++)	/* Print 16 pages i.e. 8 page of each half of display */
	{
	 IOSET1 = CS1;			/* If yes then change segment controller */
	 IOCLR1 = CS2;
	 GLCD_Command(0x40);		/* Set Y address (column=0) */
     	 GLCD_Command((0xB8+page));	/* Increment page address */
		for(column=0;column<128;column++)
		{
			if (column == 64)
			{
			IOCLR1 = CS1;			/* If yes then change segment controller */
		    	IOSET1 = CS2;
			GLCD_Command(0x40);		/* Set Y address (column=0) */
     			GLCD_Command((0xB8+page));	/* Increment page address */
			}
			  GLCD_Data(image++);		/ Print 64 column of each page */
		}
	}
}
// LCD Delay Function
void delay(int k)
{
  int a,b;
  for(a=0;a<=k;a++)
		for(b=0;b<100;b++);
}
int main(void)
{
	VPBDIV = 0X01;
	delay(1000);
	GLCD_Init();					/* Initialize GLCD */
	GLCD_ClearAll();				/* Clear all GLCD display */
	GLCD_String(img);		  	/* Display image on GLCD display */
 	while(1);
}