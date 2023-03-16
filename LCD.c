#include "lpc214x.h"

#define LCD (0xff<<8)
#define RS (1<<5)
#define RW (1<<6)
#define EN (1<<7)

void delay_fv(unsigned int x,int y);

void lcd_display(unsigned int x);
void cmd (unsigned int x);
void lcd_ini();
//void lcd_str(unsigned char *x);



int main()
{
	int i;
	unsigned char a[] = {"MITWPU"};
	PINSEL0=0X00000000;
	IODIR0=0XFFFFFFFF;
	lcd_ini();
	cmd(0x84);

	for(i=0;a[i]!='\0';i++)
	{
		lcd_display(a[i]);
	}
	return 0;
}

void delay_fv(unsigned int x,int y)
{
	unsigned int i,j;
	for(i=0;i<x;i++)
	for(j=0;j<y;j++);
}

void lcd_display(unsigned int x)	//at bit 0 to 7;x= 0x41 = 01000001
{
	IOCLR0 = 0x0000FF00;		//bits 8 to 18 as 00000000
	x =(x<<8);			 //at bit 8 to 15;x= 0x41 = 01000001
	IOSET0 = x;		// bits 8 to 18 as 01000001
	IOSET0 =RS;		//RS=1 for data
	IOCLR0 =RW;		//RW =0
	IOSET0 =EN;		//high to low pulse on enable line
	delay_fv(100,10);
	IOCLR0 =EN;
}

void cmd (unsigned int x)
{
	IOCLR0 = 0x0000FF00;
	x =(x<<8);
	IOSET0 = x;
	IOCLR0 =RS;
	IOCLR0 =RW;
	IOSET0 =EN;
	delay_fv(100,10);
	IOCLR0 =EN;
}

void lcd_ini()
{
	cmd(0X38);
	cmd(0X0e);
	cmd(0X01);
	cmd(0X06);
}

/*void lcd_str(unsigned char x[])
{
	int i;
	for(i=0;x[i]!='\0';i++)
	{
		lcd_display(x[i]);
	}
}*/