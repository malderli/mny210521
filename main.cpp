#include <iostream>
#include "constants.h"
#include "dbms.h"
#include "interface.h"

using namespace std;

int main()
{
    Interface interface;
    struct BaseData initDb = interface.getInitData();
    cout << "in Main\n"
         << initDb.path << "\n"
         << initDb.isInit;
    DBMS db(initDb.path, initDb.isInit);
    interface.setDb(&db);
    interface.runDataBase();
    return 0;
}