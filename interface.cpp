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
    std::string cmdTypes[3] = { "SELECT", "INSERT or UPDAT", "DELETE" };

    char comand;
    short cmdType = 0;
    short cmdCertain = 0;

    vector<char> cmds = { CMD_EXIT, CMD_HELP, CMD_BREAK, CMD_MENU_ITEM_1, CMD_MENU_ITEM_2, CMD_MENU_ITEM_3, CMD_MENU_ITEM_4 };
    
    string menuComand = "\nCHOOSE COMAND\n - " + std::string(1, cmds[3]) + 
                                        " Select\n - " + cmds[4] + 
                                        " Insert/Update\n - " + cmds[5] + 
                                        " Delete\n - " + cmds[0] + " Save & Exit\n - " + 
                                        cmds[1] + " Help\nInput comand: ";

    do
    {
        cmdType = _menu(menuComand, cmds);

        if (cmdType == 2)
        {
                cout << "Уже в главном меню\n";
                continue;
        }

        

        if (cmdType != 0)
        {
            //cmdTypes[cmdType] +
            std::string menuTable = "\n<";
            if ( !((cmdType > 2) && ( cmdType < 6)) )
                {
                    continue;
                }
            
            menuTable += cmdTypes[cmdType - 3];
            menuTable += "> CHOOSE TABLE\n - " + std::string(1, cmds[3]) +
                                        " Car\n - " + cmds[4] + " Manager\n - " + cmds[5] + 
                                        " Deal\n - " + cmds[6] + " Client\n - " + cmds[2] +
                                        " Break to First menu\n - " + cmds[0] + " Save & Exit\n - " + cmds[1] +
                                        " Help\nInput comand: ";
            cmdCertain = _menu(menuTable, cmds);
            if (cmdCertain == 2)
                continue;
        }
        
        switch (cmdType)
        {
        case 3:
            _select(cmdCertain);
            break;
        case 4:
            _insert(cmdCertain);
            break;
        case 5:
            _remove(cmdCertain);
            break;
        default:
            break;
        }
        
        if ((cmdType == 0) || (cmdCertain == 0))
        {
            if (std::cin.rdbuf()->in_avail() > 0)
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            cout << "Вы уверены, что хотите выйти?\nВедите 'н' для отмены или любую другую клавишу для подтверждения: ";
            comand = std::cin.get();
            cmdType = ((comand == 'н') || (comand == 'Н') || (comand == '\320')) ? -1 : 0;
        }

    } while (cmdType != 0);
}
int Interface::_menu(string text, vector<char> cmds)
{
    char input = '\0';
    do
    {
        cout << text;
        if (std::cin.rdbuf()->in_avail() > 0)
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        input = std::cin.get();
        
        auto it = std::find(cmds.begin(), cmds.end(), input);
        int index;

        if (it != std::end(cmds))
        {
            index = it - cmds.begin();
            if (index == 1)
                {
                    _help(cmds);
                    continue;
                }
            return index;
        }
        else
        {
            cout << "что-то странное ввели\n";
            continue;
        }
        
    } while (true);
    
    return -1;
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
    case 3: //model
        req.tableID = TABLE_CARS;
        break;

    case 4: //manager
        req.tableID = TABLE_MANAGERS;
        break;

    case 5: //deal
        req.tableID = TABLE_SALES;
        break;

    case 6: //client
        req.tableID = TABLE_CLIENTS;
        break;

    default:
        cout << "<! invalid argument !>\n";
        return;
    }

    if (curr != 5)
    {
        if (std::cin.rdbuf()->in_avail() > 0)
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "введите " << fields[req.tableID] << " для поиска: ";
        string str = _getString("");
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
            cout << std::setw(padding) << "ID: " << "<" << oneBlock->ints[0] << ">\n";
            cout << std::setw(padding) << "MODEL: " << "<" << oneBlock->strings[0] << ">\n";
            cout << std::setw(padding) << "YEAR: " << "<" << oneBlock->strings[1] << ">\n";
            cout << std::setw(padding) << "COLOR: " << "<" << oneBlock->strings[2] << ">\n";
            cout << std::setw(padding) << "TECH CHAR: " << "<" << oneBlock->strings[3] << ">\n";
            cout << std::setw(padding) << "EQUIPMENT: " << "<" << oneBlock->strings[4] << ">\n";
            cout << std::setw(padding) << "PRICE: " << "<" << oneBlock->strings[5] << ">\n";
            cout << std::setw(padding) << "COMMENT: " << "<" << oneBlock->strings[6] << ">\n";
            break;

        case TABLE_MANAGERS:
            cout << std::setw(padding) << "ID: " << "<" << oneBlock->ints[0] << ">\n";
            cout << std::setw(padding) << "SUM of DEALS: " << "<" << oneBlock->ints[1] << ">\n";
            cout << std::setw(padding) << "total erned money: " << "<" << oneBlock->ints[2] << ">\n";
            cout << std::setw(padding) << "Name: " << "<" << oneBlock->strings[0] << ">\n";
            cout << std::setw(padding) << "BIRTHDATE: " << "<" << oneBlock->strings[1] << ">\n";
            cout << std::setw(padding) << "COMMENT: " << "<" << oneBlock->strings[2] << ">\n";
            break;

        case TABLE_SALES:
            cout << std::setw(padding) << "ID: " << "<" << oneBlock->ints[0] << ">\n";
            cout << std::setw(padding) << "CAR ID: " << "<" << oneBlock->ints[1] << ">\n";
            cout << std::setw(padding) << "SALE DATE: " << "<" << oneBlock->strings[0] << ">\n";
            cout << std::setw(padding) << "COMMENT: " << "<" << oneBlock->strings[1] << ">\n";
            break;

        case TABLE_CLIENTS:
            cout << std::setw(padding) << "ID: " << "<"  << oneBlock->ints[0] << ">\n";
            cout << std::setw(padding) << "STATUS: " << "<"  << oneBlock->ints[1] << ">\n";
            cout << std::setw(padding) << "DISCOUNT: " << "<"  << oneBlock->ints[2] << ">\n";
            cout << std::setw(padding) << "NAME: " << "<"  << oneBlock->strings[0] << ">\n";
            cout << std::setw(padding) << "PHONE: " << "<"  << oneBlock->strings[1] << ">\n";
            cout << std::setw(padding) << "BIRTHDATE: " << "<"  << oneBlock->strings[2] << ">\n";
            cout << std::setw(padding) << "PASSPORT DATA: " << "<"  << oneBlock->strings[3] << ">\n";
            cout << std::setw(padding) << "COMMENT: " << "<"  << oneBlock->strings[4] << ">\n";
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
        case 3: //model
            req.tableID = TABLE_CARS;
            req.ints.push_back(_getNumber("set id(int): "));
            req.strings.push_back(_getString("set model: "));
            req.strings.push_back(_getString("set year: "));
            req.strings.push_back(_getString("set color: "));
            req.strings.push_back(_getString("set technician characteristics: "));
            req.strings.push_back(_getString("set equipment: "));
            req.strings.push_back(_getString("set price(int): "));
            req.strings.push_back(_getString("add your comment: "));
            break;

        case 4: //manager
            req.tableID = TABLE_MANAGERS;
            req.ints.push_back(_getNumber("set id(int): "));
            req.ints.push_back(_getNumber("set sum of deals(int): "));
            req.ints.push_back(_getNumber("set total erned money(int): "));
            req.strings.push_back(_getString("set name of manager: "));
            req.strings.push_back(_getString("set birthdate: "));
            req.strings.push_back(_getString("add your comment: "));
            break;

        case 5: //deal
            req.tableID = TABLE_SALES;
            req.ints.push_back(_getNumber("set id(int): "));
            req.ints.push_back(_getNumber("set scar id(int): "));
            req.strings.push_back(_getString("set sold date: "));
            req.strings.push_back(_getString("add your comment: "));
            break;

        case 6: //client
            req.tableID = TABLE_CLIENTS;
            req.ints.push_back(_getNumber("set id(int): "));
            req.ints.push_back(_getNumber("set status of usual(int): "));
            req.ints.push_back(_getNumber("set discount precentage(int): "));
            req.strings.push_back(_getString("set name of buyer: "));
            req.strings.push_back(_getString("set phone number (like: 89349214543): "));
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
    case 3: 
        req.tableID = TABLE_CARS;
        break;

    //manager
    case 4: 
        req.tableID = TABLE_MANAGERS;
        break;

    //deal
    case 5: 
        req.tableID = TABLE_SALES;
        break;

    //client
    case 6: 
        req.tableID = TABLE_CLIENTS;
        break;

    default:
        cout << "! invalid argument !\n";
        return;
    }

    if (curr != 5)
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

void Interface::_help(vector<char> cmds)
{
    cout << "\n_____________help_________________\n";
    cout << "2 sections of menu:\n";
    cout << "First section:\n";
    cout << "comand '" << cmds[3] << "' - SELECT\n";
    cout << "comand '" << cmds[4] << "' - INSERT or UPDATE\n";
    cout << "comand '" << cmds[5] << "' - DELETE\n-----------------------------\n";
    cout << "Second section:\n";
    cout << "comand '" << cmds[3] << "' - CAR\n";
    cout << "comand '" << cmds[4] << "' - MANAGER\n";
    cout << "comand '" << cmds[5] << "' - SALES\n";
    cout << "comand '" << cmds[6] << "' - CLIENTS\n";
    cout << "-----------------------------------\n";
    cout << "Common logic: first of all choice type of \ncomand (1 select, 2 insert/update, 3 delete)";
    cout << "after that, choice \ntable (1 cars, 2 managers, 3 sales, 4 clients)\n\n";
    cout << "to exit and save type '" << cmds[0] << "', to go to start menu type '" << cmds[2] << "', and '" << cmds[1] << "' for watch this text\n";
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

// void Interface::runDataBase()
// {
//     string cmdTypes[3] = { "SELECT", "INSERT or UPDATE", "DELETE" };

//     char comand;
//     bool flagMenu = true;
//     bool flagReset = false;
//     short cmdType = 0;
//     short cmdCertain = 0;

//     vector<char> cmds = {CMD_MENU_ITEM_1, CMD_MENU_ITEM_2, CMD_MENU_ITEM_3, CMD_MENU_ITEM_4, CMD_BREAK, CMD_HELP, CMD_EXIT,};
    
//     do
//     {
//         if (flagMenu)
//         {
//             if (std::cin.rdbuf()->in_avail() > 0)
//                 cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            
//             vector<string> menuComand = { "\nCHOOSE COMAND\n - " + cmds[0] + 
//                                         " Select\n - " + cmds[1] + 
//                                         " Insert/Update\n - " + cmds[2] + 
//                                         " Delete\n - " + cmds[6] + " Save & Exit\n - " + 
//                                         cmds[5] + " Help\nInput comand: "};

//             cmdType = _menu(menuComand, cmds);
//             comand = std::cin.get();

//             switch (comand)
//             {
//             case CMD_MENU_ITEM_1:
//                 flagMenu = false;            
//                 cmdType = 0;
//                 break;

//             case CMD_MENU_ITEM_2:
//                 flagMenu = false;       
//                 cmdType = 1;
//                 break;

//             case CMD_MENU_ITEM_3:
//                 flagMenu = false;  
//                 cmdType = 2;
//                 break;

//             case CMD_HELP:
//                 cout << "\n<? comand: HELP chosen>\n\n"; ////////////////////////////////////////////////////
//                 _help();
//                 break;

//             case CMD_EXIT:
//                 cout << "\n<Save & Exit comand>\n";      
//                 break;

//             case CMD_BREAK:
//                 cout << "you are already in default menu\n\n";
//                 break;

//             default:
//                 cout << "\nNOT a comand. Type '?' or any other comand\n\n";
//                 break;
//             }
//         }
//         else
//         {
//             if (std::cin.rdbuf()->in_avail() > 0)
//                 cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            

//             vector<string> menuTable = { "\n<" + cmdTypes[cmdType] +"CHOOSE TABLE\n - " + CMD_MENU_ITEM_1 +
//                                         " Car\n - " + CMD_MENU_ITEM_2 + " Manager\n - " + CMD_MENU_ITEM_3 + 
//                                         " Deal\n - " + CMD_MENU_ITEM_4 + " Client\n - " + CMD_BREAK +
//                                         " Break to First menu\n - " + CMD_EXIT + " Save & Exit\n - " + CMD_HELP +
//                                         " Help\nInput comand: "};

//             cmdCertain = _menu(menuTable, cmds);
//             comand = std::cin.get();

//             switch (comand)
//             {
//             case CMD_MENU_ITEM_1:
//                 flagMenu = true;
//                 //cout << "\n<1 comand: " << cmdTypes[cmdType] << " MODEL chosen>\n";
                
//                 cmdCertain = 0;
//                 flagReset = true;
//                 break;
//             case CMD_MENU_ITEM_2:
//                 flagMenu = true;
//                 //cout << "\n<2 comand: " << cmdTypes[cmdType] << " MANAGER chosen>\n";
                
//                 cmdCertain = 1;
//                 flagReset = true;
//                 break;
//             case CMD_MENU_ITEM_3:
//                 flagMenu = true;
//                 //cout << "\n<3 comand: " << cmdTypes[cmdType] << " DEAL chosen>\n";
                
                
//                 cmdCertain = 2;
//                 flagReset = true;
//                 break;
//             case CMD_MENU_ITEM_4:
//                 flagMenu = true;
//                 //cout << "\n<3 comand: " << cmdTypes[cmdType] << " CLIENT chosen>\n";
                
//                 cmdCertain = 3;
//                 flagReset = true;
//                 break;
//             case CMD_BREAK:
//                 cout << "return to base menu\n\n";
//                 flagMenu = true;
//                 flagReset = false;
//                 break;
//             case CMD_EXIT:
//                 cout << "\n<Save & Exit comand>\n\n";
//                 break;
//             case CMD_HELP:
//                 cout << "\n<? comand: HELP chosen>\n\n"; ////////////////////////////////////////////////////
//                 _help();
//                 break;
//             default:
//                 cout << "\nNOT a comand. Type '?' or any other comand\n\n";
//                 break;
//             }
//         }
//         if (flagReset)
//         {
//             flagReset = false;
//             flagMenu = true;
//             switch (cmdType)
//             {
//             case 0:
//                 _select(cmdCertain);
//                 break;
//             case 1:
//                 _insert(cmdCertain);
//                 break;
//             case 2:
//                 _remove(cmdCertain);
//                 break;
//             default:
//                 break;
//             }
//         }
//         if (comand == CMD_EXIT)
//         {
//             if (std::cin.rdbuf()->in_avail() > 0)
//                 cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

//             cout << "Are you shure? type 'n' if you want to stay in or any other key: ";
//             comand = std::cin.get();
//             comand = ((comand == 'n') || (comand == 'N')) ? 'n' : CMD_EXIT;
//         }

//     } while (comand != CMD_EXIT);
// }
