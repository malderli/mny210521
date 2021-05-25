#include <iostream>
#include <limits>
#include <vector>
#include "constants.h"
#include "dbms.h"

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

    tdata.strings.push_back("va");
    tdata.strings.push_back("10.03.1998");
    tdata.strings.push_back("good guy");

    toget.tableID = 1;
    toget.ints.push_back(0);
    toget.strings.push_back("va");

    db->ADD(tdata);
    res = db->GET(toget, 0x24);

    db->REMOVE(toget);

    cout << res.size() << "\n";
}

int main()
{
    cin.sync_with_stdio(false);
    DBMS db("/media/malderli/Projects/Money/testfolder", 1);

    DBMS_test(&db);

    return 0;
}