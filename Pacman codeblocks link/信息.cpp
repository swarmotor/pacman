#include <time.h>
#include <math.h>
#include <conio.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <windows.h>
#include <graphics.h>
#define screenx 1280
#define screeny 720
#define ORGX 60
#define ORGY 60
#define PI 3.14
typedef struct
{
    int x;
    int y;
}BOSS;
typedef struct
{
    int x;
    int y;
}PACMAN;
typedef struct
{
    int x;
    int y;
}BEAN;
typedef struct
{
	int x;
	int y;
}WALL;
typedef struct
{
	int month;
	int day;
	int hour;
	int minute;
	int second;

}TIME;

BOSS boss_a,boss_b;
PACMAN pacman_a;
BEAN *bean_member;
WALL *wall_member;

int score;
int step;
int bean_number;
int wall_number;
int ROW,COL;
int GWID,GHEI;
int tx,ty;

void readmap(void);
void drawmap(void);


void main()
{
	tx=760;
	ty=30;
	

	initgraph(screenx,screeny);
	//dabeiban
	setcolor(RGB(255,255,255));
	rectangle(tx,ty,tx+460,ty+660);
    //TIME beiban
	setfillcolor(RGB(255,255,255));
	fillrectangle(tx+140,ty+40,tx+320,ty+110);
    //TIME zijineirong
	setfillcolor(RGB(255,255,0));
	setfont(50,25,"");
	outtextxy(tx+180,ty+50,"TIME");
	//shijian beiban
	setfillcolor(RGB(255,255,255));
	fillrectangle(tx+45,ty+130,tx+150,ty+190);
	setfillcolor(RGB(255,255,255));
	fillrectangle(tx+180,ty+130,tx+285,ty+190);
	setfillcolor(RGB(255,255,255));
	fillrectangle(tx+315,ty+130,tx+420,ty+190);
	//shijian maohao
	setfillcolor(RGB(255,255,255));
	fillrectangle(tx+160,ty+145,tx+170,ty+155);
	setfillcolor(RGB(255,255,255));
	fillrectangle(tx+160,ty+165,tx+170,ty+175);
	setfillcolor(RGB(255,255,255));
	fillrectangle(tx+295,ty+145,tx+305,ty+155);
	setfillcolor(RGB(255,255,255));
	fillrectangle(tx+295,ty+165,tx+305,ty+175);
	//shijian shuzi
	setfillcolor(RGB(255,255,0));
	setfont(50,30,"");
	outtextxy(tx+70,ty+135,"00");
	setfillcolor(RGB(258,255,0));
	setfont(50,30,"");
	outtextxy(tx+203,ty+135,"00");
	setfillcolor(RGB(255,255,0));
	setfont(50,30,"");
	outtextxy(tx+338,ty+135,"00");
	//hua wubian xing
	int r=50;
	setcolor(RGB(0,0,255));
	moveto(r*sin(3*PI/10)+tx+45,0+ty+220);
	lineto(0+tx+45,r*sin(PI/5)+ty+220);
	lineto(r*sin(PI/10)+tx+45,r*sin(PI/5)+r*sin(2*PI/5)+ty+220);
	lineto(r*sin(PI/10)+r+tx+45,r*sin(PI/5)+r*sin(2*PI/5)+ty+220);
	lineto(2*r*sin(3*PI/10)+tx+45,r*sin(PI/5)+ty+220);
	lineto(r*sin(3*PI/10)+tx+45,0+ty+220);
	floodfill(r*sin(3*PI/10)+tx+45,ty+250,RGB(0,0,255));
	//you score beiban
	setfillcolor(RGB(255,255,255));
	fillrectangle(tx+185,ty+230,tx+435,ty+300);
	//YOU SCORE
	setcolor(RGB(255,0,0));
	setfont(50,25,"");
	outtextxy(tx+200,ty+240,"YOU SCORE");
	//score beiban
	setcolor(RGB(255,255,255));
	setfillcolor(RGB(255,255,255));
	fillrectangle(tx+30,ty+330,tx+430,ty+430);
	//score wenzi
	setcolor(RGB(255,0,0));
	setfont(70,50,"");
	outtextxy(tx+55,ty+345,"0");
	setcolor(RGB(255,0,0));
	setfont(70,50,"");
	outtextxy(tx+155,ty+345,"0");
	setcolor(RGB(255,0,0));
	setfont(70,50,"");
	outtextxy(tx+255,ty+345,"0");
	setcolor(RGB(255,0,0));
	setfont(70,50,"");
	outtextxy(tx+355,ty+345,"0");
	//you step beiban
	setfillcolor(RGB(255,255,255));
	fillrectangle(tx+40,ty+460,tx+200,ty+505);
	//YOU STEP
	setcolor(RGB(255,255,255));
	setfont(35,15,"");
	outtextxy(tx+60,ty+466,"YOU STEP");
	//remain beans
	setfillcolor(RGB(255,255,255));
	fillrectangle(tx+220,ty+460,tx+420,ty+505);
	//REMAIN BEANS
	setcolor(RGB(255,255,255));
	setfont(35,15,"");
	outtextxy(tx+230,ty+466,"REMAIN BEANS");
	//you step beiban
	setfillcolor(RGB(255,255,255));
	fillrectangle(tx+50,ty+520,tx+190,ty+620);
	//YOU STEP
	setcolor(RGB(255,255,255));
	setfont(90,45,"");
	outtextxy(tx+53,ty+525,"000");
	//remain beiban
	setfillcolor(RGB(255,255,255));
	fillrectangle(tx+250,ty+520,tx+390,ty+620);
	//REMAIN BEANS wenzi
	setcolor(RGB(255,255,255));
	setfont(90,45,"");
	outtextxy(tx+253,ty+525,"000");


	getch();
	closegraph();
}


