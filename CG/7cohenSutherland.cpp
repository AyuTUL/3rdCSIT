/*Lab 7:WAP to implement line clipping using Cohen Sutherland algorithm
a) Enter the clip window co-ordinate: 200,200,400,400
	Enter the end point : 150,150,350,350
b) Enter the clip window co-ordinate: 100,100,400,400
	Enter the end point: 50,50,250,350*/
#include<iostream>
#include<graphics.h>
using namespace std;

//Define outcode values to represnet position relative to clipping window
typedef unsigned int outcode;
enum
{
	TOP=0x1,
	BOTTOM=0x2,
	RIGHT=0x4,
	LEFT=0x8
};

//function to compute the outcode for given point (x,y)
outcode CompOutCode(double x,double y,double xmin,double ymin,double xmax,double ymax)
{
	outcode code=0;
	if(y>ymax) code|=TOP;
	if(y<ymin) code|=BOTTOM;
	if(x>xmax) code|=RIGHT;
	if(x<xmin) code|=LEFT;
	return code;
}

//function to implement Cohen-Sutherland line clipping algorithm
void CSLCAD(double x0,double y0,double x1,double y1,double xmin,double ymin,double xmax,double ymax)
{
	outcode outcode0,outcode1,outcodeout;
	bool accept=false,done=false;
	
	//calculate outcode for both endpoints of line
	outcode0=CompOutCode(x0,y0,xmin,ymin,xmax,ymax);
	outcode1=CompOutCode(x1,y1,xmin,ymin,xmax,ymax);
	cout<<"Outcode0="<<outcode0<<endl;
	cout<<"Outcode1="<<outcode1<<endl;
	
	//start clipping loop
	while(!done)
	{
		//case 1: both endpoints are inside clipping window
		if(outcode0==0 && outcode1==0)
		{
			accept=true;
			done=true;
		}
		//case 2: both endpoints are outside clipping window in the same region (reject line)
		else if(outcode0 & outcode1)
			done=true;
		//case 3: one of the endpoints is  outside clipping window
		else
		{
			double x,y;
			int ocd=(outcode0!=0)?outcode0:outcode1;
			//calculate new intersection point with clipping window
			if(ocd & TOP)
			{
				x=x0+(x1-x0)*(ymax-y0)/(y1-y0);
				y=ymax;
			}
			else if(ocd & BOTTOM)
			{
				x=x0+(x1-x0)*(ymin-y0)/(y1-y0);
				y=ymin;
			} 
			else if(ocd & LEFT)
			{
				y=y0+(y1-y0)*(xmin-x0)/(x1-x0);
				x=xmin;
			}
			else
			{
				y=y0+(y1-y0)*(xmax-x0)/(x1-x0);
				x=xmax;
			}
			//update clipped 
			if(ocd==outcode0)
			{
				x0=x;
				y0=y;
				outcode0=CompOutCode(x0,y0,xmin,ymin,xmax,ymax);
			}
			else
			{
				x1=x;
				y1=y;
				outcode1=CompOutCode(x1,y1,xmin,ymin,xmax,ymax);
			}
		}	
	}
	//if line is accepted (completely inside window)
	if(accept)
		line(x0,y0,x1,y1);
}
int main()
{
	double x0,y0,x1,y1,xmin,xmax,ymin,ymax;
	initwindow(500,600);
	cout<<"Enter the top co-ordinates of window : ";
	cin>>ymax;
	cout<<"Enter the bottom co-ordinates of window : ";
	cin>>ymin;
	cout<<"Enter the right co-ordinates of window : ";
	cin>>xmax;
	cout<<"Enter the left co-ordinates of window : ";
	cin>>xmin;
	rectangle(xmin,ymin,xmax,ymax);
	cout<<"Enter terminal points of line : ";
	cin>>x0>>y0>>x1>>y1;
	line(x0,y0,x1,y1);
	delay(5000);
	cleardevice();
	CSLCAD(x0,y0,x1,y1,xmin,ymin,xmax,ymax);
	rectangle(xmin,ymin,xmax,ymax);
	delay(50000);
	closegraph();
	return 0;
}