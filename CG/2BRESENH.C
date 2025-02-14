#include<iostream>
#include<conio.h>
#include<graphics.h>
using namespace std;
int main()
{
	int x,y,x1,y1,x2,y2,p,dx,dy,gd=DETECT,gm;
	initgraph(&gd,&gm,NULL);
	cout<<"Enter 1st co-ordinate : ";
	cin>>x1>>y1;
	cout<<"Enter 2nd co-ordinate : ";
	cin>>x2>>y2;
	x=x1;
	y=y1;
	dx=x2-x1;
	dy=y2-y1;
	putpixel(x,y,2);
	p=(2*dy-dx);
	while(x<=x2)
	{
		if(p<0)
		{
			x++;
			p+=2*dy;
		}
		else
		{
			x++;
			y++;
			p+=(2*dy)-(2*dx);
		}
		putpixel(x,y,7);
	}
	outtextxy(1,50,"Bresenham");
	outtextxy(x1+5,y1-5,"(x1,y1)");
	outtextxy(x2+5,y2+5,"(x2,y2)");
	getch();
	closegraph();
	return 0;
}
