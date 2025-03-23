#include<graphics.h>
#include<stdio.h>
#include<math.h>
void drawEllipse(int xc,int yc,int rx,int ry){
	int x=0 ,y=ry;
	int rx2=rx*rx;
	int ry2=ry*ry;
	int tworx2=2*rx2;
	int twory2=2*ry2;
	int p1=ry2 -(rx2*ry)+(0.25*rx2);
	int dx=0;
	int dy=tworx2*y;
	while(dx< dy){
		putpixel(xc+x,yc+y,WHITE);
		putpixel(xc-x,yc+y,WHITE);
		putpixel(xc+x,yc-y,WHITE);
		putpixel(xc-x,yc-y,WHITE);
		x++;
		dx+=twory2;
		if(p1<0){
			p1+=ry2+dx;
		}
		else
		{
			y--;
			dy-=tworx2;
			p1+=ry2+dx-dy;
		}
	}
	int p2=ry2*(x+0.5)*(x+0.5)+rx2*(y-1)*(y-1)-rx2*ry2;
	
	while(y>=0){
	    putpixel(xc+x,yc+y,WHITE);
		putpixel(xc-x,yc+y,WHITE);
		putpixel(xc+x,yc-y,WHITE);
		putpixel(xc-x,yc-y,WHITE);
		y--;
		dy-=tworx2;
		if(p2>0)
		{
			p2+=rx2-dy;
			}
			else{
				x++;
				dx+=twory2;
				p2+=rx2-dy+dx;
			}	
	}
}
int main(){
	int gd=DETECT,gm;
	initgraph(&gd,&gm,NULL);
	int xc,yc,rx,ry;
	printf("Enter the center of the ellipse (xc,yc):");
	scanf("%d%d",&xc,&yc);
	printf("Enter the semi-major axis(rx):");
	scanf("%d",&rx);
	printf("Enter the semi-minor axis(ry):");
	scanf("%d",&ry);
	drawEllipse(xc,yc,rx,ry);
	getch();
	closegraph();
	return 0;
}