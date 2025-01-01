#include <ctime>
#include <time.h>
#include <math.h>
#include <cstdio>
#include <conio.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <windows.h>
#include <graphics.h>

#define screenx 1280
#define screeny 720
#define INFOX 760
#define INFOY 30
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
DWORD dwStart;
BOSS boss_a,boss_b;
PACMAN pacman_a;
BEAN *bean_member;
WALL *wall_member;

int escgame=0;
int ROUND;

int LEVEL;
int SCORE;
int STEP;
int bean_number;
int wall_number;
int bean_numbert;
int ROW,COL;
int GWID,GHEI;
char *map;
char *TOP_SCORE[10];
char readmap_name[20];
char createmap_name[20];

void mainmenu(void);

void New_game(void);
void Producenew_map(void);
void High_score(void);

void rungame(void);
void readmap(void);
void drawmap(void);

void draw_ibboard(void);
void draw_time(void);
void draw_info(void);

void build(void);
void buildnpc(void);
void buildmapfile(char *str);

void writescore(void);
void readscore(void);
void drawtopscore(void);

void drawbean(void);
void cleanpacman(void);
void drawpacman(char c);
void runboss(void);
void judgeesc(void);
int judgestep(char c);

void cleanboss_a(void);
void cleanboss_b(void);
int judgestep_boss(int c,int t);
void drawboss(void);

void overwindow(int flag);
//系统欢迎界面
void main()
{
    initgraph(640,480);
	setfillcolor(RGB(0,0,0));
	fillrectangle(-1,-1,640,480);
    setcolor(RGB(255,255,55));
	settextstyle(90,0,"TRIPLEX_FONT");
	outtextxy(185,140,"Pacman");
	setcolor(RGB(255,255,255));
	settextstyle(40,0,"TRIPLEX_FONT");
	outtextxy(240,250,"智树作品");
	Sleep(5000);
	closegraph();
	mainmenu();
}
//主菜单界面
void mainmenu()
{
    char option,sign;
	system("cls");
    printf("                                      Pacman\n");
    printf("--------------------------------------------------------------------------------");
    printf("1. New games .\n");
    printf("2. Create new map .\n");
    printf("3. High score .\n");
    printf("4. Exit game .\n");
    do
    {
        printf("Please enter the serial number: ");
        fflush(stdin);
        scanf("%1c",&option);
        fflush(stdin);
        if(option<'1'||option>'4'){
            printf("Error! Do you want finish the program ?\n");
            printf("Please enter the Y or N : ");
            scanf("%c",&sign);
            if(toupper(sign)!='N')
                exit(0);
        }
    }while(option<'1'||option>'4');
    fflush(stdin);
    switch(option)
    {
        case '1' : New_game();       break;
        case '2' : Producenew_map(); break;
        case '3' : High_score();     break;
        case '4' : exit(0);          break;
    }
    mainmenu();
}
//游戏开始，准备界面
void New_game(void)
{
	char c;
    system("cls");
    printf("                                      Pacman\n");
    printf("--------------------------------------------------------------------------------");
    printf("Map list :\n");
    system("dir");
    printf("Which one do you want to map ?\n");
    do
    {
        gets(readmap_name);
		if(strstr(readmap_name,".txt")==NULL)
			strcat(readmap_name,".txt");
		break;
		char str[15];
		strcpy(str,readmap_name);
        HANDLE hFile=CreateFileA(str,GENERIC_READ,NULL,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_ARCHIVE,NULL);
        if(INVALID_HANDLE_VALUE==hFile){
            printf("Map does not exist !\n");
            printf("Please write again !\n");
        }
		else
			break;
    }while(1);
	system("cls");
    printf("                                      Pacman\n");
    printf("--------------------------------------------------------------------------------");
	do
	{
		printf("Please enter the LEVEL\n");
		printf("1. EASY .\n");
		printf("2. COMMON.\n");
		printf("3. DIFFICULT .\n");
		c=getch();
	}while(c<'1'||c>'3');
	if(c=='1')
		LEVEL=15;
	else
		if(c=='2')
			LEVEL=10;
		else
			LEVEL=5;
    rungame();
}

void rungame(void)
{
	int i;
	int f=0;
	srand((unsigned)time(NULL));
	initgraph(screenx,screeny);
	SCORE=0;
	readmap();
	drawmap();	
	draw_ibboard();
	draw_time();
	draw_info();
	bean_numbert=bean_number;
	ROUND=GWID<GHEI?GWID/2-8:GHEI/2-8;
	dwStart=GetTickCount();
	drawbean();
	drawboss();
	//DEL
	drawpacman(-1);
	while(escgame==0)
	{
		draw_time();
		DWORD dwEnd = GetTickCount();
		if((dwEnd-dwStart)%1000==0)
			runboss();
		if(kbhit()){
			runboss();
			char c;
			c=getch();
			if(c==27){
				escgame=-1;
				continue;
			}
			if(c=='w'||c=='W'||c=='a'||c=='A'||c=='s'||c=='S'||c=='d'||c=='D'){
				if(judgestep(c)){
					cleanpacman();
					switch(c)
					{
					    case 'w' : case 'W' : (pacman_a.y)--; break;
						case 'a' : case 'A' : (pacman_a.x)--; break;
						case 's' : case 'S' : (pacman_a.y)++; break;
						case 'd' : case 'D' : (pacman_a.x)++; break;
					}
					drawpacman(c);
					STEP++;
					judgeesc();
					for(i=0;i<bean_numbert;i++)
						if((pacman_a.x==bean_member[i].x)&&(pacman_a.y==bean_member[i].y)){
							bean_number--;
							bean_member[i].x=-1;
							bean_member[i].y=-1;
							SCORE+=150;
							DWORD dwEnd = GetTickCount();
							//额外加分
							if(!f&&(bean_numbert-bean_number)==10){
								if((dwEnd-dwStart)/1000<=30)
									SCORE+=300;
								if((dwEnd-dwStart)/1000<=60)
									SCORE+=50;
							}
							if(bean_number==0){
								if((dwEnd-dwStart)/1000<=60)
									SCORE+=500;
								if((dwEnd-dwStart)/1000<=60)
									SCORE+=100;
								escgame=1;
								continue;
							}
							draw_info();
							break;
						}
				}
				else
					continue;
			}
			else
			    continue;
		}
	}
	draw_info();
	writescore();
	overwindow(escgame);
}

void readmap(void)
{
	FILE *fp;
	int i,j,bm,wm,f=0;
	char *p;
	if((fp=fopen(readmap_name,"r"))==NULL){
		printf("Map open error !\n");
		exit(-1);
	}
	fscanf(fp,"%d,%d",&ROW,&COL);
	GWID=600/COL;
	GHEI=600/ROW;
	bean_number=0;
	wall_number=0;
	p=map=(char*)malloc(sizeof(char)*ROW*COL);
	while(!feof(fp)){
		char c;
		fscanf(fp,"%c",&c);
		if(c==48)
			bean_number++;
		if(c=='\n')
			continue;
		else
			*(p++)=c;
	}
	fclose(fp);
	*p=0;
	p=map;
	wall_number=ROW*COL-3-bean_number;
	bean_member=(BEAN*)malloc(sizeof(BEAN)*bean_number);
	wall_member=(WALL*)malloc(sizeof(WALL)*wall_number);
	bm=0;
	wm=0;
	for(i=0;i<ROW;i++)
		for(j=0;j<COL;j++)
			switch(*p++)
		{
				case '0' : bean_member[bm].x=j; bean_member[bm].y=i; bm++; break;
				case '1' : wall_member[wm].x=j; wall_member[wm].y=i; wm++; break;
				case 'P' : pacman_a.x=j; pacman_a.y=i; break;
				case 'M' : 
					       if(f==0){
							   boss_a.x=j;
							   boss_a.y=i;
							   f=1;						   
						   }
						   else{
							   boss_b.x=j;
							   boss_b.y=i;
						   }
		}
	drawmap();
}
void drawmap(void)
{
	int i;
	setcolor(RGB(255,255,255));
	rectangle(ORGX,ORGY,ORGX+600,ORGY+600);
	for(i=0;i<wall_number;i++){
		setcolor(RGB(255,255,255));
		setfillcolor(RGB(131,97,50));
		if(wall_member[i].y==0)
			bar3d(ORGX+wall_member[i].x*GWID,ORGY+wall_member[i].y*GHEI,ORGX+wall_member[i].x*GWID+GWID,ORGY+wall_member[i].y*GHEI+GHEI,5,1);
		else 
			if(wall_member[i].x==(ROW-1))
			     bar3d(ORGX+wall_member[i].x*GWID,ORGY+wall_member[i].y*GHEI,ORGX+wall_member[i].x*GWID+GWID,ORGY+wall_member[i].y*GHEI+GHEI,5,0);
		    else
				fillrectangle(ORGX+wall_member[i].x*GWID,ORGY+wall_member[i].y*GHEI,ORGX+wall_member[i].x*GWID+GWID,ORGY+wall_member[i].y*GHEI+GHEI);
	}
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
	setcolor(RGB(157,258,247));
	//setfillcolor(RGB(255,255,0));
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
	sprintf(str,"%02d",(dwEnd-dwStart)/1000/60%60);
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

void Producenew_map(void)
{
	int i,j;
	int sizescreen;
    system("cls");
	srand((unsigned)time(NULL));
    printf("                                      Pacman\n");
    printf("--------------------------------------------------------------------------------");
    printf("please write a name for the new map :\n");
    while(1)
    {
        gets(createmap_name);
		if(strstr(createmap_name,".txt")==NULL)
			strcat(createmap_name,".txt");
		char str[15];
		strcpy(str,createmap_name);
        HANDLE hFile=CreateFileA(str,GENERIC_READ,NULL,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_ARCHIVE,NULL);
        if(INVALID_HANDLE_VALUE==hFile)
            break;
        else{
            printf("File name repetition !\n");
            printf("Please write again !\n");
        }
    }
    printf("How many Rows & Cols you want ?\n");
    do
    {
        scanf("%d %d",&ROW,&COL);
        if(ROW*COL<25||ROW*COL>400){
            if(ROW*COL<25)
                printf("Too small !\n");
            else
                printf("Too big !\n");
            printf("Please write again !\n");
        }
    }while(ROW*COL<25||ROW*COL>400);
	sizescreen=(int)sqrt(pow(ROW,2)+pow(COL,2));
	do
    {
        buildnpc();
        double distance_a,distance_b;
        distance_a=sqrt(pow(boss_a.x-pacman_a.x,2)+pow(boss_a.y-pacman_a.y,2));
        distance_b=sqrt(pow(boss_b.x-pacman_a.x,2)+pow(boss_b.y-pacman_a.y,2));
        if(distance_a>sizescreen/2&&distance_b>sizescreen/2)
            break;
    }while(1);
	bean_number=rand()%(ROW*COL/3)+(int)(ROW*COL/3);
	map=(char*)malloc(ROW*COL);
	for(i=0;i<ROW;i++){
		for(j=0;j<COL;j++)
			map[i*COL+j]='1';
	}
	map[pacman_a.x+pacman_a.y*COL]='P';
	map[boss_a.x+boss_a.y*COL]='M';
	map[boss_b.x+boss_b.y*COL]='M';
	build();
	printf("File produce OK !\n");
	printf("Press any key to continue !\n");
	getch();
	buildmapfile(createmap_name);
    free(map);
}
void buildnpc(void)
{
        boss_a.x=rand()%COL;
        boss_a.y=rand()%ROW;
        boss_b.x=rand()%COL;
        boss_b.y=rand()%ROW;
        pacman_a.x=rand()%COL;
        pacman_a.y=rand()%ROW;
}
void build(void)
{
	int i,j;
	int *place;
	place=(int*)malloc(sizeof(int)*bean_number);
	do
	{
		for(i=0;i<bean_number;i++){
			place[i]=rand()%(ROW*COL);
			if((place[i]+1)%COL==0||place[i]%COL==0||place[i]<COL-1||place[i]>(ROW-1)*COL)
				i--;
			for(j=0;j<i;j++)
				if(place[i]==place[j])
					i--;
		}
		for(i=0;i<bean_number;i++){
			int f=0;
			for(j=0;j<bean_number&&f!=2;i++){
				if(i==j)
					continue;
				if((place[i]%COL==(place[j]%COL+1)||place[i]%COL==(place[j]%COL-1))&&(place[i]/COL==place[j]/COL))
					f++;
				if((place[i]/COL==(place[j]/COL+1)||place[i]/COL==(place[j]/COL-1))&&(place[i]%COL==place[j]%COL))
					f++;
			}
			if(f==2)
				continue;
			else
				break;
		}
	}while(i<bean_number);
	for(i=0;i<bean_number;i++)
		map[place[i]]='0';
}

void buildmapfile(char *str)
{
	int i,j;
	FILE *fp;
	if((fp=fopen(str,"w"))==NULL){
		printf("File open error !\n");
		exit(-1);
	}
	fprintf(fp,"%d,%d",ROW,COL);
	fprintf(fp,"\n");
	for(i=0;i<ROW;i++){
		for(j=0;j<COL;j++)
			fprintf(fp,"%c",map[i*COL+j]);
		fprintf(fp,"\n");
	}
	fclose(fp);
}
void High_score(void)
{
	readscore();
}

void writescore(void)
{
	FILE *fp;
	time_t t;
    t=time(&t);
	char str[50]={0};
	char strt[5]={0};
	sprintf(str,"%s",ctime(&t));
	str[24]=0;	
	sprintf(strt,"%04d",SCORE);
	strcat(str,"  ||  SCORE:");
	strcat(str,strt);
	strcpy(strt,"TIME:");
	strcat(strt,str);
	if((fp=fopen("SCORE.txt","a+"))==NULL){
		printf("File open error !\n");
		exit(-1);
	}
	fseek(fp,0,2);
	if(feof(fp)){
		printf("sadgasdg");
	}
	fprintf(fp,"%s\n",strt);
	fclose(fp);
}
void readscore(void)
{
	FILE *fp;
	int i,j,n=0;
	int score[100];
	char *str[100];
	if((fp=fopen("SCORE.txt","r"))==NULL){
		printf("File open error !\n");
		exit(-1);
	}
	for(i=0;i<100;i++)
		str[i]=(char*)malloc(50);
	while(!feof(fp)&&n<100){
		char c;
		char *p;
		p=str[n];
		do
		{
			fscanf(fp,"%c",&c);
			*p++=c;
		}while(c!='\n');
		*(p-1)=0;
		n++;
	}
	n--;
	fclose(fp);
	for(i=0;i<n;i++)
		score[i]=(str[i][41]-'0')*1000+(str[i][42]-'0')*100+(str[i][43]-'0')*10+(str[i][44]-'0');
	for(i=0;i<n;i++)
        for(j=i+1;j<n;j++)
            if(score[j]>score[i]){
				int t;
				char strt[50];
                t=score[i];
				score[i]=score[j];
				score[j]=t;
				strcpy(strt,str[i]);
				strcpy(str[i],str[j]);
				strcpy(str[j],strt);
            }
	for(i=0;i<10&&i<n;i++){
		TOP_SCORE[i]=(char *)malloc(50);
		strcpy(TOP_SCORE[i],str[i]);
	}
	initgraph(640,720);
	drawtopscore();
	getch();
	closegraph();
}
void drawtopscore(void)
{
	setcolor(RGB(255,162,0));
	setfillcolor(RGB(255,162,0));
	fillrectangle(80,20,560,135);
	setcolor(RGB(29,113,207));
	setfillcolor(RGB(29,113,207));
	fillrectangle(35,145,605,195);
	fillrectangle(35,205,605,255);
	fillrectangle(35,265,605,315);
	fillrectangle(35,325,605,375);
	fillrectangle(35,385,605,435);
	fillrectangle(35,445,605,495);
	fillrectangle(35,505,605,555);
	fillrectangle(35,565,605,615);
	fillrectangle(35,625,605,675);
	setcolor(RGB(255,162,0));
	setfont(90,45,"");
	outtextxy(120,33,"TOP SCORE");
	setfont(22,10,"");
	setcolor(RGB(29,113,207));
	for(int i=0;i<9;i++)
	    outtextxy(75,158+i*60,TOP_SCORE[i]);
}

//游戏主操作函数
void drawbean(void)
{
	int i;
	for(i=0;i<bean_number;i++){
		setcolor(RGB(240,220,10));
		setfillcolor(RGB(240,220,10));
		fillcircle(ORGX+bean_member[i].x*GWID+GWID/2,ORGY+bean_member[i].y*GHEI+GHEI/2,ROUND);
	}

}
void cleanpacman(void)
{
	setcolor(RGB(0,0,0));
	setfillcolor(RGB(0,0,0));
	fillcircle(ORGX+pacman_a.x*GWID+GWID/2,ORGY+pacman_a.y*GHEI+GHEI/2,ROUND);
}
void drawpacman(char c)
{
	static char t='d';
	double x,y;
	double a;
	setcolor(RGB(255,0,0));
	setfillcolor(RGB(255,0,0));
	fillcircle(ORGX+pacman_a.x*GWID+GWID/2,ORGY+pacman_a.y*GHEI+GHEI/2,ROUND);
	if(c>0)
		t=c;
	setcolor(RGB(0,0,0));
	switch(t)
	{
	    case 'a' : case 'A' : 
		{
			for(a=0;a<PI*0.25;a=a+0.0001){
				x=(int)(ROUND*cos(a+PI)+ORGX+pacman_a.x*GWID+GWID/2);
				y=(int)(ROUND*sin(a+PI)+ORGY+pacman_a.y*GHEI+GHEI/2);
				line(ORGX+pacman_a.x*GWID+GWID/2,ORGY+pacman_a.y*GHEI+GHEI/2,x,y);
				x=(int)(ROUND*cos(PI-a)+ORGX+pacman_a.x*GWID+GWID/2);
				y=(int)(ROUND*sin(PI-a)+ORGY+pacman_a.y*GHEI+GHEI/2);
				line(ORGX+pacman_a.x*GWID+GWID/2,ORGY+pacman_a.y*GHEI+GHEI/2,x,y);
			}break;
		}
		case 's' : case 'S' : 
		{
			for(a=0;a<PI*0.25;a=a+0.0001){
				x=(int)(ROUND*cos(a+PI/2)+ORGX+pacman_a.x*GWID+GWID/2);
				y=(int)(ROUND*sin(a+PI/2)+ORGY+pacman_a.y*GHEI+GHEI/2);
				line(ORGX+pacman_a.x*GWID+GWID/2,ORGY+pacman_a.y*GHEI+GHEI/2,x,y);
				x=(int)(ROUND*cos(PI/2-a)+ORGX+pacman_a.x*GWID+GWID/2);
				y=(int)(ROUND*sin(PI/2-a)+ORGY+pacman_a.y*GHEI+GHEI/2);
				line(ORGX+pacman_a.x*GWID+GWID/2,ORGY+pacman_a.y*GHEI+GHEI/2,x,y);
			}break;
		}
		case 'd' : case 'D' : 
		{
			for(a=0;a<PI*0.25;a=a+0.0001){
				x=(int)(ROUND*cos(a)+ORGX+pacman_a.x*GWID+GWID/2);
				y=(int)(ROUND*sin(a)+ORGY+pacman_a.y*GHEI+GHEI/2);
				line(ORGX+pacman_a.x*GWID+GWID/2,ORGY+pacman_a.y*GHEI+GHEI/2,x,y);
				x=(int)(ROUND*cos(-a)+ORGX+pacman_a.x*GWID+GWID/2);
				y=(int)(ROUND*sin(-a)+ORGY+pacman_a.y*GHEI+GHEI/2);
				line(ORGX+pacman_a.x*GWID+GWID/2,ORGY+pacman_a.y*GHEI+GHEI/2,x,y);
			}break;
		}
		case 'w' : case 'W' : 
		{
			for(a=0;a<PI*0.25;a=a+0.0001){
				x=(int)(ROUND*cos(a+PI*3/2)+ORGX+pacman_a.x*GWID+GWID/2);
				y=(int)(ROUND*sin(a+PI*3/2)+ORGY+pacman_a.y*GHEI+GHEI/2);
				line(ORGX+pacman_a.x*GWID+GWID/2,ORGY+pacman_a.y*GHEI+GHEI/2,x,y);
				x=(int)(ROUND*cos(PI*3/2-a)+ORGX+pacman_a.x*GWID+GWID/2);
				y=(int)(ROUND*sin(PI*3/2-a)+ORGY+pacman_a.y*GHEI+GHEI/2);
				line(ORGX+pacman_a.x*GWID+GWID/2,ORGY+pacman_a.y*GHEI+GHEI/2,x,y);
			}break;
		}
	}
}
void runboss(void)
{
	int t1,t2;
	srand((unsigned)time(NULL));
	t1=rand()%LEVEL;
	t2=rand()%LEVEL;
	if(judgestep_boss(0,t1)){
		cleanboss_a();
		if(t1==1) boss_a.y--;
		if(t1==2) boss_a.x--;
		if(t1==3) boss_a.y++;
		if(t1==4) boss_a.x++;
	}
	if(judgestep_boss(1,t2)){
		cleanboss_b();
		if(t2==1) boss_b.y--;
		if(t2==2) boss_b.x--;
		if(t2==3) boss_b.y++;
		if(t2==4) boss_b.x++;
	}
	judgeesc();
	drawboss();
}
void judgeesc(void)
{
	if((pacman_a.x==boss_a.x)&&(pacman_a.y==boss_a.y))
		escgame=-1;
	if((pacman_a.x==boss_b.x)&&(pacman_a.y==boss_b.y))
		escgame=-1;
}
int judgestep(char c)
{
	int i;
	int x,y;
	x=pacman_a.x;
	y=pacman_a.y;
	if(c=='W'||c=='w') y--;
	if(c=='A'||c=='a') x--;
	if(c=='S'||c=='s') y++;
	if(c=='D'||c=='d') x++;
	if(x>=COL||x<0||y>=ROW||y<0)
		return 0;
	for(i=0;i<wall_number;i++)
		if((wall_member[i].x==x)&&(wall_member[i].y==y))
			return 0;
	return 1;
}
void cleanboss_a(void)
{
	int i;
	for(i=0;i<bean_numbert;i++)
		if((bean_member[i].x==boss_a.x)&&(bean_member[i].y==boss_a.y)&&bean_member[i].x>=0&&bean_member[i].y>=0)
			break;
	setcolor(RGB(0,0,0));
	setfillcolor(RGB(0,0,0));
	if(i<bean_numbert){
		setcolor(RGB(240,220,10));
		setfillcolor(RGB(240,220,10));
	}
    fillcircle(ORGX+boss_a.x*GWID+GWID/2,ORGY+boss_a.y*GHEI+GHEI/2,ROUND);

}
void cleanboss_b(void)
{
	int i;
	for(i=0;i<bean_numbert;i++)
		if((bean_member[i].x==boss_b.x)&&(bean_member[i].y==boss_b.y)&&bean_member[i].x>=0&&bean_member[i].y>=0)
			break;
	setcolor(RGB(0,0,0));
	setfillcolor(RGB(0,0,0));
	if(i<bean_numbert){
		setcolor(RGB(240,220,10));
		setfillcolor(RGB(240,220,10));
	}
	fillcircle(ORGX+boss_b.x*GWID+GWID/2,ORGY+boss_b.y*GHEI+GHEI/2,ROUND);
}
int judgestep_boss(int c,int t)
{
	int i;
	int x,y;
	if(t!=1&&t!=2&&t!=3&&t!=4)
		return 0;
	if(!c){
	    x=boss_a.x;
    	y=boss_a.y;
	    if(t==1) y--;
	    if(t==2) x--;
	    if(t==3) y++;
	    if(t==4) x++;
	    if(x>=COL||x<0||y>=ROW||y<0)
		    return 0;
		if(x==boss_b.x&&y==boss_b.y)
			return 0;
	    for(i=0;i<wall_number;i++)
		    if((wall_member[i].x==x)&&(wall_member[i].y==y))
			    return 0;
	}
	else{
		x=boss_b.x;
    	y=boss_b.y;
	    if(t==1) y--;
	    if(t==2) x--;
	    if(t==3) y++;
	    if(t==4) x++;
	    if(x>=COL||x<0||y>=ROW||y<0)
		    return 0;
		if(x==boss_a.x&&y==boss_a.y)
			return 0;
	    for(i=0;i<wall_number;i++)
		    if((wall_member[i].x==x)&&(wall_member[i].y==y))
			    return 0;
	}
	return 1;
}
void drawboss(void)
{
	setcolor(RGB(240,10,245));
    setfillcolor(RGB(240,10,245));
	fillcircle(ORGX+boss_a.x*GWID+GWID/2,ORGY+boss_a.y*GHEI+GHEI/2,ROUND);
	fillcircle(ORGX+boss_b.x*GWID+GWID/2,ORGY+boss_b.y*GHEI+GHEI/2,ROUND);
}
void overwindow(int flag)
{
	if(flag>0){
		setcolor(RGB(240,220,10));
		setfillcolor(RGB(240,220,10));
		setfont(100,50,"");
		bar3d(ORGX+90,ORGY+240,ORGX+510,ORGY+360,8,1);
		outtextxy(ORGX+125,ORGY+250,"YOU WIN");
	}
	else{
		setcolor(RGB(255,0,0));
		setfillcolor(RGB(255,0,0));
		setfont(100,50,"");
		bar3d(ORGX+90,ORGY+240,ORGX+510,ORGY+360,8,1);
		outtextxy(ORGX+100,ORGY+250,"YOU LOSE");
		
	}

}