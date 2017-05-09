#ifndef HumVsHum_H
#define HumVsHum_H
#include <iostream>
#include <string>
using namespace std;

#define MAX 15

class HumVsHum{
public:
    int chessBoard[MAX][MAX];
    bool isBlack;
    bool isOver,isBlackWin,isWhiteWin;

    string maps[MAX][MAX];
public:
    HumVsHum();
    void initMap();
    void showMap();
    int checkWinner(int Cx,int Cy,int type);
    void put();
    void setPoint(int x,int y);

};
#endif // HumVsHum_H
