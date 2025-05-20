#include<iostream>
#include<graphics.h>
#include<conio.h>
#include<stdlib.h>
#include<math.h>
using namespace std;
void drawLine(int x1, int y1, int x2, int y2)
{
	line(x1, y1, x2, y2);
}

void translation(int x1, int y1, int x2, int y2, int x3, int y3)
{
	int tx, ty;
	int newx1, newy1, newx2, newy2, newx3, newy3;
	
	cout<<"Enter translation values (tx, ty): ";
	cin>>tx>>ty;
	
	newx1 = x1+tx;
	newy1 = y1+ty;
	newx2 = x2+tx;
	newy2 = y2+ty;
	newx3 = x3+tx;
	newy3 = y3+ty;
	
	cout<<"After translation:\n";
	
	drawLine(newx1, newy1, newx2, newy2);
	drawLine(newx2, newy2, newx3, newy3);
	drawLine(newx3, newy3, newx1, newy1);
}

void scaling(int x1, int y1, int x2, int y2, int x3, int y3)
{
	float sx, sy;
	int newx1, newy1, newx2, newy2, newx3, newy3;
	
	cout<<"Enter scaling factors (sx, sy): ";
	cin>>sx>>sy;
	
	newx1 = x1 * sx;
	newy1 = y1 * sy;
	newx2 = x2 * sx;
	newy2 = y2 * sy;
	newx3 = x3 * sx;
	newy3 = y3 * sy;
	
	cout<<"After scaling:\n";
	
	drawLine(newx1, newy1, newx2, newy2);
	drawLine(newx2, newy2, newx3, newy3);
	drawLine(newx3, newy3, newx1, newy1);
}

void rotation(int x1, int y1, int x2, int y2, int x3, int y3)
{
	float angle, radian;
	int newx1, newy1, newx2, newy2, newx3, newy3;
	int cx=0, cy=0;
	
	cout<<"Enter rotation angle in degrees: ";
	cin>>angle;
	
	radian = (angle * 3.14159)/180;
	
	newx1 = (x1 - cx) * cos(radian) - (y1 - cy) * sin(radian) + cx;
	newy1 = (x1 - cx) * sin(radian) + (y1 - cy) * cos(radian) + cy;
	newx2 = (x2 - cx) * cos(radian) - (y2 - cy) * sin(radian) + cx;
	newy2 = (x2 - cx) * sin(radian) + (y2 - cy) * cos(radian) + cy;
	newx3 = (x3 - cx) * cos(radian) - (y3 - cy) * sin(radian) + cx;
	newy3 = (x3 - cx) * sin(radian) + (y3 - cy) * cos(radian) + cy;
	
	cout<<"After rotation:\n";
	
	drawLine(newx1, newy1, newx2, newy2);
	drawLine(newx2, newy2, newx3, newy3);
	drawLine(newx3, newy3, newx1, newy1);
}

int main()
{
	int gm, gd=DETECT;
	int n;
	int x1, x2, x3, y1, y2, y3;
	
	initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");
	
	do
	{
		cout<<"\n---Menu---\n";
		cout<<"1) Translation\n";
		cout<<"2) Scaling\n";
		cout<<"3) Rotation\n";
		cout<<"4) Exit\n";
		
		cout<<"Enter your choice: ";
		cin>>n;
		
		cout<<"\nEnter the coordinates of triangle (x1, y1), (x2, y2), (x3, y3): ";
		cin>>x1>>y1>>x2>>y2>>x3>>y3;
		
		drawLine(x1, y1, x2, y2);
		drawLine(x2, y2, x3, y3);
		drawLine(x3, y3, x1, y1);
		
		switch(n)
		{
			case 1:
				translation(x1,y1,x2,y2,x3,y3);
				break;
			case 2:
				scaling(x1,y1,x2,y2,x3,y3);
				break;
			case 3:
				rotation(x1,y1,x2,y2,x3,y3);
				break;
			case 4:
				closegraph();
				exit(0);
			default:
				closegraph();
				exit(0);
		}
		
		getch();
		closegraph();	
	}
	while(n!=4);
	return 0;
	}