#include "dbms.h"

DBMS::DBMS(string dbFolder, bool isInit)
{
    dbPath = dbFolder;

    if (isInit) {
        treader[TABLE_CARS].open(dbFolder + TABLE_CARS_SPATH);
        treader[TABLE_MANAGERS].open(dbFolder + TABLE_MANAGERS_SPATH);
        treader[TABLE_SALES].open(dbFolder + TABLE_SALES_SPATH);
        treader[TABLE_CLIENTS].open(dbFolder + TABLE_CLIENTS_SPATH);

        readDB();
    }
    else {

    }
}

void DBMS::readDB()
{
    string str;
    rowData currData;

    for (int i = 0; i < NUM_OF_TABLES; i++)
        tdata[i].clear();

    // TABLE_CARS reading
    currData.tableID = TABLE_CARS;

    while (!treader[TABLE_CARS].eof()) {
        getline(treader[TABLE_CARS], str); currData.ints.push_back(stoi(str)); // ID
        getline(treader[TABLE_CARS], str); currData.ints.push_back(stoi(str)); // PRICE
        getline(treader[TABLE_CARS], str); currData.strings.push_back(str);    // MODEL
        getline(treader[TABLE_CARS], str); currData.strings.push_back(str);    // YEAR
        getline(treader[TABLE_CARS], str); currData.strings.push_back(str);    // COLOR
        getline(treader[TABLE_CARS], str); currData.strings.push_back(str);    // TECH
        getline(treader[TABLE_CARS], str); currData.strings.push_back(str);    // EQUIP
        getline(treader[TABLE_CARS], str); currData.strings.push_back(str);    // COMMENT

        tdata[TABLE_CARS].push_back(currData);
        currData.strings.clear();
        currData.strings.clear();
    }

    // TABLE_MANAGERS reading
    currData.tableID = TABLE_MANAGERS;
    
    while (!treader[TABLE_MANAGERS].eof()) {
        getline(treader[TABLE_MANAGERS], str); currData.ints.push_back(stoi(str)); // ID
        getline(treader[TABLE_MANAGERS], str); currData.ints.push_back(stoi(str)); // SUMDEALS
        getline(treader[TABLE_MANAGERS], str); currData.ints.push_back(stoi(str)); // TOTALEARN
        getline(treader[TABLE_MANAGERS], str); currData.strings.push_back(str);    // NAME
        getline(treader[TABLE_MANAGERS], str); currData.strings.push_back(str);    // BIRTHDATE
        getline(treader[TABLE_MANAGERS], str); currData.strings.push_back(str);    // COMMENT

        tdata[TABLE_MANAGERS].push_back(currData);
        currData.strings.clear();
        currData.strings.clear();
    }

    // TABLE_SALES reading
    currData.tableID = TABLE_SALES;

    while (!treader[TABLE_SALES].eof()) {
        getline(treader[TABLE_SALES], str); currData.ints.push_back(stoi(str)); // ID  
        getline(treader[TABLE_SALES], str); currData.ints.push_back(stoi(str)); // CARID
        getline(treader[TABLE_SALES], str); currData.strings.push_back(str);    // DATE
        getline(treader[TABLE_SALES], str); currData.strings.push_back(str);    // COMMENT

        tdata[TABLE_SALES].push_back(currData);
        currData.strings.clear();
        currData.strings.clear();
    }

    // TABLE_CLIENTS reading
    currData.tableID = TABLE_CLIENTS;

    while (!treader[TABLE_CLIENTS].eof()) {
        getline(treader[TABLE_CLIENTS], str); currData.ints.push_back(stoi(str)); // ID
        getline(treader[TABLE_CLIENTS], str); currData.ints.push_back(stoi(str)); // PHONE
        getline(treader[TABLE_CLIENTS], str); currData.ints.push_back(stoi(str)); // STAT
        getline(treader[TABLE_CLIENTS], str); currData.ints.push_back(stoi(str)); // DISCOUNT  
        getline(treader[TABLE_CLIENTS], str); currData.strings.push_back(str);    // NAME
        getline(treader[TABLE_CLIENTS], str); currData.strings.push_back(str);    // BIRTHDATE
        getline(treader[TABLE_CLIENTS], str); currData.strings.push_back(str);    // PASSDATA
        getline(treader[TABLE_CLIENTS], str); currData.strings.push_back(str);    // COMMENT

        tdata[TABLE_CLIENTS].push_back(currData);
        currData.strings.clear();
        currData.strings.clear();
    }
}

void DBMS::saveDB()
{
    for (int tid = 0; tid < NUM_OF_TABLES; tid++)
        for (rowData currData : tdata[tid]) {
            for (int i : currData.ints)
                treader[tid] << i << '\n';
            for (string s : currData.strings)
                treader[tid] << s << '\n';
        }
}

void DBMS::ADD(rowData data)
{
    tdata[data.tableID].push_back(data);
}

rowData DBMS::GET(rowData data)
{
    
}