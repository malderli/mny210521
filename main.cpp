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
    vector<rowData *> res;

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
    cin.sync_with_stdio(false);
    /*
    Interface interface;
    struct BaseData initDb = interface.getInitData();
    DBMS db(initDb.path, initDb.isInit);
         */

    DBMS db("/media/user/DATA/projects/mny210521/bb", 1);

    /*
    interface.setDb(&db);
    interface.runDataBase();
    */
    DBMS_test(&db);
    return 0;
}