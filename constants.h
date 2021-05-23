#pragma once


#define TABLE_CARS      0
#define TABLE_MANAGERS  1
#define TABLE_SALES     2
#define TABLE_CLIENTS   3

#define TABLE_CARS_SPATH "/cars.dbt"
#define TABLE_MANAGERS_SPATH "/managers.dbt"
#define TABLE_SALES_SPATH "/sales.dbt"
#define TABLE_CLIENTS_SPATH "/clients.dbt"

#include <string>
#include <vector>

struct rowData
{
    short tableID;
    std::vector<std::string> strings;
    std::vector<int> ints;
};