#include "interface.h"
#define DEBUGER(str, data) cout << str << "|" << data;

Interface::Interface(/* args */)
{
    db = nullptr;
}

Interface::~Interface()
{
}

struct BaseData Interface::getInitData()
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
    string cmdTypes[3] = {"SELECT", "INSERT or UPDATE", "DELETE"};
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
                _help();
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
                _help();
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
                _select(cmdCertain);
                break;
            case 1:
                _insert(cmdCertain);
                break;
            case 2:
                _remove(cmdCertain);
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

void Interface::_select(short curr)
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
        int data = _getNumber();
        req.ints.push_back(data);
    }

    vector<rowData *> result = db->GET(req);

    for (rowData *oneBlock : result)
    {
        cout << "_________block data__________\n";
        switch (oneBlock->tableID)
        {
        case TABLE_CARS:
            cout << "ID:\t\t" << oneBlock->ints[0] << "||\n";
            cout << "PRICE:\t\t" << oneBlock->ints[1] << "||\n";
            cout << "MODEL:\t\t" << oneBlock->strings[0] << "||\n";
            cout << "YEAR:\t\t" << oneBlock->strings[1] << "||\n";
            cout << "COLOR:\t\t" << oneBlock->strings[2] << "||\n";
            cout << "TECH CHAR:\t\t" << oneBlock->strings[3] << "||\n";
            cout << "EQUIPMENT:\t\t" << oneBlock->strings[4] << "||\n";
            cout << "COMMENT:\t\t" << oneBlock->strings[5] << "||\n";
            break;
        case TABLE_MANAGERS:
            cout << "ID:\t\t" << oneBlock->ints[0] << "||\n";
            cout << "SUM of DEALS:\t\t" << oneBlock->ints[1] << "||\n";
            cout << "total erned money:\t\t" << oneBlock->ints[2] << "$ ||\n";
            cout << "Name:\t\t" << oneBlock->strings[0] << "||\n";
            cout << "BIRTHDATE:\t\t" << oneBlock->strings[1] << "||\n";
            cout << "COMMENT:\t\t" << oneBlock->strings[2] << "||\n";
            break;
        case TABLE_SALES:
            cout << "ID:\t\t" << oneBlock->ints[0] << "||\n";
            cout << "CAR ID:\t\t" << oneBlock->ints[1] << "||\n";
            cout << "SALE DATE:\t\t" << oneBlock->strings[0] << "||\n";
            cout << "COMMENT:\t\t" << oneBlock->strings[1] << "||\n";
            break;
        case TABLE_CLIENTS:
            cout << "ID:\t\t" << oneBlock->ints[0] << "||\n";
            cout << "PHONE:\t\t" << oneBlock->ints[1] << "||\n";
            cout << "STATUS:\t\t" << oneBlock->ints[2] << "||\n";
            cout << "DISCOUNT %:\t\t" << oneBlock->ints[3] << "||\n";
            cout << "Name:\t\t" << oneBlock->strings[0] << "||\n";
            cout << "BIRTHDATE:\t\t" << oneBlock->strings[1] << "||\n";
            cout << "PASSPORT DATA:\t\t" << oneBlock->strings[2] << "||\n";
            cout << "COMMENT:\t\t" << oneBlock->strings[3] << "||\n";
            break;
        default:
            cout << "error in BASE\n";
            break;
        }
    }
    cout << "_______________________\n";
}
void Interface::_insert(short curr)
{
    cout << "select INSERT !!!!!!!!!!";
    struct rowData req;

    cout << "select COMAND !!!!!!!!!!";
    switch (curr)
    {
    case 0: //model
        req.tableID = TABLE_CARS;
        req.ints.push_back(_getNumber("set id(int): "));
        req.ints.push_back(_getNumber("set price(int): "));
        req.strings.push_back(_getString("set model: "));
        req.strings.push_back(_getString("set year: "));
        req.strings.push_back(_getString("set color: "));
        req.strings.push_back(_getString("set technician characteristics: "));
        req.strings.push_back(_getString("set equipment: "));
        req.strings.push_back(_getString("add your comment: "));
        break;
    case 1: //manager
        req.tableID = TABLE_MANAGERS;
        req.ints.push_back(_getNumber("set id(int): "));
        req.ints.push_back(_getNumber("set sum of deals(int): "));
        req.ints.push_back(_getNumber("set total erned money(int): "));
        req.strings.push_back(_getString("set name of manager: "));
        req.strings.push_back(_getString("set birthdate: "));
        req.strings.push_back(_getString("add your comment: "));
        break;
    case 2: //deal
        req.tableID = TABLE_SALES;
        req.ints.push_back(_getNumber("set id(int): "));
        req.ints.push_back(_getNumber("set scar id(int): "));
        req.strings.push_back(_getString("set sold date: "));
        req.strings.push_back(_getString("add your comment: "));
        break;
    case 3: //client
        req.tableID = TABLE_CLIENTS;
        req.tableID = TABLE_MANAGERS;
        req.ints.push_back(_getNumber("set id(int): "));
        req.ints.push_back(_getNumber("set phone number(int) (like: 89349214543): "));
        req.ints.push_back(_getNumber("set status of usual(int): "));
        req.ints.push_back(_getNumber("set discount precentage(int): "));
        req.strings.push_back(_getString("set name of buyer: "));
        req.strings.push_back(_getString("set birthdate: "));
        req.strings.push_back(_getString("set pasport data: "));
        req.strings.push_back(_getString("add your comment: "));
        break;
    default:
        cout << "! invalid argument !\n";
        return;
    }
    db->REMOVE(req);
    db->ADD(req);
    ///////////////////////////////////////////////////////////////////
}
void Interface::_remove(short curr)
{
    cout << "select REMOVE !!!!!!!!!!";
    rowData req;

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
    bool result = db->REMOVE(req);
    cout << "result: " << result << "\n";
}
void Interface::_help()
{
    cout << "HELP HELP HELP";
}

bool Interface::_is_number(const std::string &s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it))
        ++it;
    return !s.empty() && it == s.end();
}

int Interface::_getNumber()
{
    string data;
    do
    {
        cout << "input data for search (integer): ";
        cin >> data;
    } while (!_is_number(data));

    return stoi(data);
}

int Interface::_getNumber(string str)
{
    string data;
    do
    {
        cout << str;
        cin >> data;
    } while (!_is_number(data));

    return stoi(data);
}
string Interface::_getString(string str)
{
    string data;
    cout << str;
    cin >> data;
    return data;
}