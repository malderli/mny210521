#include <iostream>
#include <limits>
#include "constants.h"
#include "dbms.h"
#include "interface.h"

using namespace std;

int main()
{
    cin.sync_with_stdio(false);
    // cin.clear();
    // cin.ignore(numeric_limits<streamsize>::max(), '\n');
    Interface interface;
    struct BaseData initDb = interface.getInitData();
    DBMS db(initDb.path, initDb.isInit);
    interface.setDb(&db);
    interface.runDataBase();
    return 0;
}