For 10 to 40 PLL
# include<LPC214x.h>
int main(){
PLL0CON = 0x23;
 PLL0CFG = 0x23;
 PLL0FEED = 0xAA;
 PLL0FEED = 0x55;
 while(!(PLL0STAT & 0x00000400));
 PLL0CON = 0x03;
 PLL0FEED = 0xAA;
 PLL0FEED = 0x55;
 VPBDIV = 0x02; }
FOR LED
Code for led
# include<LPC214x.h>
void Delay(){
int c,d;
for(c=1;c<10;c++);
for(d=1;d<=10;d++);
}
int main(){
PINSEL0 = 0x5000000;
IO0DIR = 0x000000FF;
while(1){
IO0SET = 0x000000FF;
Delay();
IO0CLR = 0x000000FF;
Delay();
}
}