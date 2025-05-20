#include<iostream>
#include<conio.h>
#include<graphics.h>
#include<stdio.h>
using namespace std;
void plotEllipsePoints(int xc,int yc,int x,int y)
{
	putpixel(xc+x,yc+y,WHITE);
	putpixel(xc-x,yc+y,WHITE);
	putpixel(xc+x,yc-y,WHITE);
	putpixel(xc-x,yc-y,WHITE);
}
void midpointEllipse(int xc,int yc,int rx,int ry){
	int x=0,y=ry,rx2=rx*rx,ry2=ry*ry,tworx2=2*rx2,twory2=2*ry2,dx=0,dy=tworx2*y;
	putpixel(xc,yc,WHITE);
	int p1=ry2-(rx2*ry)+(rx2/4);
	while(dx<dy)
	{
		plotEllipsePoints(xc,yc,x,y);
		x++;
		dx+=twory2;
		if(p1<0)
			p1+=ry2+dx;
		else
		{
			y--;
			dy-=tworx2;
			p1+=ry2+dx-dy;
		}
	}
	int p2=ry2*x*x+ry2*x+(ry2/4)+rx2*(y-1)*(y-1)-rx2*ry2;
	while(y>=0)
	{
		plotEllipsePoints(xc,yc,x,y);
		y--;
		dy-=tworx2;
		if(p2>0)
			p2+=rx2-dy;
		else
		{
			x++;
			dx+=twory2;
			p2+=rx2-dy+dx;
		}	
	}
}
int main(){
	int gd=DETECT,gm,xc,yc,rx,ry;
	char center[20];
	initgraph(&gd,&gm,NULL);
	if(graphresult()!=grOk)
    {
        cout<<"Graphics initialization failed"<<endl;
        return 1;
    }
    cout<<"Enter center of ellipse : ";
	cin>>xc>>yc;
	cout<<"Enter semi-major axis (rx) : ";
	cin>>rx;
	cout<<"Enter semi-minor axis (ry) : ";
	cin>>ry;
	midpointEllipse(xc,yc,rx,ry);
	outtextxy(10,10,"Ayush Tuladhar");
	outtextxy(10,20,"Mid-point Ellipse Drawing Algorithm");
	sprintf(center,"(%d,%d)",xc,yc);
	outtextxy(xc-30,yc+5,center);
	getch();
	closegraph();
	return 0;
}