#include "dbms.h"

DBMS::DBMS(string dbFolder, bool isInit)
{
    // DB configuration info setup
    dbTableStruct[TABLE_CARS] = 0xC0;
    dbTableStruct[TABLE_MANAGERS] = 0x38;
    dbTableStruct[TABLE_SALES] = 0x0C;
    dbTableStruct[TABLE_CLIENTS] = 0xF0;

    dbTableSize[TABLE_CARS] = 8;
    dbTableSize[TABLE_MANAGERS] = 6;
    dbTableSize[TABLE_SALES] = 4;
    dbTableSize[TABLE_CLIENTS] = 8;

    // Readers opening
    dbPath = dbFolder;

    treader[TABLE_CARS].open(dbFolder + TABLE_CARS_SPATH);
    treader[TABLE_MANAGERS].open(dbFolder + TABLE_MANAGERS_SPATH);
    treader[TABLE_SALES].open(dbFolder + TABLE_SALES_SPATH);
    treader[TABLE_CLIENTS].open(dbFolder + TABLE_CLIENTS_SPATH);

    readDB();
}

void DBMS::readDB()
{
    string str;
    rowData *currData;

    for (int i = 0; i < NUM_OF_TABLES; i++)
        tdata[i].clear();

    for (int tid = 0; tid < NUM_OF_TABLES; tid++)
        while (!treader[tid].eof()) {
            currData = new rowData();
            currData->tableID = tid;

            for (int col = 0; col < dbTableSize[tid]; col++) {
                getline(treader[tid], str);

                if ((dbTableStruct[tid] >> col) & 0x01)
                    currData->ints.push_back(stoi(str));
                else
                    currData->strings.push_back(str);
            }
        }
}

void DBMS::saveDB()
{
    for (int tid = 0; tid < NUM_OF_TABLES; tid++)
        for (rowData *currData : tdata[tid]) {
            for (int i : currData->ints)
                treader[tid] << i << '\n';
            for (string s : currData->strings)
                treader[tid] << s << '\n';
        }
}

void DBMS::ADD(rowData data)
{
    tdata[data.tableID].push_back(&data);
}

vector<rowData*> DBMS::GET(rowData toGet)
{
    vector<rowData*> res;

    if (toGet.tableID != TABLE_SALES)
        for (rowData *currData : tdata[toGet.tableID])
                if (currData->strings[0] == toGet.strings[0])
                    res.push_back(currData);
    else
        for (rowData *currData : tdata[toGet.tableID])
                if (currData->ints[0] == toGet.ints[0])
                    res.push_back(currData);

    return res;
}