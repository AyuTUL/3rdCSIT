//Lab 3:

/*Algorithm
Step 1: Consider a center coordinate (x1,y1) as
	x1=0
	y1=r
Step 2: Calculate decision parameter d1:
	d1=1-r;
Step 3: Let us assume starting coordinate as:
	(xk,yk)
So, next coordinate = (xk + 1, yk + 1)
Finding hte next point on 1st octant based on the value of decision parameter (dk)
Step 4:
Case 1:
if dx<0
then xk + 1 = xk + 1
yk + 1= yk
dk + 1 = dk + 2xk + 1 + 1 
TBC
*/
#include<graphics.h>
#include<conio.h>
#include<iostream>
using namespace std;

void plotCirclePoints(int xc,int yc,int x, int y)
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

void drawCircle(int xc,int yc,int r)
{
	int x=0,y=r,p=1-r;
	
	plotCirclePoints(xc,yc,x,y);
	while(x<y)
	{
		x++;
		if(p<0)
			p+=2*x+1;
		else
		{
			y--;
			p+=2*(x-y)+1;
		}
		plotCirclePoints(xc,yc,x,y);
	}
}
int main()
{
	int gd=DETECT,gm,xc,yc,r;
	initgraph(&gd,&gm,"");
	cout<<"Enter centre of circle (xc,yc) : ";
	cin>>xc>>yc;
	cout<<"Enter radius of circle : ";
	cin>>r;
	drawCircle(xc,yc,r);
	getch();
	closegraph();
	return 0;
}