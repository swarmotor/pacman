#include <math.h>
#include <conio.h>
#include <stdio.h>
#include <graphics.h>
#define PI 3.14
#define INFOX 760
#define INFOY 30
typedef struct
{
	int month;
	int day;
	int hour;
	int minute;
	int second;

}TIME;
DWORD dwStart;
int bean_number;
int SCORE;
int STEP;
void draw_ibboard(void);
void draw_time(void);
void draw_info(void);
void main()
{
	SCORE=1234;
	STEP=37;
	dwStart = GetTickCount();
	bean_number=30;
	draw_time();
	draw_info();
	draw_ibboard();
	while(1)
	{
		draw_time();
	    draw_info();
	}
	getch();
	closegraph();


}
void draw_ibboard(void)
{
	//dabeiban
	setcolor(RGB(139,69,19));
	setfillcolor(RGB(0,0,0));
	bar3d(INFOX,INFOY,INFOX+460,INFOY+660,10,1);
    //TIME beiban
	setcolor(RGB(139,69,19));
	setfillcolor(RGB(139,69,19));
	bar3d(INFOX+140,INFOY+40,INFOX+320,INFOY+110,10,1);
	//TIME zijineirong
	setcolor(RGB(255,255,255));
	setfillcolor(RGB(255,255,0));
	setfont(50,25,"");
	outtextxy(INFOX+180,INFOY+50,"TIME");
	//shijian beiban
	setcolor(RGB(169,169,169));
	setfillcolor(RGB(169,169,169));
	fillrectangle(INFOX+45,INFOY+130,INFOX+150,INFOY+190);
	setcolor(RGB(169,169,169));
	setfillcolor(RGB(169,169,169));
	fillrectangle(INFOX+180,INFOY+130,INFOX+285,INFOY+190);
	setcolor(RGB(169,169,169));
	setfillcolor(RGB(169,169,169));
	fillrectangle(INFOX+315,INFOY+130,INFOX+420,INFOY+190);
	//shijian maohao
	setcolor(RGB(169,169,169));
	setfillcolor(RGB(169,169,169));
	fillrectangle(INFOX+160,INFOY+145,INFOX+170,INFOY+155);
	setcolor(RGB(169,169,169));
	setfillcolor(RGB(169,169,169));
	fillrectangle(INFOX+160,INFOY+165,INFOX+170,INFOY+175);
	setcolor(RGB(169,169,169));
	setfillcolor(RGB(169,169,169));
	fillrectangle(INFOX+295,INFOY+145,INFOX+305,INFOY+155);
	setcolor(RGB(169,169,169));
	setfillcolor(RGB(169,169,169));
	fillrectangle(INFOX+295,INFOY+165,INFOX+305,INFOY+175);
	//hua wubian xing
	int r=50;
	setcolor(RGB(255,215,0));
	moveto(r*sin(3*PI/10)+INFOX+45,0+INFOY+220);
	lineto(0+INFOX+45,r*sin(PI/5)+INFOY+220);
	lineto(r*sin(PI/10)+INFOX+45,r*sin(PI/5)+r*sin(2*PI/5)+INFOY+220);
	lineto(r*sin(PI/10)+r+INFOX+45,r*sin(PI/5)+r*sin(2*PI/5)+INFOY+220);
	lineto(2*r*sin(3*PI/10)+INFOX+45,r*sin(PI/5)+INFOY+220);
	lineto(r*sin(3*PI/10)+INFOX+45,0+INFOY+220);
	setfillcolor(RGB(255,215,0));
	floodfill(r*sin(3*PI/10)+INFOX+45,INFOY+250,RGB(255,215,0));
	//you score beiban
	setcolor(RGB(255,215,0));
	setfillcolor(RGB(255,215,0));
	fillrectangle(INFOX+185,INFOY+230,INFOX+435,INFOY+300);
	//score beiban
	setcolor(RGB(255,215,0));
	setfillcolor(RGB(255,215,0));
	fillrectangle(INFOX+30,INFOY+330,INFOX+430,INFOY+430);
	//YOU SCORE
	setcolor(RGB(255,0,0));
	setfont(50,25,"");
	outtextxy(INFOX+200,INFOY+240,"YOU SCORE");
	//you step beiban
	setcolor(RGB(138,5,237));
	setfillcolor(RGB(138,5,237));
	fillrectangle(INFOX+40,INFOY+460,INFOX+200,INFOY+505);
	//YOU STEP
	setcolor(RGB(132,232,11));
	setfont(35,15,"");
	outtextxy(INFOX+60,INFOY+466,"YOU STEP");
	//remain beans beiban
	setcolor(RGB(138,5,237));
	setfillcolor(RGB(138,5,237));
	fillrectangle(INFOX+220,INFOY+460,INFOX+420,INFOY+505);
	//REMAIN BEANS
	setcolor(RGB(132,232,11));
	setfont(35,15,"");
	outtextxy(INFOX+230,INFOY+466,"REMAIN BEANS");
	//you step beiban
	setcolor(RGB(13,191,230));
	setfillcolor(RGB(13,191,230));
	fillrectangle(INFOX+50,INFOY+520,INFOX+190,INFOY+620);
	//remain beiban
	setcolor(RGB(233,210,10));
	setfillcolor(RGB(233,210,10));
	fillrectangle(INFOX+250,INFOY+520,INFOX+390,INFOY+620);
	
}
void draw_time(void)
{
	char str[3]={0};
	DWORD dwEnd = GetTickCount();
	//shijian shuzi
	setcolor(RGB(255,255,255));
	setfillcolor(RGB(255,255,0));
	setfont(50,30,"");
	sprintf(str,"%02d",(dwEnd-dwStart)/1000/60);
	outtextxy(INFOX+70,INFOY+135,str);
	setcolor(RGB(255,255,255));
	setfillcolor(RGB(258,255,0));
	setfont(50,30,"");
	sprintf(str,"%02d",(dwEnd-dwStart)/1000%60);
	outtextxy(INFOX+203,INFOY+135,str);
	setcolor(RGB(255,255,255));
	setfillcolor(RGB(255,255,0));
	setfont(50,30,"");
	sprintf(str,"%02d",(dwEnd-dwStart)%1000/10);
	outtextxy(INFOX+338,INFOY+135,str);
}
void draw_info(void)
{
	char str[4]={0};
	//score wenzi
	setcolor(RGB(255,0,0));
	setfont(70,50,"");
	sprintf(str,"%d",SCORE/1000);
	outtextxy(INFOX+55,INFOY+345,str);
	setcolor(RGB(255,0,0));
	setfont(70,50,"");
	sprintf(str,"%d",SCORE%1000/100);
	outtextxy(INFOX+155,INFOY+345,str);
	setcolor(RGB(255,0,0));
	setfont(70,50,"");
	sprintf(str,"%d",SCORE%100/10);
	outtextxy(INFOX+255,INFOY+345,str);
	setcolor(RGB(255,0,0));
	setfont(70,50,"");
	sprintf(str,"%d",SCORE%10);
	outtextxy(INFOX+355,INFOY+345,str);	
	//YOU STEP
	setcolor(RGB(255,255,255));
	setfont(90,45,"");
	sprintf(str,"%03d",STEP);
	outtextxy(INFOX+53,INFOY+525,str);	
	//REMAIN BEANS wenzi
	setfont(90,45,"");
	if(bean_number<=10)
	    setcolor(RGB(255,0,0));
	else
		if(bean_number<=20)
		    setcolor(RGB(0,0,255));
		else
			setcolor(RGB(0,255,0));
	sprintf(str,"%03d",bean_number);
	outtextxy(INFOX+253,INFOY+525,str);
}