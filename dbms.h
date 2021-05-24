#pragma once
#include <iostream>
#include <fstream>
#include "constants.h"
#include <string>

using namespace std;

class DBMS
{
private:
    bool INITDB(string dbFolder);

    fstream tables[4];

public:
    DBMS(string dbFolder, bool isInit = true);

    rowData GET(rowData data);
    bool ADD(rowData data);
    bool REMOVE(rowData data);
};
