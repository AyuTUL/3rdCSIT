/* Lab 7: To write a program to implement line clipping using cohen sutherland line clipping algorithm
 a) Enter the clip window coordinate 200 200 400 400 
 	Enter the line end point : 150 150 350 500
 b) Enter the clip window coordinate : 100 100 400 400 
 	Enter point : 50 50 250 350 
*/

#include<iostream>
#include<graphics.h>
using namespace std;
typedef unsigned int outcode;
enum {
	TOP = 0x1, BOTTOM = 0x2, RIGHT = 0x4, LEFT = 0x8
};
using namespace std;
outcode CompOutCode(double x, double y, double xmin, double xmax, double ymin, double ymax){
	outcode code = 0;
	if(y > ymax) code |= TOP;
	if(y < ymin) code |= BOTTOM;
	if(x > xmax) code |= RIGHT;
	if(x < xmin) code |= LEFT;
	return code;
}  

void CSLCAD(double x0, double y0, double x1, double y1, double xmin, double xmax, double ymin, double ymax )
{
	outcode outcode0, outcode1, outcodeout;
	bool accept = false, done = false;
	
	outcode0 = CompOutCode(x0,y0,xmin,xmax,ymin,ymax);
	outcode1 = CompOutCode(x1,y1,xmin,xmax,ymin,ymax);
	
	cout << "outcode0 = "<<outcode0<<endl;
	cout << "outcode1 = "<<outcode1<<endl;
	
	while(!done){
		if(outcode0 == 0 && outcode1 == 0){
			accept = true;
			done = true;
		}
		else if(outcode0 & outcode1){
			done = true;
		}
		
		else{
			double x,y;
			int ocd = (outcode0 != 0) ? outcode0 : outcode1;
			
			if (ocd & TOP){
				x = x0 + (x1 - x0)*(ymax - y0)/(y1 - y0);
				y = ymax;
			}
			else if (ocd & BOTTOM){
				x = x0 + (x1 - x0)*(ymin - y0)/(y1 - y0);
				y = ymin;
			}
			else if (ocd & LEFT)
			{
				y = y0 + (y1 - y0)*(xmin - x0)/(x1 - x0);
				x = xmin;
			} 
			else 
			{
				y = y0 + (y1 - y0)*(xmax - x0)/(x1 - x0);
				x = xmax;
			}
			
			if (ocd == outcode0){
				x0 = x;
				y0 = y;
				outcode0 = CompOutCode(x0, y0, xmin, xmax, ymin, ymax);
			}
			else {
				x1 = x;
				y1 = y;
				outcode1 = CompOutCode(x1, y1, xmin, xmax, ymin, ymax);
			}
		}	
	}		
	
	if (accept)
	{
		line (x0,y0,x1,y1);
	}
}

int main()
{
	double xmin,xmax,ymin,ymax,x0,y0,x1,y1;
	initwindow(500,600);
	
	cout<<"Enter the bottom coordinates of window: ";
	cin>>ymin;
	cout<<"Enter the left coordinates of window: ";
	cin>>xmin;
	cout<<"Enter the right coordinates of window: ";
	cin>>xmax;
	cout<<"Enter the top coordinates of window: ";
	cin>>ymax;
	
	rectangle(xmin,ymin,xmax,ymax);
	
	cout<<"Enter the coordinates of the line: ";
	cin>>x0>>y0;
	cin>>x1>>y1;
	
	line(x0,y0,x1,y1);
	
	delay(5000);
	cleardevice();
	CSLCAD(x0,y0,x1,y1,xmin,xmax,ymin,ymax);
	rectangle(xmin,ymin,xmax,ymax);
	delay(50000);
	closegraph();
	return 0;
}
