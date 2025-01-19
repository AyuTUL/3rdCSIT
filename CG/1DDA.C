#include<stdio.h>
void main()
{
	int gd=DETECT,gm;
	int x1,y1,x2,y2,steps,k;
	float xincr,yincr,x,y,dx,dy;
	printf("Enter starting co-ordinate : ");
	scanf("%d%d",&x1,&y1);
	printf("Enter ending co-ordinate : ");
	scanf("%d%d",&x2,&y2);
	initgraph(&gd,&gm,"C:\\TC\\BGI");
	dx=x2-x1;
	dy=y2-y1;
	if(abs(dx)>abs(dy))
		steps=abs(dx);
	else
		steps=abs(dy);
	xincr=dx/steps;
	yincr=dy/steps;
	x=x1;
	y=y1;
	for(k=1;k<=steps;k++)
	{
		x+=xincr;
		y+=yincr;
		putpixel(round(x),round(y),WHITE);
	}
	outtextxy(200,20,"DDA");
	outtextxy(x1+5,y1-5,"(x1,y1)");
	outtextxy(x2+5,y2+5,"(x2,y2)");
	getch();
	closegraph();
}
float round(float a)
{
	int b=a+0.5;
	return b;
}
