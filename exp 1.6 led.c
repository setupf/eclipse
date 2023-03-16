#include<LPC214x.h>

int Delay()
{
	int c,d;
	for(c =1;c<=10; c++)
		for(d=1;d<=10; d++);
	return 0;
}

int main()
{
	PINSEL0= 0x00000000;
	IO0DIR = 0x000000FF;
	while(1)
	{
		IO0SET = 0x000000FF; //off
		Delay();
		IO0CLR = 0x000000FF; //on
		Delay();
	}
}

