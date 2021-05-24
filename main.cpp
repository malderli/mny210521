#include <iostream>
#include "constants.h"
#include "dbms.h"
#include "interface.h"

using namespace std;

int main()
{
    Interface interface;
    struct BaseData initDb = interface.init();
    cout << "in Main\n"
         << initDb.path << "\n"
         << initDb.isInit;
    interface.runDataBase();
    return 0;
}