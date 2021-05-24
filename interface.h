#pragma once
#include <iostream>
#include <vector>
//#include <conio.h>
#include "dbms.h"
#include <limits>
struct BaseData
{
    std::string path;
    bool isInit;
};

class Interface
{
private:
    DBMS *db;
    void _select(short curr);
    void _insert(short curr);
    void _remove(short curr);
    bool _is_number(const std::string &s);
    int _getNumber();
    int _getNumber(string str);
    string _getString(string str);
    void _help();

public:
    Interface(/* args */);
    ~Interface();
    struct BaseData getInitData();
    void setDb(DBMS *);
    void runDataBase();
};
