#include "dbms.h"

DBMS::DBMS(string dbFolder, bool isInit)
{
    // DB configuration info setup
    dbTableStruct[TABLE_CARS] = 0x80;
    dbTableStruct[TABLE_MANAGERS] = 0x38;
    dbTableStruct[TABLE_SALES] = 0x0C;
    dbTableStruct[TABLE_CLIENTS] = 0xE0;

    dbTableSize[TABLE_CARS] = 8;
    dbTableSize[TABLE_MANAGERS] = 6;
    dbTableSize[TABLE_SALES] = 4;
    dbTableSize[TABLE_CLIENTS] = 8;

    // Readers opening
    dbPath = dbFolder;

    if (isInit)
        readDB();

    treader[TABLE_CARS].open(dbPath + TABLE_CARS_SPATH, ios::out);
    treader[TABLE_MANAGERS].open(dbPath + TABLE_MANAGERS_SPATH, ios::out);
    treader[TABLE_SALES].open(dbPath + TABLE_SALES_SPATH, ios::out);
    treader[TABLE_CLIENTS].open(dbPath + TABLE_CLIENTS_SPATH, ios::out);
}

DBMS::~DBMS()
{
    saveDB();
    
    for (int tid = 0; tid < NUM_OF_TABLES; tid++)
        treader[tid].close();
}

void DBMS::readDB()
{
    string str;
    rowData *currData;

    treader[TABLE_CARS].open(dbPath + TABLE_CARS_SPATH, ios::in);
    treader[TABLE_MANAGERS].open(dbPath + TABLE_MANAGERS_SPATH, ios::in);
    treader[TABLE_SALES].open(dbPath + TABLE_SALES_SPATH, ios::in);
    treader[TABLE_CLIENTS].open(dbPath + TABLE_CLIENTS_SPATH, ios::in);

    for (int tid = 0; tid < NUM_OF_TABLES; tid++) {
        tdata[tid].clear();

        while (!(treader[tid].peek() == EOF)) {
            currData = new rowData();
            currData->tableID = tid;

            for (int col = dbTableSize[tid] - 1; col >= 0; col--) {
                getline(treader[tid], str);

                if ((dbTableStruct[tid] >> col) & 0x01) {
                    if (str.empty())
                        currData->ints.push_back(0);
                    else
                        currData->ints.push_back(stoi(str));
                }
                else
                    currData->strings.push_back(str);
            }

            tdata[tid].push_back(currData);
        }
    }

    for (int tid = 0; tid < NUM_OF_TABLES; tid++)
        treader[tid].close();
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
    rowData *tmp = new rowData;
    tmp->tableID = data.tableID;
    tmp->ints = data.ints;
    tmp->strings = data.strings;

    tdata[data.tableID].push_back(tmp);
}

vector<rowData *> DBMS::GET(rowData toGet)
{
    vector<rowData *> res;

    if (toGet.tableID != TABLE_SALES) {
        for (rowData *currData : tdata[toGet.tableID])
            if ((currData->strings.size() > 0) && (currData->strings[0] == toGet.strings[0]))
                res.push_back(currData);
    }
    else
        for (rowData *currData : tdata[toGet.tableID])
            if ((currData->ints.size() > 0) && (currData->ints[0] == toGet.ints[0]))
                res.push_back(currData);

    return res;
}

bool DBMS::REMOVE(rowData data)
{
    int startSize;

    startSize = tdata[data.tableID].size();

    if (data.tableID != TABLE_SALES) {
        for (int jnx = 0; jnx < tdata[data.tableID].size(); jnx++)
            if (tdata[data.tableID][jnx]->strings[0] == data.strings[0])
                tdata[data.tableID].erase(tdata[data.tableID].begin() + jnx);
    }
    else
        for (int jnx = 0; jnx < tdata[data.tableID].size(); jnx++)
            if (tdata[data.tableID][jnx]->ints[0] == data.ints[0])
                tdata[data.tableID].erase(tdata[data.tableID].begin() + jnx);

    return startSize == tdata[data.tableID].size();
}