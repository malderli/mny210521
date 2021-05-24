#include "interface.h"
//#define DEBUGER(str, data) cout << "\n<<" << str << "|" << data << ">>\n";
#define DEBUGER(str, data)

Interface::Interface()
{
    db = nullptr;
}

struct BaseData Interface::getInitData()
{
    if (std::cin.rdbuf()->in_avail() > 0)
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    cout << "Hello, let's start\nDo you already have data base(y/N): ";
    char baseExist = std::cin.get();
    DEBUGER("test", baseExist)

    struct BaseData outData;
    outData.isInit = ((baseExist == 'Y') || (baseExist == 'y')) ? true : false;
    DEBUGER("is init: ", outData.isInit)
    
    if (std::cin.rdbuf()->in_avail() > 0)
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
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
    string cmdTypes[3] = { "SELECT", "INSERT or UPDATE", "DELETE" };
    char comand;
    bool flagMenu = true;
    bool flagReset = false;
    short cmdType = 0;
    short cmdCertain = 0;
    
    do
    {
        if (flagMenu)
        {
            if (std::cin.rdbuf()->in_avail() > 0)
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "First menu\n - 1 Select\n - 2 Insert/Update\n - 3 Delete\nInput comand (or type '?'): ";
            cin >> comand;
            switch (comand)
            {
            case '1':
                flagMenu = false;
                cout << "\n<1 comand: SELECT chosen>\n";
                cmdType = 0;
                break;

            case '2':
                flagMenu = false;
                cout << "\n<2 comand: INSERT or UPDATE chosen>\n";
                cmdType = 1;
                break;

            case '3':
                flagMenu = false;
                cout << "\n<3 comand: DELETE chosen>\n";
                cmdType = 2;
                break;

            case '?':
                cout << "\n<? comand: HELP chosen>\n"; ////////////////////////////////////////////////////
                _help();
                break;

            case 'e':
                cout << "\n<exit comand>\n";
                break;

            case 's':
                cout << "you are already in default menu\n";
                break;

            default:
                cout << "\nNOT a comand. Type '?' or any other comand\n";
                break;
            }
        }
        else
        {
            if (std::cin.rdbuf()->in_avail() > 0)
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                
            cout << "Second menu\nFirst choise: " << cmdType + 1
                 << " <" << cmdTypes[cmdType] << '>'
                 << "\n - 1 Model\n - 2 Manager\n - 3 Deal\n - 3 Client\nInput comand (or type '?'): ";
            cin >> comand;

            switch (comand)
            {
            case '1':
                flagMenu = true;
                cout << "\n<1 comand: " << cmdTypes[cmdType] << " MODEL chosen>\n";
                cmdCertain = 0;
                flagReset = true;
                break;
            case '2':
                flagMenu = true;
                cout << "\n<2 comand: " << cmdTypes[cmdType] << " MANAGER chosen>\n";
                cmdCertain = 1;
                flagReset = true;
                break;
            case '3':
                flagMenu = true;
                cout << "\n<3 comand: " << cmdTypes[cmdType] << " DEAL chosen>\n";
                cmdCertain = 2;
                flagReset = true;
                break;
            case '4':
                flagMenu = true;
                cout << "\n<3 comand: " << cmdTypes[cmdType] << " CLIENT chosen>\n";
                cmdCertain = 3;
                flagReset = true;
                break;
            case 's':
                cout << "return to base menu\n";
                flagMenu = true;
                flagReset = false;
                break;
            case 'e':
                cout << "\n<exit comand>\n";
                break;
            case '?':
                cout << "\n<? comand: HELP chosen>\n"; ////////////////////////////////////////////////////
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
            if (std::cin.rdbuf()->in_avail() > 0)
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Are you shure? type 'n' if you want to stay in or any other key: ";
            comand = std::cin.get();
            comand = ((comand == 'n') || (comand == 'N')) ? 'n' : 'e';
        }

    } while (comand != 'e');
}

void Interface::_select(short curr)
{
    string fields[4];
    fields[TABLE_CARS] = "car model";
    fields[TABLE_MANAGERS] = "name of manager";
    fields[TABLE_SALES] = "input id of sale (integer): ";
    fields[TABLE_CLIENTS] = "name of client";
    struct rowData req;

    DEBUGER("SELECT COMAND in func", "")

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
        cout << "<! invalid argument !>\n";
        return;
    }

    if (curr != 2)
    {
        if (std::cin.rdbuf()->in_avail() > 0)
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "input " << fields[req.tableID] << ": ";
        string str;
        cin >> str;
        req.strings.push_back(str);
    }
    else
    {
        int data = _getNumber(fields[req.tableID]);
        req.ints.push_back(data);
    }

    vector<rowData *> result = db->GET(req);
    if (result.size() == 0)
    {
        cout << "\nNo such data in base\n";
    }

    for (rowData *oneBlock : result)
    {
        int padding = 17;
        int paddNext = 15;
        cout << "_________block data__________\n\n";

        switch (oneBlock->tableID)
        {
        case TABLE_CARS:
            cout << std::setw(padding) << "ID: " << "<" << std::setw(paddNext)<< oneBlock->ints[0] << ">||\n";
            cout << std::setw(padding) << "PRICE: " << "<" << std::setw(paddNext)<< oneBlock->ints[1] << ">||\n";
            cout << std::setw(padding) << "MODEL: " << "<" << std::setw(paddNext)<< oneBlock->strings[0] << ">||\n";
            cout << std::setw(padding) << "YEAR: " << "<" << std::setw(paddNext)<< oneBlock->strings[1] << ">||\n";
            cout << std::setw(padding) << "COLOR: " << "<" << std::setw(paddNext)<< oneBlock->strings[2] << ">||\n";
            cout << std::setw(padding) << "TECH CHAR: " << "<" << std::setw(paddNext)<< oneBlock->strings[3] << ">||\n";
            cout << std::setw(padding) << "EQUIPMENT: " << "<" << std::setw(paddNext)<< oneBlock->strings[4] << ">||\n";
            cout << std::setw(padding) << "COMMENT: " << "<" << std::setw(paddNext)<< oneBlock->strings[5] << ">||\n";
            break;

        case TABLE_MANAGERS:
            cout << std::setw(padding) << "ID: " << "<" << std::setw(paddNext)<< oneBlock->ints[0] << ">||\n";
            cout << std::setw(padding) << "SUM of DEALS: " << "<" << std::setw(paddNext)<< oneBlock->ints[1] << ">||\n";
            cout << std::setw(padding) << "total erned money: " << "<" << std::setw(paddNext)<< oneBlock->ints[2] << "$>||\n";
            cout << std::setw(padding) << "Name: " << "<" << std::setw(paddNext)<< oneBlock->strings[0] << ">||\n";
            cout << std::setw(padding) << "BIRTHDATE: " << "<" << std::setw(paddNext)<< oneBlock->strings[1] << ">||\n";
            cout << std::setw(padding) << "COMMENT: " << "<" << std::setw(paddNext)<< oneBlock->strings[2] << ">||\n";
            break;

        case TABLE_SALES:
            cout << std::setw(padding) << "ID: " << "<" << std::setw(paddNext)<< oneBlock->ints[0] << ">||\n";
            cout << std::setw(padding) << "CAR ID: " << "<" << std::setw(paddNext)<< oneBlock->ints[1] << ">||\n";
            cout << std::setw(padding) << "SALE DATE: " << "<" << std::setw(paddNext)<< oneBlock->strings[0] << ">||\n";
            cout << std::setw(padding) << "COMMENT: " << "<" << std::setw(paddNext)<< oneBlock->strings[1] << ">||\n";
            break;

        case TABLE_CLIENTS:
            cout << std::setw(padding) << "ID: " << "<" << std::setw(paddNext) << oneBlock->ints[0] << ">||\n";
            cout << std::setw(padding) << "PHONE: " << "<" << std::setw(paddNext) << oneBlock->ints[1] << ">||\n";
            cout << std::setw(padding) << "STATUS: " << "<" << std::setw(paddNext) << oneBlock->ints[2] << ">||\n";
            cout << std::setw(padding) << "DISCOUNT %: " << "<" << std::setw(paddNext) << oneBlock->ints[3] << ">||\n";
            cout << std::setw(padding) << "Name: " << "<" << std::setw(paddNext) << oneBlock->strings[0] << ">||\n";
            cout << std::setw(padding) << "BIRTHDATE: " << "<" << std::setw(paddNext) << oneBlock->strings[1] << ">||\n";
            cout << std::setw(padding) << "PASSPORT DATA: " << "<" << std::setw(paddNext) << oneBlock->strings[2] << ">||\n";
            cout << std::setw(padding) << "COMMENT: " << "<" << std::setw(paddNext) << oneBlock->strings[3] << ">||\n";
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
    DEBUGER("select INSERT !!!!!!!!!!", "")
    struct rowData req;

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
    DEBUGER("select REMOVE !!!!!!!!!!", "")

    string fields[4];
    fields[TABLE_CARS] = "car model";
    fields[TABLE_MANAGERS] = "name of manager";
    fields[TABLE_SALES] = "input id of sale (integer): ";
    fields[TABLE_CLIENTS] = "name of client";

    rowData req;

    switch (curr)
    {
    //model
    case 0: 
        req.tableID = TABLE_CARS;
        break;

    //manager
    case 1: 
        req.tableID = TABLE_MANAGERS;
        break;

    //deal
    case 2: 
        req.tableID = TABLE_SALES;
        break;

    //client
    case 3: 
        req.tableID = TABLE_CLIENTS;
        break;

    default:
        cout << "! invalid argument !\n";
        return;
    }

    if (curr != 2)
    {
        if (std::cin.rdbuf()->in_avail() > 0)
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 

        cout << "input " << fields[req.tableID] << ": ";
        string str;
        cin >> str;
        req.strings.push_back(str);
    }
    else
    {
        int data = _getNumber(fields[req.tableID]);
        req.ints.push_back(data);
    }

    cout << "result: " << db->REMOVE(req) << "\n";
}

void Interface::_help()
{
    cout << "\n_____________help_________________\n";
    cout << "2 sections of menu:\n";
    cout << "First section:\n";
    cout << "comand '1' - SELECT\n";
    cout << "comand '2' - INSERT or UPDATE\n";
    cout << "comand '3' - DELETE\n-----------------------------\n";
    cout << "Second section:\n";
    cout << "comand '1' - CAR\n";
    cout << "comand '2' - MANAGER\n";
    cout << "comand '3' - SALES\n";
    cout << "comand '4' - CLIENTS\n";
    cout << "-----------------------------------\n";
    cout << "Common logic: first of all choice type of \ncomand (1 select, 2 insert/update, 3 delete)";
    cout << "after that, choice \ntable (1 cars, 2 managers, 3 sales, 4 clients)\n\n";
    cout << "to exit type 'e', to go to start menu type 's', and '?' for watch this text\n";
    cout << "___________________________________\n\n";
}

bool Interface::_is_number(const std::string &s)
{
    std::string::const_iterator it = s.begin();

    while (it != s.end() && std::isdigit(*it))
        ++it;

    try
    {
        bool flag = !s.empty() && it == s.end();

        if (flag)
            stoi(s);
        else
            cout << "\n<<!NOT INT NUMBER!>>\n\n";

        return flag;
    }
    catch (...)
    {
        cout << "to much... need smaler number\n";
        return false;
    }
}

int Interface::_getNumber()
{
    string data;

    do
    {
        if (std::cin.rdbuf()->in_avail() > 0)
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
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
        if (std::cin.rdbuf()->in_avail() > 0)
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        cout << str;
        cin >> data;
    } while (!_is_number(data));

    return stoi(data);
}

string Interface::_getString(string str)
{
    std::string data;
    
    if (std::cin.rdbuf()->in_avail() > 0)
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    cout << str;
    DEBUGER("clean buffer ", std::numeric_limits<std::streamsize>::max())
    std::getline(std::cin, data);
    DEBUGER(data, "this is your data")
    
    return data;
}