#include <iostream>
#include <limits>
#include <vector>
#include <filesystem>
#include <unistd.h>
#include "constants.h"
#include "dbms.h"
#include "interface.h"
#include <string>

using std::filesystem::current_path;

int main()
{
    setlocale(LC_ALL, "Russian");
    //SetConsoleCP(1251);
    //SetConsoleOutputCP(1251);
    cin.sync_with_stdio(false);

    Interface interface;
    string path = current_path();
    //cout << "\n<<" << "current directory" << "|" << path << ">>\n";
    path += "/DataBase";

    struct BaseData initDb = interface.getInitData();
    if (initDb.isInit)
    {
        path = initDb.path;
    }

    DBMS db(path, 1);

    interface.setDb(&db);
    interface.runDataBase();
    return 0;
}