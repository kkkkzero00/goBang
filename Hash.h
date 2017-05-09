#ifndef HASH_H
#define HASH_H
#include <string>
#include "ChessInBoard.h"
using namespace std;
class Hash{
public:
    int len;
    ChessInBoard* data;
public:
    Hash();
    ~Hash();
    void setData(ChessInBoard s);
};

#endif // HASH_H
