#include <iostream>
#include "MyStack.h"
#include "ChessInBoard.h"
using namespace std;

MyStack::MyStack(int size){
    m_iSize = size;
    arr = new ChessInBoard[size];
    m_iTop = 0;
}

MyStack::~MyStack(){
    delete []arr;
    arr = NULL;
}

bool MyStack::stackEmpty(){
    return (0 == m_iTop)?true:false;
}

bool MyStack::stackFull(){
    return (m_iTop == m_iSize)?true:false;
}

void MyStack::clearStack(){
    m_iTop = 0;
}

int MyStack::stackLength(){
    return m_iTop;
}

bool MyStack::push(ChessInBoard elem){
    if(stackFull())return false;

    arr[m_iTop] = elem;
    m_iTop++;
    return true;
}

//char MyStack::pop(){
//    if(stackEmpty()){
//        throw "error";
//    }
//
//    m_iTop--;
//    return m_pBuffer[m_iTop];
//}

bool MyStack::pop(ChessInBoard &elem){
    if(stackEmpty()) return false;

    m_iTop--;
    elem = arr[m_iTop];
    return true;
}

void MyStack::stackTraverse(bool isFromTop){
    if(isFromTop){
        for(int i = m_iTop-1;i>=0;i--){
//            cout << m_pBuffer[i] << " ";
//            arr[i].printCoordinate();
        }

    }else{
        for(int i=0;i<m_iTop;i++){
//            cout << m_pBuffer[i] << " ";
//            arr[i].printCoordinate();
        }
    }
    cout << endl;
}

ChessInBoard MyStack::getElement(int i){
    return arr[i];
}
