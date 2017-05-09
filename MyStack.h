#ifndef MYSTACK_H
#define MYSTACK_H
#define MAX 15
#include "ChessInBoard.h"

class MyStack{
public:
    MyStack(int size=MAX*MAX);
    ~MyStack();
    bool stackEmpty();
    bool stackFull();
    void clearStack();
    int stackLength();
    bool push(ChessInBoard elem);
    bool pop(ChessInBoard &elem);
    void stackTraverse(bool isFromTop=false);
    ChessInBoard getElement(int i);
private:
    ChessInBoard *arr;//指向栈空间
    int m_iSize;//栈容量
    int m_iTop;//栈顶，栈元素个数
};

#endif // MYSTACK_H
