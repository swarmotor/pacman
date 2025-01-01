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

int SCORE;
int STEP;
int bean_number;
int wall_number;
int ROW,COL;
int GWID,GHEI;
char readmap_name[10];

void mainmenu(void);
void New_game(void);
void High_score(void);
void Producenew_map(void);

void draw_ibboard(void);
void draw_time(void);
void draw_info(void);

void rungame(void);
void readmap(void);
void drawmap(void); //不包括人物
void drawinformation(void);
