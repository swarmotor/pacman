#include <string.h>
#include <cstdio>
#include <ctime>
#include <stdlib.h>
#include <graphics.h>
#include <conio.h>
int SCORE=20;
char *TOP_SCORE[10];
void writescore(void);
void readscore(void);
void drawtopscore(void);
void main(void)
{
	writescore();
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