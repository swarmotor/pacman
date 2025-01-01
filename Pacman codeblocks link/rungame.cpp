#include "head.h"
void New_game(void)
{
    system("cls");
    printf("                                      Pacman\n");
    printf("--------------------------------------------------------------------------------");
    printf("Map list :\n");
    system("dir");
    printf("Which one do you want to map ?\n");
    do
    {
        gets(readmap_name);
        HANDLE hFile=CreateFileA(readmap_name,GENERIC_READ,NULL,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_ARCHIVE,NULL);
        if(INVALID_HANDLE_VALUE==hFile){
            printf("Map does not exist !\n");
            printf("Please write again !\n");
        }
		else
			break;
    }while(1);
    rungame();
}
void rungame(void)
{

}
void readmap(void)
{
	FILE *fp;
	int i,j,bm,wm,f=0;
	char *map,*p;
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
	initgraph(screenx,screeny);
	setcolor(RGB(255,255,255));
	rectangle(ORGX,ORGY,ORGX+600,ORGY+600);
	for(i=0;i<wall_number;i++){
		setcolor(RGB(255,255,255));
		setfillcolor(RGB(131,97,50));
		if(wall_member[i].x==0)
			bar3d(ORGX+wall_member[i].y*GWID,ORGY+wall_member[i].x*GHEI,ORGX+wall_member[i].y*GWID+GWID,ORGY+wall_member[i].x*GHEI+GHEI,5,1);
		else 
			if(wall_member[i].y==(ROW-1))
			     bar3d(ORGX+wall_member[i].y*GWID,ORGY+wall_member[i].x*GHEI,ORGX+wall_member[i].y*GWID+GWID,ORGY+wall_member[i].x*GHEI+GHEI,5,0);
		    else
				fillrectangle(ORGX+wall_member[i].y*GWID,ORGY+wall_member[i].x*GHEI,ORGX+wall_member[i].y*GWID+GWID,ORGY+wall_member[i].x*GHEI+GHEI);
	}
}
void drawinformation(void)
{


}