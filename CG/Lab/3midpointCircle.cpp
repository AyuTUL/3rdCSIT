#include<iostream>
#include<conio.h>
#include<graphics.h>
#include<stdio.h>
using namespace std;
void plotCirclePoints(int xc,int yc,int x,int y)
{
	putpixel(xc+x,yc+y,WHITE);
	putpixel(xc-x,yc+y,WHITE);
	putpixel(xc+x,yc-y,WHITE);
	putpixel(xc-x,yc-y,WHITE);
	putpixel(xc+y,yc+x,WHITE);
	putpixel(xc-y,yc+x,WHITE);
	putpixel(xc+y,yc-x,WHITE);
	putpixel(xc-y,yc-x,WHITE);
}
void midpointCircle(int xc,int yc,int r)
{
	int x=0,y=r,p=1-r;
	putpixel(xc,yc,WHITE);
	do 
	{
	    plotCirclePoints(xc,yc,x,y);
	    x++;
	    if(p<0)
	        p+=2*x+1;
	    else
	    {
	        y--;
	        p+=2*(x-y)+1;
	    }
	}while(x<y);
}
int main()
{
	int gd=DETECT,gm,xc,yc,r;
	char center[20];
	initgraph(&gd,&gm,"");
	if(graphresult()!=grOk)
    {
        cout<<"Graphics initialization failed"<<endl;
        return 1;
    }
	cout<<"Enter center of circle : ";
	cin>>xc>>yc;
	cout<<"Enter radius of circle : ";
	cin>>r;
	midpointCircle(xc,yc,r);
	outtextxy(10,10,"Ayush Tuladhar");
	outtextxy(10,20,"Mid-point Circle Drawing Algorithm");
	sprintf(center,"(%d,%d)",xc,yc);
	outtextxy(xc-30,yc+5,center);
	getch();
	closegraph();
	return 0;
}