#include <iostream>
#include <string>
#include <conio.h>
#include <windows.h>
#include "HumVsHum.h"

using namespace std;

#define MAX 15

#define NONE 0
#define Black 1
#define White 2
//1是黑棋，2是白棋，0没有棋子
POINT point2 = { 0,0 };//点类型变量，用来获取鼠标位置

HumVsHum::HumVsHum(){
    isBlack = true;
    isOver = false;
    isBlackWin = false;
    isWhiteWin = false;

    initMap();
    showMap();

    int i,j;
    for(i=0;i<MAX;i++){
        for(j=0;j<MAX;j++){
            chessBoard[i][j] = NONE;
        }
    }

}

void HumVsHum::initMap(){
	int i,j;
	for(i=0;i<MAX;i++)
	{
		for(j=0;j<MAX;j++)
		{
            if(i==0&&j==0)
            {
                maps[i][j] = "┌";
            }
            else if(i==0&&j==MAX-1)
            {
                maps[i][j] = "┐";
            }
            else if(i==MAX-1&&j==0)
            {
                maps[i][j] = "└";
            }
            else if(i==MAX-1&&j==MAX-1)
            {
                maps[i][j] = "┘";
            }
            else if(i==0&&j!=0)
            {
                maps[i][j] = "┬";
            }
            else if(i!=0&&j==0)
            {
                maps[i][j] = "├";
            }
            else if(i!=0&&j==MAX-1)
            {
                maps[i][j] = "┤";
            }

            else if(i==MAX-1&&j!=0)
            {
                maps[i][j] = "┴";
            }

            else{
                maps[i][j] = "┼";
            }
        }
	}
}

void HumVsHum::showMap(){
    int i,j;
	for(i=0;i<MAX;i++)
	{
		for(j=0;j<MAX;j++)
            cout<< maps[i][j];
        cout<<endl;
    }
}

int HumVsHum::checkWinner(int Cx,int Cy,int type){
	int x=1,y=1,z=1,w=1,i;
	//判断纵向
	for(i=1;i<5;i++)
		if(Cx+i<MAX&&(chessBoard[Cx+i][Cy] == type)) y++;
		else break;

	for(i=1;i<5;i++)
		if(Cx-i>0&&chessBoard[Cx-i][Cy] == type) y++;
		else break;

	if(y>=5) return type;
	//判断横向
	for(i=1;i<5;i++)
		if(Cy+i<MAX&&chessBoard[Cx][Cy+i] == type) x++;
		else break;

	for(i=1;i<5;i++)
		if(Cy-i>0&&chessBoard[Cx][Cy-i] == type) x++;
		else break;
	//printf("%d\n",x);

	if(x>=5) return type;

	//从左上到右下
	for(i=1;i<5;i++)
		if(Cy+i<MAX&&Cx+i<MAX&&chessBoard[Cx+i][Cy+i] == type) z++;
		else break;

	for(i=1;i<5;i++)
		if(Cx-i>0&&Cy-i>0&&chessBoard[Cx-i][Cy-i] == type) z++;
		else break;

	if(z>=5) return type;

	//从右上到左下
	for(i=1;i<5;i++)
		if(Cx-i>0&&Cy+i<MAX&&chessBoard[Cx-i][Cy+i] == type) w++;
		else break;

	for(i=1;i<5;i++)
		if(Cx+i<MAX&&Cy-i>0&&chessBoard[Cx+i][Cy-i] == type) w++;
		else break;

	if(w>=5) return type;

	return 0;
}

void HumVsHum::put(){
    HWND hwnd = GetForegroundWindow();
    SetWindowTextA(hwnd,"五子棋");
    //GetCursorPos(&point);
    int x=500,y=500;
    MoveWindow(hwnd,0,0,x,y,true);

    //移动窗口位置
    if(_getch()) GetCursorPos(&point2);
    int i = (point2.y-38+8)/16 + 1,
        j = (point2.x-16+8)/16 + 1;
    //cout << "当前i" << "当前j" << j << "当前鼠标x" << point.x << "当前坐标y" << point.y << endl;

    int oi,oj;

    //cin>> i >> j;

    oi = i-1;
    oj = j-1;
    //cout<<oi<<","<<oj<<endl;
    setPoint(oi,oj);
}

void HumVsHum::setPoint(int x,int y){

	if(x<0||y<0||x>MAX-1||y>MAX-1)
	{
		cout<<"棋子没落在棋盘内，请重新输入！"<<endl;
		put();
	}
	else if(chessBoard[x][y]!=NONE)
	{
		cout<<"此位置已有棋子，请重新输入！\n"<<endl;
		put();
	}
	else
	{
		if(isBlack){
			chessBoard[x][y]=Black;
            maps[x][y] = "●";

			if(checkWinner(x,y,Black)){
                isBlackWin = true;
				isOver = true;
			}

            isBlack = false;
		}else{
			chessBoard[x][y]=White;
            maps[x][y] = "○";

			if(checkWinner(x,y,White)){
                isWhiteWin = true;
				isOver = true;
			}
			isBlack = true;
		}
	}

}


