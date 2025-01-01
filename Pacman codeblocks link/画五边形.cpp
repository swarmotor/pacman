#include "graphics.h"
#include<math.h>
#include<stdio.h>
#include <conio.h>
#define PI 3.14
#define r 100
#define ORGX 100
#define ORGY 100
void main()
{
	initgraph(640,480);
	setcolor(RGB(0,0,255));
	moveto(r*sin(3*PI/10)+ORGX,0+ORGY);
	lineto(0+ORGX,r*sin(PI/5)+ORGY);
	lineto(r*sin(PI/10)+ORGX,r*sin(PI/5)+r*sin(2*PI/5)+ORGY);
	lineto(r*sin(PI/10)+r+ORGX,r*sin(PI/5)+r*sin(2*PI/5)+ORGY);
	lineto(2*r*sin(3*PI/10)+ORGX,r*sin(PI/5)+ORGY);
	lineto(r*sin(3*PI/10)+ORGX,0+ORGY);


/*a:  r*sin(3*PI/10),0
b:	0,r*sin(PI/5)
c:  2*r*sin(3*PI/10),r*sin(PI/5),
d:	r*sin(PI/10),r*sin(PI/5)+r*sin(2*PI/5)
e:	r*sin(PI/10)+r,r*sin(PI/5)+r*sin(2*PI/5)*/
	
	getch();closegraph();
}