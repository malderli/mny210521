#include <iostream>
#include <limits>
#include <vector>
#include "constants.h"
#include "dbms.h"
#include "interface.h"

using namespace std;

void DBMS_test(DBMS *db)
{
    rowData tdata;
    rowData toget;
    vector<rowData*> res;

    tdata.tableID = 1;
    tdata.ints.push_back(0);
    tdata.ints.push_back(4);
    tdata.ints.push_back(1000020);

    tdata.strings.push_back("ta");
    tdata.strings.push_back("10.03.2000");
    tdata.strings.push_back("nice guy");

    toget.tableID = 1;
    toget.strings.push_back("vasya");

    db->ADD(tdata);
    res = db->GET(toget);

    cout << res.size() << "\n";
}

int main()
{
    /*
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    Interface interface;
    struct BaseData initDb = interface.getInitData();
    cout << "in Main\n"
         << initDb.path << "\n"
         << initDb.isInit;

    DBMS db(initDb.path, initDb.isInit);
         */

    DBMS db("/media/malderli/Projects/Money/testfolder", 1);

    /*
    interface.setDb(&db);
    interface.runDataBase();
    */
    DBMS_test(&db);
    return 0;
}