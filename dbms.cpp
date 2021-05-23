#include "dbms.h"


DBMS::DBMS(string dbFolder, bool isInit)
{
    if (isInit) {

    }
    else {

    }
}

bool DBMS::ADD(rowData data)
{
    switch (data.tableID) {
        case TABLE_CARS:
            break;
    }
}

rowData DBMS::GET(rowData data)
{

}