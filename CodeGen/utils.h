#ifndef _UTILS_H
#define _UTILS_H

#define SIZE_FLAGS 10
#include <string>
using namespace std;

class Token{
public:
    Token() { }
    Token(string* lexem, int code)
    {
        this->lexem = lexem;
        this->val = code;
    }
    ~Token()
    {
        delete lexem;
    }
    string* lexem;
    int val;
};

class Gen {
public:
    Gen()
    {
        this->code = "";
        this->place = -1;
    }
    string code;
    int place;
};
#endif
