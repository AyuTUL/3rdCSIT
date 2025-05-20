#include<iostream>
#include<conio.h>
#include<graphics.h>
#include<math.h>
#include<stdio.h>
using namespace std;
void bresenham(int x1,int y1,int x2,int y2)
{
	int p,x,y,xend,dx=abs(x2-x1),dy=abs(y2-y1),stepY;
	p=2*dy-dx;
	stepY=(y2>y1)?1:-1;
	if(x1>x2)
	{
		x=x2;
		y=y2;
		xend=x1;
	}
	else
	{
		x=x1;
		y=y1;
		xend=x2;
	}
	putpixel(x,y,WHITE);	
	while(x<xend)
	{
		x++;
		if(p<0)
			p+=2*dy;
		else
		{
			y+=stepY;
			p+=2*(dy-dx);
		}
		putpixel(x,y,WHITE);
	}
}
int main()
{
	int gd=DETECT,gm,x1,y1,x2,y2;
	char start[20],end[20];
	initgraph(&gd,&gm,"");
	if(graphresult()!=grOk)
    {
        cout<<"Graphics initialization failed"<<endl;
        return 1;
    }
	cout<<"Enter starting co-ordinate: ";
	cin>>x1>>y1;
	cout<<"Enter ending co-ordinate : ";
	cin>>x2>>y2;
	bresenham(x1,y1,x2,y2);
	outtextxy(10,10,"Ayush Tuladhar");
	outtextxy(10,20,"Bresenham Line Drawing Algorithm");
	sprintf(start,"(%d,%d)",x1,y1);
	sprintf(end,"(%d,%d)",x2,y2);
	outtextxy(x1+5,y1-5,start);
	outtextxy(x2+5,y2+5,end);
	getch();
	closegraph();
	return 0;
}