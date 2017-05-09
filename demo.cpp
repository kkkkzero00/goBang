#include <iostream>
#include <Windows.h>
#include "Chess.h"
#include "HumVsHum.h"

using namespace std;
//POINT point = { 0,0 };//点类型变量，用来获取鼠标位置
void setSystemWindow(){
    HWND hwnd = GetForegroundWindow();//获取到当前窗口
    SetWindowTextA(hwnd,"五子棋");//设置窗口标题

    int x=500,y=500;
    MoveWindow(hwnd,0,0,x,y,true);//强制固定当前窗口的位置

    system("color 70");
    system("mode con cols=60 lines=20");
}

int main(){

    setSystemWindow();
    //人人对战的棋盘
	int map[MAX][MAX] = {0};

    int type = 0;
    int level = 0;
    int board = 0;
    cout<< "请选择对战方式 1：人人对战 2：人机对战" << endl;
    cin>>type;

    if(type==1){
        system("cls");
        HumVsHum hum;

        while(true){
            if(hum.isOver){
                if(hum.isBlackWin){
                    cout<<"黑方胜利！"<<endl;
                }else if(hum.isWhiteWin){
                    cout<<"白方胜利！"<<endl;
                }else{
                    cout<<"平局"<<endl;
                }
                break;
            }

            hum.put();
            system("cls");
            hum.showMap();
            Sleep(1000);
        }
    }else if(type==2){

        cout<< "请选择棋盘大小，如15，即15*15" << endl;
        cin>>board;
        cout<< "请选择难度 1:新手级、2：普通级、3：困难级、4：修罗级" << endl;
        cin>>level;
        system("cls");

        Chess chess(board,board,level);

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

    return 0;
}




