#include<iostream>
#include<conio.h>
#include<graphics.h>
#include<math.h>
#include<stdio.h>
using namespace std;
void DDA(int x1,int y1,int x2,int y2)
{
	int steps;	
	float xincr,yincr,x,y,dx=x2-x1,dy=y2-y1;
	if(abs(dx)>abs(dy))
		steps=abs(dx);
	else
		steps=abs(dy);
	xincr=dx/(float)steps;
	yincr=dy/(float)steps;
	x=x1;
	y=y1;
	for(int k=1;k<=steps;k++)
	{
		x+=xincr;
		y+=yincr;
		putpixel(round(x),round(y),WHITE);
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
	DDA(x1,y1,x2,y2);
	outtextxy(10,10,"Ayush Tuladhar");
	outtextxy(10,20,"DDA Line Drawing Algorithm");
	sprintf(start,"(%d,%d)",x1,y1);
	sprintf(end,"(%d,%d)",x2,y2);
	outtextxy(x1+5,y1-5,start);
	outtextxy(x2+5,y2+5,end);
	getch();
	closegraph();
	return 0;
}