#include "dbms.h"

DBMS::DBMS(string dbFolder, bool isInit)
{
    if (isInit)
    {
    }
    else
    {
    }
}

bool DBMS::ADD(rowData data)
{
    switch (data.tableID)
    {
    case TABLE_CARS:
        break;
    }
    return false;
}

rowData DBMS::GET(rowData data)
{
    rowData d;
    return d;
}

bool DBMS::REMOVE(rowData data)
{
    return false;
}

bool DBMS::INITDB(string dbFolder)
{
    return false;
}