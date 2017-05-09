#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <time.h>
#include <string>

#include "MyStack.h"
#include "ChessInBoard.h"
#include "Hash.h"

#include"stdlib.h"
//#include <stack>
using namespace std;

#define MAX 15
//#define Offset 4

#define OffsetSize 11
#define Range 2
#define COUNT 572

#define NONE 0
#define HUM 1
#define COM 2

#define Black 1
#define White 2

//定义分数
#define MAX_VALUE 1000000
#define MIN_VALUE -1000000
#define FOUR_W 5000
#define THREE_W 1000
#define TWO_W 200
#define ONE_W 10

//1是黑棋，2是白棋，0没有棋子

POINT point = { 0,0 };//点类型变量，用来获取鼠标位置

class PointArr{
public:
    ChessInBoard* p;
    int len;
    PointArr(ChessInBoard* cArr,int l){
        p = cArr;
        len = l;
    }
};

class WinsCount{
public:
    int max,min;
    WinsCount(){
        max = 0;
        min = 0;
    }
};

class Chess {
public:
    int Offset=4,MaxOffset;
	int row,col,trueRow,trueCol;
	bool isHum;
	bool isOver;
	int chessboard[MAX][MAX];
	int my_count;
	bool wins[MAX][MAX][572];
	WinsCount *maxWin;
	WinsCount *minWin;
	MyStack st;
	int nearPointNum,availNum;
	int comRow,comCol,humRow,humCol;
	int level;
public:
	Chess(int x, int y);
	void initWins();
	int initPlayerWins();
	void initMap();
	void showMap();
	void setPoint(int row,int col,int type);
	void rollback(int step=1);

	int evaluate();
	bool isHumWin();
	bool isComWin();
    bool isValid(int row ,int col);

    void humPut();
    void computerAI();
	PointArr* availableStep();
    int Com(int depth=1,int alpha=1000);
    int Hum(int depth,int beta);
    PointArr* getNearPoints(ChessInBoard &c);
};

Chess::Chess(int x,int y){
    row = x;
    col = y;
    isHum = true;
    isOver = false;
    maxWin = new WinsCount[COUNT];
	minWin = new WinsCount[COUNT];
	nearPointNum = 0;
	availNum = 0;
	level = 3;

	initWins();
    initMap();
    showMap();


}

void Chess::initWins(){
    int counts = 0;
    int i,j,k;

    for(i=0;i<MAX;i++){
        for(j=0;j<MAX;j++){
            for(k=0;k<COUNT;k++)
                wins[i][j][k] = false;
        }
    }

    //横向
    for(i=0;i<MAX;i++){
        for(j=0;j<MAX-4;j++){
            for(k=0;k<5;k++)
                wins[i][j+k][counts] = true;
            counts++;
        }
    }

    //纵向
    for(i=0;i<MAX;i++){
        for(j=0;j<MAX-4;j++){
            for(k=0;k<5;k++)
                wins[j+k][i][counts] = true;
            counts++;
        }
    }

    //正斜线
    for(i=0;i<MAX-4;i++){
        for(j=0;j<MAX-4;j++){
            for(k=0;k<5;k++)
                wins[i+k][j+k][counts] = true;
            counts++;
        }
    }

    //反斜线
    for(i=0;i<MAX-4;i++){
        for(j=MAX-1;j>3;j--){
            for(k=0;k<5;k++)
                wins[i+k][j-k][counts] = true;
            counts++;
        }
    }
    for(i=0;i<MAX;i++){
        for(j=0;j<MAX;j++){
            chessboard[i][j] = NONE;
        }
    }


    this->my_count = counts;

}

void Chess::initMap(){
    int i,j;

	for(i=0;i<MAX;i++)
	{
		for(j=0;j<MAX;j++)
		{
            if(i==0&&j==0)
            {
                this->maps[i][j] = "┌";
            }
            else if(i==0&&j==MAX-1)
            {
                this->maps[i][j] = "┐";
            }
            else if(i==MAX-1&&j==0)
            {
                this->maps[i][j] = "└";
            }
            else if(i==MAX-1&&j==MAX-1)
            {
                this->maps[i][j] = "┘";
            }
            else if(i==0&&j!=0)
            {
                this->maps[i][j] = "┬";
            }
            else if(i!=0&&j==0)
            {
                this->maps[i][j] = "├";
            }
            else if(i!=0&&j==MAX-1)
            {
                this->maps[i][j] = "┤";
            }

            else if(i==MAX-1&&j!=0)
            {
                this->maps[i][j] = "┴";
            }

            else{
                this->maps[i][j] = "┼";
            }
		}
	}
}

void Chess::showMap(){
	int i,j;
	for(i=0;i<MAX;i++){
		for(j=0;j<MAX;j++)
            cout<< this->maps[i][j];
		cout<<endl;
	}
}

void Chess::setPoint(int row,int col,int type){
    //cout<<row<<","<<col<<endl;
	if(row<0||col<0||row>=MAX||col>=MAX){
		cout<<"棋子没落在棋盘内，请重新输入！\n"<<endl;
		humPut();
	}
	else if(chessboard[row][col]!=NONE){
		cout<<"此位置已有棋子，请重新输入！\n"<<endl;
		humPut();
	}
	else if(chessboard[row][col] == NONE){

        chessboard[row][col] = type;
        if(type == HUM)
            maps[row][col] = "●";
        else if(type == COM)
            maps[row][col] = "○";

        ChessInBoard c(row,col,type);
        st.push(c);

        for(int i=0;i<COUNT;i++){
            if(wins[row][col][i]){
                if(type == HUM){
                    this->maxWin[i].max++;
                    this->minWin[i].max++;
                }else if(type == COM){
                    this->maxWin[i].min++;
                    this->minWin[i].min++;
                }
            }
        }

        if(st.stackLength() == this->row*this->col){
            isOver = true;
        }
    }

}

void Chess::rollback(int step){
    int i,j,row=0,col=0,type;
    ChessInBoard c;

    for(i=0;i<step;i++){
        st.pop(c);
        row = c.c_row;
        col = c.c_col;
        type = c.c_type;
        chessboard[row][col] = NONE;

        if(row==0&&col==0)
        {
            this->maps[row][col] = "┌";
        }
        else if(row==0&&col==MAX-1)
        {
            this->maps[row][col] = "┐";
        }
        else if(row==MAX-1&&col==0)
        {
            this->maps[row][col] = "└";
        }
        else if(row==MAX-1&&col==MAX-1)
        {
            this->maps[row][col] = "┘";
        }
        else if(row==0&&col!=0)
        {
            this->maps[row][col] = "┬";
        }
        else if(row!=0&&col==0)
        {
            this->maps[row][col] = "├";
        }
        else if(row!=0&&col==MAX-1)
        {
            this->maps[row][col] = "┤";
        }

        else if(row==MAX-1&&col!=0)
        {
            this->maps[row][col] = "┴";
        }

        else{
            this->maps[row][col] = "┼";
        }

        for(j=0;j<COUNT;j++){
            if(wins[row][col][j]){
                if(type == HUM){
                    this->maxWin[j].max--;
                    this->minWin[j].max--;
                }else if(type==COM){
                    this->maxWin[j].min--;
                    this->minWin[j].min--;
                }
            }
        }
    }

    isOver = false;

}

int Chess::evaluate(){
    int maxScore=0,minScore=0;
    int maxGroup[4],minGroup[4];
    int i;
    for(i=0;i<4;i++){
        maxGroup[i] = 0;
        minGroup[i] = 0;
    }

    for(i=0;i<my_count;i++){

        if(maxWin[i].max==5&&maxWin[i].min==0)
            return MAX_VALUE;
        if(minWin[i].min==5&&minWin[i].max==0)
            return MIN_VALUE;

        //如果人类在这里下了四颗棋而电脑一颗也没下
        if(maxWin[i].max==4&&maxWin[i].min==0)
            maxGroup[3]++;
        if(minWin[i].min==4&&minWin[i].max==0)
            minGroup[3]++;

        //如果人类在这里下了四颗棋而电脑一颗也没下
        if(maxWin[i].max==3&&maxWin[i].min==0)
            maxGroup[2]++;
        if(minWin[i].min==3&&minWin[i].max==0)
            minGroup[2]++;

        //如果人类在这里下了四颗棋而电脑一颗也没下
        if(maxWin[i].max==2&&maxWin[i].min==0)
            maxGroup[1]++;
        if(minWin[i].min==2&&minWin[i].max==0)
            minGroup[1]++;

        //如果人类在这里下了四颗棋而电脑一颗也没下
        if(maxWin[i].max==1&&maxWin[i].min==0)
            maxGroup[0]++;
        if(minWin[i].min==1&&minWin[i].max==0)
            minGroup[0]++;

    }

    maxScore = maxGroup[3]*FOUR_W + maxGroup[2]*THREE_W + maxGroup[1]*TWO_W +  maxGroup[0]*ONE_W;
    minScore = minGroup[3]*FOUR_W + minGroup[2]*THREE_W + minGroup[1]*TWO_W +  minGroup[0]*ONE_W;

    return maxScore - minScore;

}

bool Chess::isHumWin(){
    int score = evaluate();
    return (score==MAX_VALUE)?true:false;
}

bool Chess::isComWin(){
    int score = evaluate();
    return (score==MIN_VALUE)?true:false;
}

bool Chess::isValid(int x ,int y){
    return (x>=0 && y>=0 && x<MAX && y<MAX && chessboard[x][y] == NONE)?true:false;
}

PointArr* Chess::getNearPoints(ChessInBoard &c){
    int i,cRow,cCol,row,col;
    int p_counts=0;
    cRow = c.c_row;
    cCol = c.c_col;
    ChessInBoard* points = new ChessInBoard[Range*8];

    for(i=-Range;i<=Range;i++){
        //横向
        row = cRow;
        col = cCol+i;
        if(isValid(row,col)){
            ChessInBoard c(row,col,COM);
            points[p_counts] = c;
            p_counts++;
        }

        //纵向
        row = cRow+i;
        col = cCol;
        if(isValid(row,col)){
            ChessInBoard c(row,col,COM);
            points[p_counts] = c;
            p_counts++;
        }

        //正斜线
        row = cRow+i;
        col = cCol+i;
        if(isValid(row,col)){
            ChessInBoard c(row,col,COM);
            points[p_counts] = c;
            p_counts++;
        }

        //反斜线
        row = cRow-i;
        col = cCol+i;
        if(isValid(row,col)){
            ChessInBoard c(row,col,COM);
            points[p_counts] = c;
            p_counts++;
        }

    }
    PointArr* pArr = new PointArr(points,p_counts);

    return pArr;
}

PointArr* Chess::availableStep(){

    int len = st.stackLength();
    int centerRow,centerCol;

    centerRow = (this->row)/2;
    centerCol = (this->col)/2;
    PointArr* availableSteps;

    if(len == 0||(len == 1 && this->chessboard[centerRow][centerCol]==NONE)){
        ChessInBoard* c = new ChessInBoard(centerRow,centerCol,COM);
        availableSteps = new PointArr(c,1);

        return availableSteps;

    }else{
        if(len==1&&this->chessboard[centerRow][centerCol]==HUM){
            srand(time(NULL));

            int row = centerRow+((rand()%10>5)?-1:1);
            int col = centerCol+((rand()%10>5)?-1:1);

            ChessInBoard* c = new ChessInBoard(row,col,COM);
            availableSteps = new PointArr(c,1);

            return availableSteps;
        }else{
            int i,j,k;
            int row,col,a_count = 0;
            bool isEq;

            ChessInBoard* availArr = new ChessInBoard[MAX*MAX];
            //建一个哈希类来判断交集
            //ChessInBoard c;
            PointArr* np;
            Hash hs;

            for(i=0;i<len;i++){

                int h_len = 0;
                //获取所有可能的点
                ChessInBoard currChess = st.getElement(i);

                np = getNearPoints(currChess);
                ChessInBoard* nearPoints  = np->p;
                int npLen = np->len;

                j=0;
                while(j<npLen){
                    row = nearPoints[j].c_row;
                    col = nearPoints[j].c_col;

                    h_len = hs.len;
                    k = 0;
                    do{
                        isEq = (hs.data[k].c_row==row&&hs.data[k].c_col==col);

                        if(isEq){
                            break;
                        }else{

                            if(h_len == 0||k==hs.len-1){
                                availArr[a_count] = nearPoints[j];
                                a_count++;
                                hs.setData(nearPoints[j]);
                                h_len = hs.len;
                                break;
                            }
                            k++;
                        }

                    }while(k<h_len);

                    j++;
                }

            }

            availableSteps = new PointArr(availArr,a_count);
            //availNum = hs.len;
            return availableSteps;

        }
    }

    //return availableSteps;

}

int Chess::Com(int depth,int alpha){

    int beta = 10000000;
    //int row=0,col=0;

    if(depth == 0){
        beta = evaluate();
//        ChessInBoard c;
//        c.score = beta;
        return beta;
    }else{
        PointArr* as = availableStep();
        ChessInBoard* steps = as->p;
        int sLen = as->len;

        int i=0;
        if(st.stackLength() != 0){
            if(st.stackLength()==1){
                comRow = steps[i].c_row;
                comCol = steps[i].c_col;
                return beta;
            }
            while(i<sLen){
                setPoint(steps[i].c_row,steps[i].c_col,COM);

                if(isComWin()){

                    beta = MIN_VALUE;
                    comRow = steps[i].c_row;
                    comCol = steps[i].c_col;
                    rollback();
                    break;
                }else{
                    int res;
                    res = Hum(depth-1,beta);
                    rollback();
                    if(res<beta){
                        beta = res;
                        comRow = steps[i].c_row;
                        comCol = steps[i].c_col;
                    }

                    if(beta<=alpha&&depth != level){
                        //cout<< "COM: " << availNum << "个节点，共剪掉了 "<< availNum-1-i << " 个棋局" << endl;
                        break;
                    }
                }

                i++;
            }

            return beta;

        }
    }

}

int Chess::Hum(int depth,int beta){

    int alpha = -10000000;

    if(depth == 0){
        alpha = evaluate();

        return alpha;
    }else{
        PointArr* as = availableStep();
        ChessInBoard* steps = as->p;
        int sLen = as->len;

        if(st.stackLength() != 0){

            int i=0;

            //if(st.stackLength()==1){
             //   comRow = steps[i].c_row;
             //   comCol = steps[i].c_col;
              //  return alpha;
            //}

            while(i<sLen){
                setPoint(steps[i].c_row,steps[i].c_col,HUM);

                if(isHumWin()){
                    alpha = MAX_VALUE;
                    //humRow = steps[i].c_row;
                    //humCol = steps[i].c_col;
                    rollback();
                    break;
                }else{
                    int res;
                    res = Com(depth-1,alpha);
                    rollback();
                    if(res>alpha){
                         alpha = res;
                    }

                    if(alpha>=beta){
                        //cout<< "COM: " << availNum << "个节点，共剪掉了 "<< availNum-1-i << " 个棋局" << endl;
                        break;
                    }
                }
                i++;
            }

            return alpha;

        }
    }
}

void Chess::humPut(){
    HWND hwnd = GetForegroundWindow();
    SetWindowTextA(hwnd,"五子棋");
    //GetCursorPos(&point);
    int x=500,y=500;
    MoveWindow(hwnd,0,0,x,y,true);

    //移动窗口位置
    if(_getch()) GetCursorPos(&point);
    int i = (point.y-38+8)/16 + 1,
        j = (point.x-16+8)/16 + 1;
    //cout << "当前i" << "当前j" << j << "当前鼠标x" << point.x << "当前坐标y" << point.y << endl;

    int oi,oj;

    //cin>> i >> j;

    oi = i-1;
    oj = j-1;
    //cout<<oi<<","<<oj<<endl;
    setPoint(oi,oj,HUM);

}

void Chess::computerAI(){

    Com(level);
    setPoint(comRow,comCol,COM);

}


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


