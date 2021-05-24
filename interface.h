#pragma once
#include <iostream>
#include <vector>
//#include <conio.h>
#include "dbms.h"
struct BaseData
{
    std::string path;
    bool isInit;
};

class Interface
{
private:
    DBMS *db;
    void select(short curr);
    void insert(short curr);
    void remove(short curr);
    bool is_number(const std::string &s);

    void help();

public:
    Interface(/* args */);
    ~Interface();
    struct BaseData init();
    void setDb(DBMS *);
    void runDataBase();
};
