#include <iostream>
#include "Hash.h"
#include <string>
using namespace std;

Hash::Hash(){
    len = 0;
    data = new ChessInBoard[255];
}
Hash::~Hash(){
    delete[]data;
    data = NULL;
}

void Hash::setData(ChessInBoard s){
    data[len] = s;
    len++;
}
