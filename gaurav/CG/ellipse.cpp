#include<iostream>
#include<conio.h>
#include<graphics.h>
#include<math.h>
using namespace std;
void disp();
float x,y;
int xc,yc;
int main()
{
	int gd = DETECT,gm;
	int rx,ry;
	float p1,p2;
	
	initgraph(&gd,&gm,"");
	cout<<"Enter centre point:";
	cin>>xc>>yc;
	cout<<"Enter the value for rx and ry:";
	cin>>rx>>ry;
	x=0;
	y=ry;
	disp();
	p1=(rx*ry)-(rx*rx*ry)+(rx*rx)/4;
	while((2.0*ry*ry*x)<=(2.0*rx*rx*y))
	{
		x++;
		if(p1<=0)
		p1+=(2.0*ry*ry*x)+(ry*ry);
		else
		{
			y--;
			p1+=(2.0*ry*ry*x)-(2.0*rx*rx*y)+(ry*ry);
		}
		disp();
		x=-x;
		disp();
		x=-x;
	}
	x=rx;
	y=0;
	disp();
	p2=(rx*ry)+2.0*(ry*ry*rx)+(ry*ry)/4;
	while((2.0*ry*ry*x)>(2.0*rx*rx*y))
	{
		y++;
		if(p2>0)
		{
			p2+=(rx*rx)-(2.0*rx*rx*y);
		}
		else
		{
			x--;
			p2+=(2.0*ry*ry*x)-(2.0*rx*rx*y)+(rx*rx);
		}
		disp();
		y=-y;
		disp();
		y=-y;
	}
	getch();
	closegraph();
	
}

void disp()
{

	putpixel(xc+x,yc+y,10);
	putpixel(xc-x,yc+y,10);
	putpixel(xc+x,yc-y,10);
	putpixel(xc-x,yc-y,10);
}