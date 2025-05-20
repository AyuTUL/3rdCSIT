/*LAB 3: wap to implement mid-point circle drawing algorithm to draw circle.
a. RADIUS=100 AND CENTER (200, 125)
b. RADIUS= 50 AND CENTER(100, 150)

Algorithm:
Step 1: Conisder a center co-ordinates(X, Y) as
		X1=0, Y1=r

Step 2: Calcu;late the starting decision parametered 
		d1 = r-1;

Step 3: Let us assume, starting co-ordinates as
		=(Xk, Yk)
		So the next co-ordinate = (XK+1, Y(k+1)
		Findingf the next point on first octant based on the values of decision parameter(dk)
		
Step 4: Case 1:
		if dk<0
		then Xk+1= X(k+1)
		Y(k+1)= Yk
		
		dk+1= dk+2X(k+1)
		
		Case 2:
		If dk>=0
		then X(k+1) = Xk+1
			Y(k-1)=Yk-1
			
			dk+1=dk-2(Y(k+1)+2Xk+1)+1

Step 5: If the center co-ordinate point (X1, Y1) is not at the origin (0,0)
		then finding the point as follows
		for X-coordinate = Xc+X1}Xc and Yc contain current values 
		for Y-coordinate = Yc+Y1} of X, Y

Step 6: Repeat 4 and 5 til;l we get X>=Y*/

#include<iostream>
#include<conio.h>
#include<graphics.h>
using namespace std;

void plotCirclePoints(int xc, int yc , int x, int y)
{
	putpixel(xc+x, yc+y, WHITE);
	putpixel(xc-x, yc+y, WHITE);
	putpixel(xc+x, yc-y, WHITE);
	putpixel(xc-x, yc-y, WHITE);
	putpixel(xc+y, yc+x, WHITE);
	putpixel(xc-y, yc+x, WHITE);
	putpixel(xc+y, yc-x, WHITE);
	putpixel(xc-y, yc-x, WHITE);
}

void drawCircle(int xc, int yc, int r)
{
	int x= 0, y=r;
	int p=1-r;
	
	plotCirclePoints(xc, yc, x, y);
	while(x<y)
	{
		x++;
		if(p<0)
		{
			p+=2*x+1;
		}
		else
		{
			y--;
			p+=2*(x-y)+1;
		}
		plotCirclePoints(xc, yc, x, y);
	}
}

int main()
{
	int gd=DETECT,gm;
	initgraph(&gd,&gm,"");
	int xc,yc,r;
	cout<<"Enter center of circle(xc,yc):";
	cin>>xc>>yc;
	cout<<"Enter radius of circle:";
	cin>>r;
	drawCircle(xc,yc,r);
	getch();
	closegraph();
	return 0;
}