#include "interface.h"
#define DEBUGER(str, data) cout << str << "|" << data;

Interface::Interface(/* args */)
{
    db = nullptr;
}

Interface::~Interface()
{
}

struct BaseData Interface::init()
{
    cout << "Hello, let's start\nDo you already have data base(y/N): ";
    char baseExist = std::cin.get();
    DEBUGER("test", baseExist)
    cout << '\n';

    struct BaseData outData;
    outData.isInit = ((baseExist == 'Y') || (baseExist == 'y')) ? true : false;
    cout << "Type data base directory: ";
    cin >> outData.path;
    return outData;
}

void Interface::setDb(DBMS *base)
{
    db = base;
    return;
}

void Interface::runDataBase()
{
    /*
    1 select model name
    2 select manager name
    3 select deal id
    4 select client name

    5 - 8 insert

    9-12 delete


    */
    char *cmdTypes[3] = {"SELECT", "INSERT or UPDATE", "DELETE"};
    char comand; // = "end";
    bool flagMenu = true;
    bool flagReset = false;
    short cmdType = 0;
    short cmdCertain = 0;
    do
    {
        cout << "Input comand (or type '?'): ";
        cin >> comand;
        if (flagMenu)
        {
            switch (comand)
            {
            case '1':
                flagMenu = false;
                cout << "\n 1 comand: SELECT\n";
                cmdType = 0;
                break;
            case '2':
                flagMenu = false;
                cout << "\n 2 comand: INSERT or UPDATE\n";
                cmdType = 1;
                break;
            case '3':
                flagMenu = false;
                cout << "\n 3 comand: DELETE\n";
                cmdType = 2;
                break;
            case '?':
                cout << "\n ? comand: help\n"; ////////////////////////////////////////////////////
                help();
                break;
            case 'e':
                cout << "exit comand\n";
                break;
            default:
                cout << "\nNOT a comand. Type '?' or any other comand\n";
                break;
            }
        }
        else
        {
            switch (comand)
            {
            case '1':
                flagMenu = true;
                cout << "\n 1 comand: " << cmdTypes[cmdType] << " MODEL\n";
                cmdCertain = 0;
                flagReset = true;
                break;
            case '2':
                flagMenu = true;
                cout << "\n 2 comand: " << cmdTypes[cmdType] << " MANAGER\n";
                cmdCertain = 1;
                flagReset = true;
                break;
            case '3':
                flagMenu = true;
                cout << "\n 3 comand: " << cmdTypes[cmdType] << " DEAL\n";
                cmdCertain = 2;
                flagReset = true;
                break;
            case '4':
                flagMenu = true;
                cout << "\n 3 comand: " << cmdTypes[cmdType] << " CLIENT\n";
                cmdCertain = 3;
                flagReset = true;
                break;
            case 's':
                cout << "return to base menu\n";
                flagMenu = true;
                flagReset = false;
                break;
            case 'e':
                cout << "exit comand\n";
                break;
            case '?':
                cout << "\n ? comand: help\n"; ////////////////////////////////////////////////////
                help();
                break;
            default:
                cout << "\nNOT a comand. Type '?' or any other comand\n";
                break;
            }
        }
        if (flagReset)
        {
            flagReset = false;
            flagMenu = true;
            switch (cmdType)
            {
            case 0:
                select(cmdCertain);
                break;
            case 1:
                insert(cmdCertain);
                break;
            case 2:
                remove(cmdCertain);
                break;
            default:
                break;
            }
        }
        if (comand == 'e')
        {
            cout << "Are you shure? type 'n' if you want to stay in or any other key: ";
            cin >> comand;
            comand = comand == 'n' ? 'n' : 'e';
        }

    } while (comand != 'e');
}

void Interface::select(short curr)
{
    struct rowData req;

    cout << "select COMAND !!!!!!!!!!";
    switch (curr)
    {
    case 0: //model
        req.tableID = TABLE_CARS;
        break;
    case 1: //manager
        req.tableID = TABLE_MANAGERS;
        break;
    case 2: //deal
        req.tableID = TABLE_SALES;
        break;
    case 3: //client
        req.tableID = TABLE_CLIENTS;
        break;
    default:
        cout << "! invalid argument !\n";
        return;
    }
    if (curr != 2)
    {
        cout << "input data for search: ";
        string str;
        cin >> str;
        req.strings.push_back(str);
    }
    else
    {
        string data;
        do
        {
            cout << "input data for search (integer): ";
            cin >> data;
        } while (!is_number(data));
        int intDat = stoi(data);
        req.ints.push_back(intDat);
    }
    //db->GET(req);
}
void Interface::insert(short curr)
{
    cout << "select INSERT !!!!!!!!!!";
}
void Interface::remove(short curr)
{
    cout << "select REMOVE !!!!!!!!!!";
}
void Interface::help()
{
    cout << "HELP HELP HELP";
}

bool Interface::is_number(const std::string &s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it))
        ++it;
    return !s.empty() && it == s.end();
}