#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
//#include <conio.h>
#include "dbms.h"
#include <limits>
#include <algorithm>
#include <string>

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
    int _getNumber(string str);
    int _menu(string, vector<char>);
    string _getString(string str);
    void _help(vector<char>);

public:
    Interface();
    struct BaseData getInitData();
    void setDb(DBMS *);
    void runDataBase();
};
