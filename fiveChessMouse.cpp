# include<stdio.h>
# include<string.h>
# include<stdlib.h>
#include <windows.h>
#define MAX 15
//防止检索溢出
#define offset 4

#define MaxOffset MAX+offset
#define OffsetSize MAX-offset

#define true (1==1)

#define Black 1
#define White 2
//1是黑棋，2是白棋，0没有棋子

//typedef WinsBoard *WinsPoint;

void showMap(int map[MaxOffset][MaxOffset])
{
	int i,j;
	for(i=offset;i<MaxOffset;i++)
	{
		for(j=offset;j<MaxOffset;j++)
		{
			if(map[i][j]==0)
			{
				if(i==offset&&j==offset)
				{
					printf("┌");
				}
				else if(i==offset&&j==MaxOffset-1)
				{
					printf("┐");
				}
				else if(i==MaxOffset-1&&j==offset)
				{
					printf("└");
				}
				else if(i==MaxOffset-1&&j==MaxOffset-1)
				{
					printf("┘");
				}
				else if(i==offset&&j!=offset)
				{
					printf("┬");
				}
				else if(i!=offset&&j==offset)
				{
					printf("├");
				}
				else if(i!=offset&&j==MaxOffset-1)
				{
					printf("┤");
				}

				else if(i==MaxOffset-1&&j!=offset)
				{
					printf("┴");
				}

				else{
					printf("┼");
				}
			}
			else if(map[i][j]==Black)
			{
				printf("●");
			}
			else if(map[i][j]==White)
			{
				printf("○");
			}
		}
		printf("\n");
	}
}

int checkWinner(int Cx,int Cy,int map[MaxOffset][MaxOffset],int now){
	int x=1,y=1,z=1,w=1,i;
	//判断纵向
	for(i=1;i<5;i++)
		if(Cx+i<MaxOffset&&map[Cx+i][Cy] == now) y++;
		else break;

	for(i=1;i<5;i++)
		if(Cx-i>offset&&map[Cx-i][Cy] == now) y++;
		else break;

	if(y>=5) return now;
	//判断横向
	for(i=1;i<5;i++)
		if(Cy+i<MaxOffset&&map[Cx][Cy+i] == now) x++;
		else break;

	for(i=1;i<5;i++)
		if(Cy-i>offset&&map[Cx][Cy-i] == now) x++;
		else break;
	//printf("%d\n",x);

	if(x>=5) return now;

	//从左上到右下
	for(i=1;i<5;i++)
		if(Cy+i<MaxOffset&&Cx+i<MaxOffset&&map[Cx+i][Cy+i] == now) z++;
		else break;

	for(i=1;i<5;i++)
		if(Cx-i>offset&&Cy-i>offset&&map[Cx-i][Cy-i] == now) z++;
		else break;

	if(z>=5) return now;

	//从右上到左下
	for(i=1;i<5;i++)
		if(Cx-i>offset&&Cy+i<MaxOffset&&map[Cx-i][Cy+i] == now) w++;
		else break;

	for(i=1;i<5;i++)
		if(Cx+i<MaxOffset&&Cy-i>offset&&map[Cx+i][Cy-i] == now) w++;
		else break;

	if(w>=5) return now;

	return 0;
}

int setPoint(int map[MaxOffset][MaxOffset],int* isBlack){
	int i,j;
	int oi,oj;

	scanf("%d%d",&i,&j);

	oi = i+offset;
	oj = j+offset;

	if(oi<offset||oj<offset||oi>MaxOffset-1||oj>MaxOffset-1)
	{
		printf("棋子没落在棋盘内，请重新输入！\n");
		setPoint(map,isBlack);
	}
	else if(map[oi][oj]!=0)
	{
		printf("此位置已有棋子，请重新输入！\n");
		setPoint(map,isBlack);
	}
	else
	{
		if(*isBlack==1){
			map[oi][oj]=Black;

			if(checkWinner(oi,oj,map,Black)){
				printf("黑方胜利！\n");
				return 0;
			}

			*isBlack = 0;
		}else{
			map[oi][oj]=White;

			if(checkWinner(oi,oj,map,White)){
				printf("白方胜利！\n");
				return 0;
			}
			*isBlack = 1;
		}
	}


	return 1;

}

int main(){

	int isBlack = 1;
	int i,j;
	system("color 70");

    //人人对战的棋盘
	int maps[MaxOffset][MaxOffset] = {0};

//	map[8][8] = 1;
    system("mode con cols=60 lines=20");
    //showMap(map);
    showMap(maps);
    while(true){
        if(!setPoint(maps,&isBlack)){
            break;
        }

        system("cls");
        showMap(maps);
        printf("%d\n",isBlack);
        Sleep(1000);
    }



}


//┌┐└┘├┤┬┴┼●○
