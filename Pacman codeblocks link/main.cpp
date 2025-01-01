#include "head.h"
int main()
{
    initgraph(640,480);
	setfillcolor(RGB(0,0,0));
	fillrectangle(-1,-1,640,480);
    setcolor(RGB(255,255,55));
	settextstyle(90,0,"TRIPLEX_FONT");
	outtextxy(185,140,"Pacman");
	setcolor(RGB(255,255,255));
	settextstyle(40,0,"TRIPLEX_FONT");
	outtextxy(240,250,"ÖÇÊ÷×÷Æ·");
	Sleep(5000);
	closegraph();
	mainmenu();
	return 0;
}
