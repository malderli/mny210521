#pragma once
#include <iostream>
#include <fstream>
#include "constants.h"
#include <string>
#include <vector>

using namespace std;

class DBMS
{
private:
    void readDB();
    void saveDB();

    int dbTableStruct[NUM_OF_TABLES];
    short dbTableSize[NUM_OF_TABLES];

    fstream treader[NUM_OF_TABLES];
    vector<rowData*> tdata[NUM_OF_TABLES];

public:
    string dbPath;

    DBMS(string dbFolder, bool isInit);
    ~DBMS();

    vector<rowData *> GET(rowData toGet);
    vector<rowData *> GET(rowData toGet, short mask);

    void ADD(rowData data);
    bool REMOVE(rowData data);
};
