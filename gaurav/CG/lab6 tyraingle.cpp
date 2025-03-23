#include<iostream>
#include<graphics.h>
#include<cmath>
#include<cstring>
#include<conio.h>
 using namespace std;
 
 void drawtriangle(int x1,int y1,int x2,int y2,int x3,int y3,int color,const char* label)
 {
 	setcolor(color);
 	line(x1,y1,x2,y2);
 	line(x2,y2,x3,y3);
 	line(x3,y3,x1,y1);
 	
 	settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
 	char text[50];
 	strcpy(text,label);
 	outtextxy(x1,y1-10,text);
 	
 }
 
 void scale(int &x,int &y,int px,int py,float sx,float sy)
 {
 	x=px+(x-px)*sx;
 	y=py+(y-py)*sy;
 }
 
 void rotate(int &x,int &y,int px,int py,float angle)
 {
 	float rad= angle*(3.14159/180);
 	int x_new=px+(x-px)*cos(rad)-(y-py)*sin(rad);
 	int y_new=py+(x-px)*sin(rad)+(y-py)*cos(rad);
 	x=x_new;
 	y=y_new;
 }
 
 int main()
 {
 	int gd=DETECT,gm;
 	initgraph(&gd,&gm,"");
 	
 	int x1,y1,x2,y2,x3,y3;
 	float sx,sy,angle;
 	
 	cout<<"Enter coordinates of the traingle:\n";
 	cout<<"(x1,y1)=";
 	cin>>x1>>y1;
 	cout<<"(x2,y2)=";
 	cin>>x2>>y2;
 	cout<<"(x3,y3)=";
 	cin>>x3>>y3;
 	
 	cout<<"Enter rotation angle:(in degrees):";
 	cin>>angle;
 	
 	int cx=(x1+x2+x3)/3;
 	int cy=(y1+y2+y3)/3;
 	
 	drawtriangle(x1,y1,x2,y2,x3,y3,WHITE,"Original Traingle");
 	
 	int x1_scaled=x1,y1_scaled=y1;
 	int x2_scaled=x2,y2_scaled=y2;
 	int x3_scaled=x3,y3_scaled=y3;
 	
 	scale(x1_scaled,y1_scaled,cx,cy,sx,sy);
 	scale(x2_scaled,y2_scaled,cx,cy,sx,sy);
 	scale(x3_scaled,y3_scaled,cx,cy,sx,sy);
 	
 	drawtriangle(x1_scaled,y1_scaled,x2_scaled,y2_scaled,x3_scaled,y3_scaled,RED,"Centroid Scaled");
 	
 	int x1_rot=x1,y1_rot=y1;
 	int x2_rot=x2,y2_rot=y2;
 	int x3_rot=x3,y3_rot=y3;
 	
 	rotate(x1_rot,y1_rot,cx,cy,angle);
 	rotate(x2_rot,y2_rot,cx,cy,angle);
 	rotate(x3_rot,y3_rot,cx,cy,angle);
 	
 	drawtriangle(x1_rot,y1_rot,x2_rot,y2_rot,x3_rot,y3_rot,BLUE,"Rotated");
 	
 	getch();
 	closegraph();
 	return 0;
 }