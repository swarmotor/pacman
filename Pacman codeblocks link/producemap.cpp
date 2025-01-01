#include "head.h"
char *map;
int sizescreen;
char createmap_name[10];
void build(void);
void buildnpc(void);
void buildmapfile(char *str);
void Producenew_map(void)
{
	int i,j;
    system("cls");
	srand((unsigned)time(NULL));
    printf("                                      Pacman\n");
    printf("--------------------------------------------------------------------------------");
    printf("please write a name for the new map :\n");
    while(1)
    {
        gets(createmap_name);
        HANDLE hFile=CreateFileA(readmap_name,GENERIC_READ,NULL,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_ARCHIVE,NULL);
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

	for(i=0;i<ROW;i++){
		for(j=0;j<COL;j++)
			printf("%c",map[i*COL+j]);
		printf("\n");
	}

	buildmapfile("createmap_name");
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