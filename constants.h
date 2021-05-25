#pragma once

#define NUM_OF_TABLES 4

#define TABLE_CARS 0
#define TABLE_MANAGERS 1
#define TABLE_SALES 2
#define TABLE_CLIENTS 3

#define TABLE_CARS_SPATH "/cars.dbt"
#define TABLE_MANAGERS_SPATH "/managers.dbt"
#define TABLE_SALES_SPATH "/sales.dbt"
#define TABLE_CLIENTS_SPATH "/clients.dbt"

#define CMD_MENU_ITEM_1 '1'
#define CMD_MENU_ITEM_2 '2'
#define CMD_MENU_ITEM_3 '3'
#define CMD_MENU_ITEM_4 '4'
#define CMD_BREAK 'b'
#define CMD_EXIT 'e'
#define CMD_HELP '?'



#include <string>
#include <vector>

struct rowData
{
    short tableID;
    std::vector<std::string> strings;
    std::vector<int> ints;
};
