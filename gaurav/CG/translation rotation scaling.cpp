#include<iostream>
#include<graphics.h>
#include<conio.h>
#include<stdlib.h>
#include<math.h>
using namespace std;
void drawline(int x1,int y1,int x2,int y2)
{
	line(x1,y1,x2,y2);
}

void trans(int x1,int y1,int x2,int y2,int x3,int y3)
{
	int tx,ty;
	int newx1,newy1,newx2,newy2,newx3,newy3;
	cout<<"Enter translation valuess:(tx,ty)\n";
	cin>>tx>>ty;
	newx1=x1+tx;
	newy1=y1+ty;
	newx2=x2+tx;
	newy2=y2+ty;
	newx3=x3+tx;
	newy3=y3+ty;
	
	cout<<"After translation:\n";
	
	drawline(newx1,newx1,newx2,newy2);
	drawline(newx2,newx2,newx3,newy3);
	drawline(newx3,newx3,newx1,newy1);
}
void scaling(int x1,int y1,int x2,int y2,int x3,int y3)
{
	float sx,sy;
	int newx1,newy1,newx2,newy2,newx3,newy3;
	
	cout<<"Enter scaling factor(sx,sy):";
	cin>>sx>>sy;
	newx1=x1*sx;
	newy1=y1*sy;
	newx2=x2*sx;
	newy2=y2*sy;
	newx3=x3*sx;
	newy3=y3*sy;
	cout<<"After scaling:\n";
	
	drawline(newx1,newx1,newx2,newy2);
	drawline(newx2,newx2,newx3,newy3);
	drawline(newx3,newx3,newx1,newy1);
}
void rotation(int x1,int y1,int x2,int y2,int x3,int y3)
{
	float angle,radian;
	int newx1,newy1,newx2,newy2,newx3,newy3;
	int cx=0,cy=0;
	cout<<"Enter rotation angle(indegrees):";
	cin>>angle;
	radian=(angle*3.14159)/180;
	
	newx1=(x1-cx)*cos(radian)-(y1-cy)*sin(radian)+cx;
	newy1=(x1-cy)*sin(radian)+(y1-cy)*cos(radian)+cy;
	newx2=(x2-cx)*cos(radian)-(y2-cy)*sin(radian)+cx;
	newy2=(x2-cy)*sin(radian)+(y2-cy)*cos(radian)+cy;
	newx3=(x3-cx)*cos(radian)-(y3-cy)*sin(radian)+cx;
	newy3=(x3-cy)*sin(radian)+(y3-cy)*cos(radian)+cy;
	
	cout<<"After rotation:\n";
	
	drawline(newx1,newx1,newx2,newy2);
	drawline(newx2,newx2,newx3,newy3);
	drawline(newx3,newx3,newx1,newy1);
}

int main()
{
	int gm,gd=DETECT;
	int x,x1,x2,x3,y1,y2,y3;
	char ch;
	initgraph(&gd,&gm,"");
	cout<<"enter coordiantes of triangle:(x1,y1),(x2,y2),(x3,y3):";
	cin>>x1>>y1>>x2>>y2>>x3>>y3;
	do{
		cout<<"Menu\n1.Translation\n2.Scaling\n3.Rotation\nEnter your choice:";
		cin>>x;
		
		switch(x)
		{
			case 1:
			    trans(x1,y1,x2,y2,x3,y3);
				break;
			case 2:
			    scaling(x1,y1,x2,y2,x3,y3);
				break;
			case 3:
				rotation(x1,y1,x2,y2,x3,y3);
				break;
		    
			default:
				cout<<"Wrong choiceeee!";
				break;
				
				
		}
		cout<<"Do you want to choose again:Y for yes and N for no\n:";
		cin>>ch;
		
	}while(ch=='Y'||ch=='y');
	closegraph();    
}