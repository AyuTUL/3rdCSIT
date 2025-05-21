#include<iostream>
#include<conio.h>
#include<graphics.h>
#include<math.h>
#define PI 3.141
using namespace std;
struct Point 
{
    int x,y;
};
void drawTriangle(Point p1,Point p2,Point p3) 
{
    line(p1.x,p1.y,p2.x,p2.y);
    line(p2.x,p2.y,p3.x,p3.y);
    line(p3.x,p3.y,p1.x,p1.y);
}
Point translate(Point p,int tx,int ty)
{
	return {p.x+tx,p.y+ty};
}
Point scale(Point p, float sx, float sy)
{
	return {(int)p.x*sx,(int)p.y*sy};
}
Point rotate(Point p,float angle,Point center) 
{
    float rad=angle*PI/180.0,cosA=cos(rad),sinA=sin(rad);
    float x=p.x-center.x;
    float y=p.y-center.y;
    float xr=x*cosA-y*sinA+center.x;
    float yr=x*sinA+y*cosA+center.y;
    return {(int)xr,(int)yr};
}
int main()
{
	system("color f0");
	int gd=DETECT,gm,choice;
	initgraph(&gd,&gm,NULL);
	if(graphresult()!=grOk)
    {
        cout<<"Graphics initialization failed"<<endl;
        return 1;
    }
    Point p1,p2,p3;
    cout<<"Enter coordinates of triangle :"<<endl;
    cout<<"Point 1 (x1,y1) : ";cin>>p1.x>>p1.y;
    cout<<"Point 2 (x2,y2) : ";cin>>p2.x>>p2.y;
    cout<<"Point 3 (x3,y3) : ";cin>>p3.x>>p3.y; 
	do
	{
		cleardevice();
        setcolor(WHITE);
        drawTriangle(p1,p2,p3);
		outtextxy(10,10,"Ayush Tuladhar");
		outtextxy(10,20,"2D Translation");
        cout<<"Basic 2D Transformations:\n1. Translation\n2. Scaling\n3. Rotation\n4. Exit\nEnter your choice : ";
        cin>>choice;
        switch(choice) 
		{
            case 1: 
			{
                int tx,ty;
                cout<<"Enter translation values (tx,ty) : ";
                cin>>tx>>ty;
                Point tp1=translate(p1,tx,ty);
                Point tp2=translate(p2,tx,ty);
                Point tp3=translate(p3,tx,ty);
                setcolor(MAGENTA);
				drawTriangle(tp1,tp2,tp3);
                break;
            }
            case 2: 
			{
                float sx,sy;
                cout<<"Enter scaling factors (sx,sy) : ";
                cin>>sx>>sy;
                Point sp1=scale(p1,sx,sy);
                Point sp2=scale(p2,sx,sy);
                Point sp3=scale(p3,sx,sy);
                setcolor(CYAN);
                drawTriangle(sp1,sp2,sp3);
                break;
            }
            case 3: 
			{
                float angle;
                cout<<"Enter rotation angle (degrees) : ";
                cin>>angle;
                Point center;
    			center.x=(p1.x+p2.x+p3.x)/3;
    			center.y=(p1.y+p2.y+p3.y)/3;
                Point rp1=rotate(p1,angle,center);
                Point rp2=rotate(p2,angle,center);
                Point rp3=rotate(p3,angle,center);
                setcolor(GREEN);
                drawTriangle(rp1,rp2,rp3);
                break;
            }
            case 4:
                break;
            default:
                cout<<"Invalid choice"<<endl;
                break;
        }
        getch();
        cout<<endl;
    } while(choice!=4);
    closegraph();
    return 0;
}