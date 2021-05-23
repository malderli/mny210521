#include <iostream>
#include <fstream>
#include "constants.h"
#include <string>
#include <vector>

using namespace std;

class DBMS
{
private:
    bool initDB(string dbFolder);
    void readDB();
    void saveDB();

    fstream treader[NUM_OF_TABLES];
    vector<rowData> tdata[NUM_OF_TABLES];

public:
    string dbPath;

    DBMS(string dbFolder, bool isInit);

    rowData GET(rowData data);
    void ADD(rowData data);
    bool REMOVE(rowData data);
};

