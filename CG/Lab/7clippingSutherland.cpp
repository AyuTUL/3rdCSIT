/*
WAP to implementthe clipping using cohen sutherland algorithm.
a. Enter the clip window coordinate:200,200,400,400. Enter the endpoint-150,150,350,350
b. Enter te clip window coordinate:100,100,400,400. Enter endpoint: 50 50 250 350 
*/
#include<iostream>
#include<graphics.h>
using namespace std;
struct Point {
	double x,y;
};
typedef unsigned int outcode;
enum { top=0x1,bottom=0x2,rt=0x4,lt=0x8 };
outcode getOutcode(Point p,double xmin,double xmax,double ymin,double ymax) 
{
	outcode code=0;
	if(p.y>ymax) code|=top;
	if(p.y<ymin) code|=bottom;
	if(p.x>xmax) code|=rt;
	if(p.x<xmin) code|=lt;
	return code;
}
void cohenSutherland(Point p0,Point p1,double xmin,double xmax,double ymin,double ymax) 
{
	outcode code0=getOutcode(p0,xmin,xmax,ymin,ymax);
	outcode code1=getOutcode(p1,xmin,xmax,ymin,ymax);
	bool accept=false;
	while(true) 
	{
		if((code0|code1)==0)
		{
			accept=true; 
			break;
		} 
		else if(code0&code1) 
			break;
		else 
		{
			Point p;
			outcode out=code0?code0:code1;
			if(out&top) 
			{
				p.x=p0.x+(p1.x-p0.x)*(ymax-p0.y)/(p1.y-p0.y);
				p.y=ymax;
			} 
			else if(out&bottom) 
			{
				p.x=p0.x+(p1.x-p0.x)*(ymin-p0.y)/(p1.y-p0.y);
				p.y=ymin;
			} 
			else if(out&lt) 
			{
				p.y=p0.y+(p1.y-p0.y)*(xmin-p0.x)/(p1.x-p0.x);
				p.x=xmin;
			} 
			else 
			{
				p.y=p0.y+(p1.y-p0.y)*(xmax-p0.x)/(p1.x-p0.x);
				p.x=xmax;
			}
			if(out==code0) 
			{
				p0=p;
				code0=getOutcode(p0,xmin,xmax,ymin,ymax);
			} else 
			{
				p1=p;
				code1=getOutcode(p1,xmin,xmax,ymin,ymax);
			}
		}
	}
	if(accept) line(p0.x,p0.y,p1.x,p1.y);
}
int main() 
{
	double xmin,xmax,ymin,ymax;
	Point p1,p2;
	initwindow(500,600);
	outtextxy(10,10,"Ayush Tuladhar");
	outtextxy(10,20,"Cohen-Sutherland Line Clipping");
	cout<<"Enter clip window co-ordinates : "<<endl;
	cout<<"(xmin,ymin) : ";
	cin>>xmin>>ymin;
	cout<<"(xmax,ymax) : ";
	cin>>xmax>>ymax;
	rectangle(xmin,ymin,xmax,ymax);
	cout<<"Enter line end-points co-ordinates : "<<endl;
	cout<<"(x1,y1) : ";
	cin>>p1.x>>p1.y;
	cout<<"(x2,y2) : ";
	cin>>p2.x>>p2.y;
	line(p1.x,p1.y,p2.x,p2.y);
	delay(3000);
	cleardevice();
	outtextxy(10,10,"Ayush Tuladhar");
	outtextxy(10,20,"Cohen-Sutherland Line Clipping");
	cohenSutherland(p1,p2,xmin,xmax,ymin,ymax);
	rectangle(xmin,ymin,xmax,ymax);
	delay(5000);
	closegraph();
	return 0;
}