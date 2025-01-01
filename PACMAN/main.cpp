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

// 屏幕宽度
#define screenx 1280
// 屏幕高度
#define screeny 720
// 信息面板x坐标
#define INFOX 760
// 信息面板y坐标
#define INFOY 30
// 地图绘制起始x坐标
#define ORGX 60
// 地图绘制起始y坐标
#define ORGY 60
// 圆周率近似值
#define PI 3.14

// 定义结构体表示BOSS的位置
typedef struct
{
    int x;
    int y;
} BOSS;

// 定义结构体表示PACMAN（吃豆人）的位置
typedef struct
{
    int x;
    int y;
} PACMAN;

// 定义结构体表示BEAN（豆子）的位置
typedef struct
{
    int x;
    int y;
} BEAN;

// 定义结构体表示WALL（墙壁）的位置
typedef struct
{
    int x;
    int y;
} WALL;

// 定义结构体表示TIME（时间）
typedef struct
{
    int month;
    int day;
    int hour;
    int minute;
    int second;
} TIME;

// 记录游戏开始时间
DWORD dwStart;
// 两个BOSS对象
BOSS boss_a, boss_b;
// 吃豆人对象
PACMAN pacman_a;
// 豆子数组指针
BEAN *bean_member;
// 墙壁数组指针
WALL *wall_member;
// 游戏退出标志，0表示未退出，-1表示退出
int escgame = 0;
// 当前游戏回合数
int ROUND;
// 游戏难度等级
int LEVEL;
// 游戏得分
int SCORE;
// 吃豆人移动步数
int STEP;
// 地图中豆子的数量
int bean_number;
// 地图中墙壁的数量
int wall_number;
// 记录初始豆子数量
int bean_numbert;
// 地图行数
int ROW, COL;
// 单个格子宽度
int GWID, GHEI;
// 地图数据指针
char *map;
// 高分记录数组
char *TOP_SCORE[10];
// 读取地图文件名数组
char readmap_name[20];
// 创建新地图文件名数组
char createmap_name[20];

// 主菜单函数声明
void mainmenu(void);
// 开始新游戏函数声明
void New_game(void);
// 创建新地图函数声明
void Producenew_map(void);
// 显示高分榜函数声明
void High_score(void);
// 运行游戏函数声明
void rungame(void);
// 读取地图数据函数声明
void readmap(void);
// 绘制地图函数声明
void drawmap(void);
// 绘制信息面板函数声明
void draw_ibboard(void);
// 绘制游戏时间函数声明
void draw_time(void);
// 绘制游戏信息函数声明
void draw_info(void);
// 构建地图函数声明（内部使用）
void build(void);
// 构建NPC（角色和敌人）位置函数声明
void buildnpc(void);
// 将地图数据写入文件函数声明
void buildmapfile(char *str);
// 写入得分记录函数声明
void writescore(void);
// 读取得分记录函数声明
void readscore(void);
// 绘制高分榜界面函数声明
void drawtopscore(void);
// 绘制豆子函数声明
void drawbean(void);
// 清除吃豆人绘制函数声明
void cleanpacman(void);
// 绘制吃豆人函数声明
void drawpacman(char c);
// 移动敌人函数声明
void runboss(void);
// 判断游戏是否结束函数声明
void judgeesc(void);
// 判断吃豆人移动是否合法函数声明
int judgestep(char c);
// 清除BOSS a绘制函数声明
void cleanboss_a(void);
// 清除BOSS b绘制函数声明
void cleanboss_b(void);
// 判断敌人移动是否合法函数声明
int judgestep_boss(int c, int t);
// 绘制敌人函数声明
void drawboss(void);
// 显示游戏结束窗口函数声明
void overwindow(int flag);

// 主函数，程序入口
void main()
{
    // 初始化图形界面，大小为640x480
    initgraph(640, 480);
    // 设置填充颜色为黑色
    setfillcolor(RGB(0, 0, 0));
    // 用黑色填充整个图形界面
    fillrectangle(-1, -1, 640, 480);
    // 设置文字颜色为亮黄色
    setcolor(RGB(255, 255, 55));
    // 设置文字样式
    settextstyle(90, 0, "TRIPLEX_FONT");
    // 在指定位置输出游戏标题"Pacman"
    outtextxy(185, 140, "Pacman");
    // 设置文字颜色为白色
    setcolor(RGB(255, 255, 255));
    // 设置文字样式
    settextstyle(40, 0, "TRIPLEX_FONT");
    // 在指定位置输出提示信息
    outtextxy(240, 250, "      品");
    // 暂停5000毫秒，显示游戏标题和提示信息
    Sleep(5000);
    // 关闭图形界面
    closegraph();
    // 显示主菜单
    mainmenu();
}

// 显示主菜单函数
void mainmenu()
{
    char option, sign;
    // 清屏
    system("cls");
    // 输出游戏标题
    printf("                                      Pacman\n");
    // 输出菜单分隔线
    printf("--------------------------------------------------------------------------------");
    // 输出菜单选项
    printf("1. New games.\n");
    printf("2. Create new map.\n");
    printf("3. High score.\n");
    printf("4. Exit game.\n");
    do
    {
        // 提示用户输入选项
        printf("Please enter the serial number: ");
        // 清空输入缓冲区
        fflush(stdin);
        // 读取用户输入的一个字符作为选项
        scanf("%1c", &option);
        fflush(stdin);
        // 判断输入是否有效
        if (option < '1' || option > '4')
        {
            // 输入无效，提示用户是否结束程序
            printf("Error! Do you want finish the program?\n");
            printf("Please enter the Y or N : ");
            scanf("%c", &sign);
            // 如果用户输入Y或y，退出程序
            if (toupper(sign)!= 'N')
                exit(0);
        }
    } while (option < '1' || option > '4');
    fflush(stdin);
    // 根据用户选择调用相应函数
    switch (option)
    {
    case '1':
        New_game();
        break;
    case '2':
        Producenew_map();
        break;
    case '3':
        High_score();
        break;
    case '4':
        exit(0);
        break;
    }
    // 重新显示主菜单
    mainmenu();
}

// 开始新游戏函数
void New_game(void)
{
    char c;
    // 清屏
    system("cls");
    // 输出游戏标题
    printf("                                      Pacman\n");
    // 输出菜单分隔线
    printf("--------------------------------------------------------------------------------");
    // 输出地图列表提示
    printf("Map list :\n");
    // 执行系统命令"dir"，列出当前目录下的文件
    system("dir");
    // 提示用户选择地图
    printf("Which one do you want to map?\n");
    do
    {
        // 获取用户输入的地图文件名
        gets(readmap_name);
        // 如果文件名不包含".txt"后缀，添加后缀
        if (strstr(readmap_name, ".txt") == NULL)
            strcat(readmap_name, ".txt");
        break;
        char str[15];
        // 复制文件名
        strcpy(str, readmap_name);
        // 尝试打开文件
        HANDLE hFile = CreateFileA(str, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_ARCHIVE, NULL);
        // 如果文件打开失败
        if (INVALID_HANDLE_VALUE == hFile)
        {
            // 提示地图不存在，要求用户重新输入
            printf("Map does not exist!\n");
            printf("Please write again!\n");
        }
        else
            break;
    } while (1);
    system("cls");
    // 输出游戏标题
    printf("                                      Pacman\n");
    // 输出菜单分隔线
    printf("--------------------------------------------------------------------------------");
    do
    {
        // 提示用户选择游戏难度
        printf("Please enter the LEVEL\n");
        printf("1. EASY.\n");
        printf("2. COMMON.\n");
        printf("3. DIFFICULT.\n");
        // 读取用户输入的一个字符作为难度选择
        c = getch();
    } while (c < '1' || c > '3');
    // 根据用户选择设置游戏难度等级
    if (c == '1')
        LEVEL = 15;
    else if (c == '2')
        LEVEL = 10;
    else
        LEVEL = 5;
    // 开始运行游戏
    rungame();
}

// 运行游戏函数
void rungame(void)
{
    int i;
    int f = 0;
    // 用当前时间作为随机数种子
    srand((unsigned)time(NULL));
    // 初始化图形界面，大小为screenx x screeny
    initgraph(screenx, screeny);
    // 初始化游戏得分
    SCORE = 0;
    // 读取地图数据
    readmap();
    // 绘制地图
    drawmap();
    // 绘制信息面板
    draw_ibboard();
    // 绘制游戏时间
    draw_time();
    // 绘制游戏信息（得分、步数、剩余豆子数等）
    draw_info();
    // 记录初始豆子数量
    bean_numbert = bean_number;
    // 根据格子宽度和高度计算吃豆人的移动范围（取较小值减8）
    ROUND = GWID < GHEI? GWID / 2 - 8 : GHEI / 2 - 8;
    // 记录游戏开始时间
    dwStart = GetTickCount();
    // 绘制豆子
    drawbean();
    // 绘制敌人
    drawboss();
    // 绘制吃豆人（初始位置）
    drawpacman(-1);
    // 游戏主循环，直到游戏结束（escgame不为0）
    while (escgame == 0)
    {
        // 绘制游戏时间
        draw_time();
        // 获取当前时间
        DWORD dwEnd = GetTickCount();
        // 每1000毫秒（1秒）移动一次敌人
        if ((dwEnd - dwStart) % 1000 == 0)
            runboss();
        // 如果有键盘输入
        if (kbhit())
        {
            // 移动敌人
            runboss();
            char c;
            // 读取用户输入的一个字符
            c = getch();
            // 如果用户按下ESC键
            if (c == 27)
            {
                // 设置游戏退出标志为 -1
                escgame = -1;
                continue;
            }
            // 如果用户按下方向键（w、a、s、d或W、A、S、D）
            if (c == 'w' || c == 'W' || c == 'a' || c == 'A' || c == 's' || c == 'S' || c == 'd' || c == 'D')
            {
                // 判断吃豆人移动是否合法
                if (judgestep(c))
                {
                    // 清除吃豆人之前的绘制
                    cleanpacman();
                    // 根据用户输入的方向移动吃豆人
                    switch (c)
                    {
                    case 'w':
                    case 'W':
                        (pacman_a.y)--;
                        break;
                    case 'a':
                    case 'A':
                        (pacman_a.x)--;
                        break;
                    case 's':
                    case 'S':
                        (pacman_a.y)++;
                        break;
                    case 'd':
                    case 'D':
                        (pacman_a.x)++;
                        break;
                    }
                    // 绘制吃豆人在新位置
                    drawpacman(c);
                    // 增加吃豆人移动步数
                    STEP++;
                    // 判断游戏是否结束（吃豆人与敌人碰撞）
                    judgeesc();
                    // 检查吃豆人是否吃到豆子
                    for (i = 0; i < bean_numbert; i++)
                        if ((pacman_a.x == bean_member[i].x) && (pacman_a.y == bean_member[i].y))
                        {
                            // 减少剩余豆子数量
                            bean_number--;
                            // 将吃到的豆子位置标记为 -1
                            bean_member[i].x = -1;
                            bean_member[i].y = -1;
                            // 增加游戏得分
                            SCORE += 150;
                            DWORD dwEnd = GetTickCount();
                            // 如果是第一次吃到10个豆子且在规定时间内
                            if (!f && (bean_numbert - bean_number) == 10)
                            {
                                if ((dwEnd - dwStart) / 1000 <= 30)
                                    SCORE += 300;
                                if ((dwEnd - dwStart) / 1000 <= 60)
                                    SCORE += 50;
                            }
                            // 如果所有豆子都被吃完且在规定时间内
                            if (bean_number == 0)
                            {
                                if ((dwEnd - dwStart) / 1000 <= 60)
                                    SCORE += 500;
                                if ((dwEnd -dwStart) / 1000 <= 60)
                                    SCORE += 100;
                                // 设置游戏胜利标志（escgame为1）
                                escgame = 1;
                                continue;
                            }
                            // 更新游戏信息显示
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
    // 更新游戏信息显示
    draw_info();
    // 写入游戏得分记录
    writescore();
    // 显示游戏结束窗口（根据游戏结果）
    overwindow(escgame);
}

// 读取地图数据函数
void readmap(void)
{
    FILE *fp;
    int i, j, bm, wm, f = 0;
    char *p;
    // 打开地图文件
    if ((fp = fopen(readmap_name, "r")) == NULL)
    {
        // 如果文件打开失败，输出错误信息并退出程序
        printf("Map open error!\n");
        exit(-1);
    }
    // 从文件中读取地图的行数和列数
    fscanf(fp, "%d,%d", &ROW, &COL);
    // 计算单个格子的宽度
    GWID = 600 / COL;
    // 计算单个格子的高度
    GHEI = 600 / ROW;
    // 初始化豆子数量为0
    bean_number = 0;
    // 初始化墙壁数量为0
    wall_number = 0;
    // 分配地图数据内存
    p = map = (char *)malloc(sizeof(char) * ROW * COL);
    // 读取地图数据，直到文件结束
    while (!feof(fp))
    {
        char c;
        // 从文件中读取一个字符
        fscanf(fp, "%c", &c);
        // 如果字符为'0'，表示豆子，增加豆子数量
        if (c == 48)
            bean_number++;
        // 如果字符为换行符，跳过
        if (c == '\n')
            continue;
        else
            // 将字符存入地图数据数组
            *(p++) = c;
    }
    // 关闭文件
    fclose(fp);
    // 在地图数据末尾添加字符串结束符
    *p = 0;
    p = map;
    // 计算墙壁数量（地图格子总数减3减豆子数量）
    wall_number = ROW * COL - 3 - bean_number;
    // 分配豆子数组内存
    bean_member = (BEAN *)malloc(sizeof(BEAN) * bean_number);
    // 分配墙壁数组内存
    wall_member = (WALL *)malloc(sizeof(WALL) * wall_number);
    bm = 0;
    wm = 0;


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

	//time num

	
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
//
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
		for(i=0;i<bean_number;i++)
        {
			place[i]=rand()%(ROW*COL)//check
			if((place[i]+1)%COL==0||place[i]%COL==0||place[i]<COL-1||place[i]>(ROW-1)*COL)
				i--;//check
			for(j=0;j<i;j++)
				if(place[i]==place[j])
					i--;//check
		}
        
		for(i=0;i<bean_number;i++)
        {
			int f=0;

			for(j=0;j<bean_number&&f!=2;i++)
            {
				if(i==j)//is_neighbor
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
		map[place[i]]='0';//write
}

void buildmapfile(char *str)
{
	int i,j;
	FILE *fp;


	if((fp=fopen(str,"w"))==NULL)
    {
		printf("File open error !\n");
		exit(-1);
	}

	fprintf(fp,"%d,%d",ROW,COL);
	fprintf(fp,"\n");//in

	for(i=0;i<ROW;i++)
    {
		for(j=0;j<COL;j++)
			fprintf(fp,"%c",map[i*COL+j]);
		fprintf(fp,"\n");
	}
	fclose(fp);//end in
}


void High_score(void)
{
	readscore();
}//

void writescore(void)
{
	FILE *fp;
	time_t t;

    t=time(&t);

	char str[50]={0};
	char strt[5]={0};

	sprintf(str,"%s",ctime(&t));
	
    str[24]=0;	

	sprintf(strt,"%04d",SCORE);//change to str
	
    strcat(str,"  ||  SCORE:");
	strcat(str,strt);

	strcpy(strt,"TIME:");
	strcat(strt,str);
	//write
	if((fp=fopen("SCORE.txt","a+"))==NULL)
    {
		printf("File open error !\n");
		exit(-1);
	}

	fseek(fp,0,2);
	if(feof(fp))
    {
		printf("sadgasdg");
	}
	fprintf(fp,"%s\n",strt);
	fclose(fp);//end
}


void readscore(void)
{
	FILE *fp;
	int i,j,n=0;
	int score[100];
	char *str[100];

	if((fp=fopen("SCORE.txt","r"))==NULL)
    {
		printf("File open error !\n");
		exit(-1);
	}

	for(i=0;i<100;i++)//recorde history
		str[i]=(char*)malloc(50);

	while(!feof(fp)&&n<100)
	{
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
    //bubble sort
	for(i=0;i<n;i++)
        for(j=i+1;j<n;j++)
            if(score[j]>score[i])
			{
				int t;
				char strt[50];
                t=score[i];
				score[i]=score[j];
				score[j]=t;

				strcpy(strt,str[i]);
				
                strcpy(str[i],str[j]);
				
                strcpy(str[j],strt);
            }
//TOP_SCORE
	for(i=0;i<10&&i<n;i++)
	{
		TOP_SCORE[i]=(char *)malloc(50);
		strcpy(TOP_SCORE[i],str[i]);
	}

    //init
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


void drawbean(void)
{
	int i;

	for(i=0;i<bean_number;i++)
	{
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
}//end 


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
			for(a=0;a<PI*0.25;a=a+0.0001)
			{
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
    // 判断吃豆人与BOSS a是否在同一位置
    if ((pacman_a.x == boss_a.x) && (pacman_a.y == boss_a.y))
        // 如果是，设置游戏退出标志为 -1，表示游戏失败
        escgame = -1;
    // 判断吃豆人与BOSS b是否在同一位置
    if ((pacman_a.x == boss_b.x) && (pacman_a.y == boss_b.y))
        // 如果是，设置游戏退出标志为 -1，表示游戏失败
        escgame = -1;
}

int judgestep(char c)
{
    int i;
    int x, y;
    // 获取吃豆人当前的x坐标
    x = pacman_a.x;
    // 获取吃豆人当前的y坐标
    y = pacman_a.y;
    // 根据输入的方向字符，更新吃豆人的坐标
    if (c == 'W' || c == 'w')

        y--;

    if (c == 'A' || c == 'a')

        x--;

    if (c == 'S' || c == 's')

        y++;
    if (c == 'D' || c == 'd')

        x++;

    // 判断吃豆人新位置是否超出地图边界

    if (x >= COL || x < 0 || y >= ROW || y < 0)
        return 0;
    // 遍历墙壁数组，判断吃豆人新位置是否与墙壁重合
    for (i = 0; i < wall_number; i++)
        if ((wall_member[i].x == x) && (wall_member[i].y == y))
            return 0;
    // 如果吃豆人移动合法，返回1
    return 1;
}


void cleanboss_a(void)
{
    int i;
    // 遍历豆子数组，找到与BOSS a位置相同的豆子（如果有）
    for (i = 0; i < bean_numbert; i++)

        if ((bean_member[i].x == boss_a.x) && (bean_member[i].y == boss_a.y) && bean_member[i].x >= 0 && bean_member[i].y >= 0)
            break;
    // 设置绘制颜色为黑色
    setcolor(RGB(0, 0, 0));
    // 设置填充颜色为黑色
    setfillcolor(RGB(0, 0, 0));
    // 如果找到与BOSS a位置相同的豆子，设置绘制颜色和填充颜色为豆子颜色（黄色）
    if (i < bean_numbert)
    {
        setcolor(RGB(240, 220, 10));
        setfillcolor(RGB(240, 220, 10));
    }
    // 用指定颜色填充BOSS a所在的圆形区域，清除之前的绘制
    fillcircle(ORGX + boss_a.x * GWID + GWID / 2, ORGY + boss_a.y * GHEI + GHEI / 2, ROUND);
}

void cleanboss_b(void)
{
    int i;
    // 遍历豆子数组，找到与BOSS b位置相同的豆子（如果有）
    for (i = 0; i < bean_numbert; i++)

        if ((bean_member[i].x == boss_b.x) && (bean_member[i].y == boss_b.y) && bean_member[i].x >= 0 && bean_member[i].y >= 0)
            break;
    // 设置绘制颜色为黑色
    setcolor(RGB(0, 0, 0));
    // 设置填充颜色为黑色
    setfillcolor(RGB(0, 0, 0));
    // 如果找到与BOSS b位置相同的豆子，设置绘制颜色和填充颜色为豆子颜色（黄色）
    if (i < bean_numbert)
    {
        setcolor(RGB(240, 220, 10));
        setfillcolor(RGB(240, 220, 10));
    }
    // 用指定颜色填充BOSS b所在的圆形区域，清除之前的绘制
    fillcircle(ORGX + boss_b.x * GWID + GWID / 2, ORGY + boss_b.y * GHEI + GHEI / 2, ROUND);
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
    // 如果游戏胜利（flag > 0）
    if (flag > 0)
    {
        // 设置绘制颜色为绿色（用于填充胜利窗口）
        setcolor(RGB(240, 220, 10));
        // 设置填充颜色为绿色
        setfillcolor(RGB(240, 220, 10));
        // 设置字体大小和样式
        setfont(100, 50, "");
        // 绘制3D矩形作为胜利窗口背景
        bar3d(ORGX + 90, ORGY + 240, ORX + 510, ORGY + 360, 8, 1);
        // 在胜利窗口中输出"YOU WIN"
        outtextxy(ORGX + 125, ORGY + 250, "YOU WIN");
    }

	
    // 如果游戏失败（flag <= 0）
    else
    {
        // 设置绘制颜色为红色（用于填充失败窗口）
        setcolor(RGB(255, 0, 0));
        // 设置填充颜色为红色
        setfillcolor(RGB(255, 0, 0));
        // 设置字体大小和样式
        setfont(100, 50, "");
        // 绘制3D矩形作为失败窗口背景
        bar3d(ORGX + 90, ORGY + 240, ORX + 510, ORGY + 360, 8, 1);
        // 在失败窗口中输出"YOU LOSE"
        outtextxy(ORGX + 100, ORGY + 250, "YOU LOSE");
    }
}