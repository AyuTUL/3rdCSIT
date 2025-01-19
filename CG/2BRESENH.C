#include<stdio.h>
#include<conio.h>
#include<graphics.h>
void main()
{
	int x,y,x1,y1,x2,y2,p,dx,dy;
	int gd=DETECT,gm;
	initgraph(&gd,&gm,"C:\\TC\\BGI");
	printf("Enter 1st co-ordinate : ");
	scanf("%d%d",&x1,&y1);
	printf("Enter 2nd co-ordinate : ");
	scanf("%d%d",&x2,&y2);
	x=x1;
	y=y1;
	dx=x2-x1;
	dy=y2-y1;
	putpixel(x,y,2);
	p=(2*dy-dx);
	while(x<=x2)
	{
		if(p<0)
		{
			x++;
			p+=2*dy;
		}
		else
		{
			x++;
			y++;
			p+=(2*dy)-(2*dx);
		}
		putpixel(x,y,7);
	 }
	 outtextxy(1,40,"Ayush Tuladhar");
	 outtextxy(1,50,"Bresenham");
	 outtextxy(x1+5,y1-5,"(x1,y1)");
	 outtextxy(x2+5,y2+5,"(x2,y2)");
	 getch();
	 closegraph();
 }



