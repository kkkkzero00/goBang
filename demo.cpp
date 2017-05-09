#include <iostream>

#include <Windows.h>


#include "MyStack.h"
#include "ChessInBoard.h"
#include "Hash.h"
#include "Chess.h"


//#include <stack>
using namespace std;

//#define MAX 15
////#define Offset 4
//
//#define OffsetSize 11
//#define Range 2
//#define COUNT 572
//
//#define NONE 0
//#define HUM 1
//#define COM 2
//
//#define Black 1
//#define White 2
//

//1是黑棋，2是白棋，0没有棋子


int main(){
    HWND hwnd = GetForegroundWindow();//获取到当前窗口
    SetWindowTextA(hwnd,"五子棋");//设置窗口标题

    int x=500,y=500;
    MoveWindow(hwnd,0,0,x,y,true);//强制固定当前窗口的位置

	//int i,j;
    bool isBlack = true;
    //人人对战的棋盘
	int map[MAX][MAX] = {0};
	system("color 70");
    system("mode con cols=60 lines=20");

    Chess chess(15,15);

    while(true){

        if(chess.isOver)break;

        if(chess.isHum){
             chess.humPut();

            if(chess.isHumWin()){
                chess.isOver = true;
                cout<< "人类赢了!" << endl;
                break;
            }
            chess.isHum = false;

        }else{
            chess.computerAI();

            if(chess.isComWin()){
                chess.isOver = true;
                cout<< "电脑赢了!" << endl;
                //chess.showMap();
                break;
            }
            chess.isHum = true;

        }

        system("cls");
        chess.showMap();
        Sleep(1000);
    }
}

//┌┐└┘├┤┬┴┼●○


