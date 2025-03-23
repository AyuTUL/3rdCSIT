#include<iostream>
#include<graphics.h>
#include<cmath>
#include<conio.h>
using namespace std;
void bresenham(int x1,int y1,int x2,int y2){
	char p1[50],p2[50];
	int x,y,xend;
	float dx,dy,p;
	dx=abs(x2-x1);
	dy=abs(y2-y1);
	p=2*dy-dx;
	if(x1>x2){
		x=x2;
		y=y2;
		xend=x1;
	}else{
		x=x1;
		y=y1;
		xend=x2;
	}
	outtextxy(150,0,"Bresenham Line Drawing Algorithm");
	sprintf(p1,"(%d,%d)",x1,y1);
	outtextxy(x1-15,y1-15,p1);
	while(x<xend){
		x++;
		if(p>=0){
			y++;
			p+=2*(dy-dx);
		}else{
			p+=2*dy;
		}
		putpixel(round(x),round(y),WHITE);
		
	}
	sprintf(p2,"(%d,%d)",x2,y2);
	outtextxy(x2+5,y2+5,p2);
	getch();
}
int main(){
	int x1,y1,x2,y2;
	int gd=DETECT,gm;
	initgraph(&gd, &gm, "");
	cout<<"Enter(x1,y1): ";
	cin>>x1>>y1;
	cout<<"Enter(x2,y2): ";
	cin>>x2>>y2;
	bresenham(x1,y1,x2,y2);
	closegraph();
	return 0;
}
