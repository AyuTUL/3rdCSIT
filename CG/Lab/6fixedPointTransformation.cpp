#include<iostream>
#include<conio.h>
#include<graphics.h>
#include<math.h>
#define PI 3.141
using namespace std;
struct Point {
    int x,y;
};
void drawTriangle(Point p1,Point p2,Point p3,int color,const char* label) 
{
    setcolor(color);
    line(p1.x,p1.y,p2.x,p2.y);
    line(p2.x,p2.y,p3.x,p3.y);
    line(p3.x,p3.y,p1.x,p1.y);
    settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
    outtextxy(p1.x,p1.y-10,(char*)label);
}
Point scale(Point p,Point center,float sx,float sy) {
    return {
        (int)(center.x+(p.x-center.x)*sx),
        (int)(center.y+(p.y-center.y)*sy)
    };
}
Point rotate(Point p,Point center,float angle) {
    float rad=angle*PI/180.0,cosA=cos(rad),sinA=sin(rad);
    float dx=p.x-center.x,dy=p.y-center.y;
    return {
        (int)(center.x+dx*cosA-dy*sinA),
        (int)(center.y+dx*sinA+dy*cosA)
    };
}
int main() {
    int gd=DETECT,gm;
    Point p1,p2,p3;
    float sx,sy,angle;
    initgraph(&gd,&gm,"");
	if(graphresult()!=grOk)
    {
        cout<<"Graphics initialization failed"<<endl;
        return 1;
    }
    cout<<"Enter coordinates of triangle :"<<endl;
    cout<<"Point 1 (x1,y1) : ";cin>>p1.x>>p1.y;
    cout<<"Point 2 (x2,y2) : ";cin>>p2.x>>p2.y;
    cout<<"Point 3 (x3,y3) : ";cin>>p3.x>>p3.y;
    cout<<"Enter scaling factors (sx,sy) : ";cin>>sx>>sy;
    cout<<"Enter rotation angle (degrees) : ";cin>>angle;
    Point center={(p1.x+p2.x+p3.x)/3,(p1.y+p2.y+p3.y)/3};
    outtextxy(10,10,"Ayush Tuladhar");
	outtextxy(10,20,"Fixed Point 2D Translation");
    drawTriangle(p1,p2,p3,WHITE,"Original Triangle");
    Point sp1=scale(p1,center,sx,sy);
    Point sp2=scale(p2,center,sx,sy);
    Point sp3=scale(p3,center,sx,sy);
    drawTriangle(sp1,sp2,sp3,LIGHTMAGENTA,"Centroid Scaled");
    Point rp1=rotate(p1,center,angle);
    Point rp2=rotate(p2,center,angle);
    Point rp3=rotate(p3,center,angle);
    drawTriangle(rp1,rp2,rp3,LIGHTCYAN,"Centroid Rotated");
    getch();
    closegraph();
    return 0;
}