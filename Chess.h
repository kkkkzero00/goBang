#ifndef CHESS_H
#define CHESS_H
#include <iostream>
#include <string>
#include "ChessInBoard.h"
#include "MyStack.h"
using namespace std;

#define MAX 15
#define COUNT 572

//1是黑棋，2是白棋，0没有棋子

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
	int row,col;
	bool isHum;
	bool isOver;
	int chessboard[MAX][MAX];
	string maps[MAX][MAX];
	int my_count;
	bool wins[MAX][MAX][COUNT];
	WinsCount *maxWin;
	WinsCount *minWin;
	MyStack st;
	int nearPointNum,availNum;
	int comRow,comCol;
	int level;
public:
	Chess(int x=15, int y=15,int l=2);
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

#endif // CHESS_H
