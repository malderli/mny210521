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
    
    cout << "Здравствуйте\nу вас уже есть база данных(д/Н): ";
    //char baseExist = std::cin.get();
    string baseExist = _getString("");
    DEBUGER("test", baseExist)

    struct BaseData outData;
    outData.isInit = ((baseExist == "Д") || (baseExist == "д")) ? true : false;
    DEBUGER("уже есть база данных: ", outData.isInit)
    
    if (std::cin.rdbuf()->in_avail() > 0)
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    cout << "Введите путь к базе данных: ";
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
    std::string cmdTypes[4] = { "ВЫБРАТЬ", "ВСТАВИТЬ или ПЕРЕЗАПИСАТЬ", "УДАЛИТЬ", "АНАЛИТИКА" };

    char comand;
    short cmdType = 0;
    short cmdCertain = 0;

    vector<std::string> cmds = { CMD_EXIT, CMD_HELP, CMD_BREAK, CMD_MENU_ITEM_1, CMD_MENU_ITEM_2, CMD_MENU_ITEM_3, CMD_MENU_ITEM_4, CMD_MENU_ITEM_5 };
    
    string menuComand = "\nВыбор команды\n - "
                        + cmds[3] + " " + cmdTypes[0] + "\n - " 
                        + cmds[4] + " " + cmdTypes[1] + "\n - "
                        + cmds[5] + " " + cmdTypes[2] + "\n - "
                        + cmds[6] + " " + cmdTypes[3] + "\n - "
                        + cmds[0] + " Сохранить & Закрыть\n - "
                        + cmds[1] + " Справка\nВведите команду: ";
    std::string menuTable;

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
            if ( !((cmdType > 2) && ( cmdType < 7)) )
                {
                    continue;
                }

            menuTable = "\n<";
            menuTable += cmdTypes[cmdType - 3];
            if (cmdType == 6)
            {
                menuTable += ">\n - " 
                            + cmds[3] + " Процент постоянных клиентов\n - "
                            + cmds[4] + " Cделка по id и информации об авто\n - "  
                            + cmds[5] + " Выдать все машины определенного цвета\n - " 
                            + cmds[6] + " Выдать список имен и телефонов всех клиентов\n - "
                            + cmds[7] + " Количество клиентов со скидкой\n - " 
                            + cmds[2] + " Вернуться в основное меню\n - " 
                            + cmds[0] + " Сохранить & Закрыть\n - " 
                            + cmds[1] + " Справка\nВведите команду: ";
            }
            else
            {
                menuTable += "> Выбор таблицы\n - "
                                + cmds[3] + " Машины\n - "
                                + cmds[4] + " Менеджеры\n - "
                                + cmds[5] + " Сделки\n - "
                                + cmds[6] + " Клиенты\n - "
                                + cmds[2] + " Вернуться в основное меню\n - "
                                + cmds[0] + " Сохранить & Закрыть\n - "
                                + cmds[1] + " Справка\nВведите команду: ";
            }
            
            cmdCertain = _menu(menuTable, cmds);

            if (cmdCertain == 2)
                {
                    cout << "Переход в основное меню...\n";
                    continue;
                }
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

        case 6:
            _analitic(cmdCertain);
            break;

        default:
            break;
        }
        
        if ((cmdType == 0) || (cmdCertain == 0))
        {
            if (std::cin.rdbuf()->in_avail() > 0)
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            cout << "Вы уверены, что хотите выйти?\nВедите 'н' для отмены или любую другую клавишу для подтверждения: ";
            std::string commit = _getString("");
            cmdType = ((commit == "н") || (commit == "Н") /*|| (comand == '\320')*/) ? -1 : 0;
        }

    } while (cmdType != 0);
}
int Interface::_menu(string text, vector<string> cmds)
{
    string input = "";
    do
    {
        cout << text;
        // if (std::cin.rdbuf()->in_avail() > 0)
        //         cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        input = _getString("");
        
        auto it = std::find(cmds.begin(), cmds.end(), input);
        int index;

        if (it != std::end(cmds))
        {
            index = it - cmds.begin();
            if (cmds[index] == CMD_HELP)
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
    fields[TABLE_CARS] = "модель машины";
    fields[TABLE_MANAGERS] = "ФИО менеджера";
    fields[TABLE_SALES] = "Введите id продажи (целое): ";
    fields[TABLE_CLIENTS] = "ФИО клиента";
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
        cout << "<! неверный аргумент !>\n";
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
    _showData(result);
}

void Interface::_analitic(short curr)
{
    string fields[7] {"Процент постоянных клиентов", "введите id сделки: ", "введите цвет машины: ", "Имена и телефоны клиентов", "\nвведите нижнюю границу (целое число): ", "\nвведите сначала нижнюю границу (целое число): ", "\nвведите верхнюю границу (целое число): "};
    struct rowData req;

    DEBUGER("ANALITIC in func", "")
    short mask = 0;

    switch (curr)
    {
    case 3: 
        req.tableID = TABLE_CLIENTS;
        mask = 0x00;
        break;

    case 4: 
        req.tableID = TABLE_SALES;
        mask = 0x08;
        break;

    case 5: 
        req.tableID = TABLE_CARS;
        mask = 0x10;
        break;

    case 6: 
        req.tableID = TABLE_CLIENTS;
        mask = 0x00;
        break;

    case 7: 
        req.tableID = TABLE_CLIENTS;
        mask = 0x00;
        break;

    default:
        cout << "<! неверный аргумент !>\n";
        return;
    }

    if ((curr != 4) && (curr != 7))
    {   //if 3
        if (curr == 3)
        {
            vector<rowData *> result = db->GET(req, mask);

            int usualCount = 0;
            
            if (result.size() == 0)
            {
                cout << "\nКлиентов Нет\n";
                return;
            }
            
            for (rowData *oneBlock : result)
            {
                if (oneBlock->ints[1] == 1)
                    usualCount++;
            }
            cout << "\nПроцент постоянных клиентов: " << 100 * ((double)usualCount / result.size()) 
                << "\nпостоянных: " << usualCount << " всего: " << result.size() << "\n"; 

            return;
        }
        //5 or 6
        else
        {
            short outMask = 0xFF;
            
            if (curr == 6)
                outMask = 0x18;
            else
            {
                req.strings.push_back(_getString(fields[curr - 3]));
            }

            vector<rowData *> result = db->GET(req, mask);
            

            _showData(result, outMask);
            return;
        }
        
    }
    else
    {
        if (curr == 4)
        {
            int data = _getNumber(fields[curr - 3]);
            req.ints.push_back(data);
            cout << "сделка + машина\n";
            vector<rowData *> result = db->GET(req);
            _showData(result);
            struct rowData reqCar;
            reqCar.tableID = TABLE_CARS;
            if (result.size() > 0)
            {
                reqCar.ints.push_back(result[0]->ints[1]);
                mask = 0x80;
                vector<rowData *> resultNext = db->GET(reqCar, mask);
                _showData(resultNext);
            }
            else
            {
                cout << "такой машины нет\n";
            }
            return;
            
        }
        else
        {
            vector<string> cmds = {CMD_MENU_ITEM_1, CMD_MENU_ITEM_2, CMD_MENU_ITEM_3};
            string text = "\n - " + cmds[0] + " Клиенты с скидкой меньше чем _\n - "
                                        + cmds[1] + " Клиенты с скидкой меньше чем _ и больше чем _\n - "  
                                        + cmds[2] + " Клиенты с скидкой больше чем _\nВвод: ";
            
            vector<rowData *> result = db->GET(req, mask);
            vector<rowData *> final;
            int option = _menu(text, cmds);

            int target = _getNumber(fields[curr + option - 3]);
            int targetNext = 0;
            switch (option)
            {
            case 0:
                final = _showPrecentage(result, target,true);
                cout << "Клиенты с скидкой меньше чем " << target << "\n";
                break;
            
            case 1:
                result = _showPrecentage(result, target,true);
                targetNext =  _getNumber("\nТеперь верхняя граница скидки (целое число): ");
                final = _showPrecentage(result, targetNext,false);
                cout << "Клиенты с скидкой меньше чем " << target << " и больше чем " << targetNext << "\n";
                break;
            
            case 2:
                final = _showPrecentage(result, target,false);
                cout << "Клиенты с скидкой больше чем " << target << "\n";
                break;
            }
            _showData(final);
            return;
        }
        
    }

    return;
}

void Interface::_showData(vector<rowData *> result, short mask)
{
    if (result.size() == 0)
    {
        cout << "\nВ таблице нет совпадений\n";
        return;
    }

    for (rowData *oneBlock : result)
    {
        int padding = 17;
        int paddNext = 15;
        cout << "_________блок данных__________\n\n";

        switch (oneBlock->tableID)
        {
        case TABLE_CARS:
            if (mask & 0x80 > 0)
                cout << std::setw(padding) << "ID: " << "<" << oneBlock->ints[0] << ">\n";
            if (mask & 0x40 > 0)
                cout << std::setw(padding) << "МОДЕЛЬ: " << "<" << oneBlock->strings[0] << ">\n";
            if (mask & 0x20 > 0)
                cout << std::setw(padding) << "ГОД: " << "<" << oneBlock->strings[1] << ">\n";
            if (mask & 0x10 > 0)
                cout << std::setw(padding) << "ЦВЕТ: " << "<" << oneBlock->strings[2] << ">\n";
            if (mask & 0x08 > 0)
                cout << std::setw(padding) << "ХАРАКТЕРИСТИКИ: " << "<" << oneBlock->strings[3] << ">\n";
            if (mask & 0x04 > 0)
                cout << std::setw(padding) << "ВАРИАНТЫ КОМПЛЕКТАЦИИ: " << "<" << oneBlock->strings[4] << ">\n";
            if (mask & 0x02 > 0)
                cout << std::setw(padding) << "ЦЕНА с ВАРИАНТАМИ КОМПЛЕКТАЦИИ: " << "<" << oneBlock->strings[5] << ">\n";
            if (mask & 0x01 > 0)
                cout << std::setw(padding) << "КОММЕНТАРИЙ: " << "<" << oneBlock->strings[6] << ">\n";
            break;

        case TABLE_MANAGERS:
            if (mask & 0x20 > 0)
                cout << std::setw(padding) << "ID: " << "<" << oneBlock->ints[0] << ">\n";
            if (mask & 0x10 > 0)
                cout << std::setw(padding) << "КОЛИЧЕСТВО СДЕЛОК: " << "<" << oneBlock->ints[1] << ">\n";
            if (mask & 0x08 > 0)
                cout << std::setw(padding) << "ОБЩИЙ ДОХОД: " << "<" << oneBlock->ints[2] << ">\n";
            if (mask & 0x04 > 0)
                cout << std::setw(padding) << "ФИО: " << "<" << oneBlock->strings[0] << ">\n";
            if (mask & 0x02 > 0)
                cout << std::setw(padding) << "ГОД РОЖДЕНИЯ: " << "<" << oneBlock->strings[1] << ">\n";
            if (mask & 0x01 > 0)
                cout << std::setw(padding) << "КОММЕНТАРИЙ: " << "<" << oneBlock->strings[2] << ">\n";
            break;

        case TABLE_SALES:
            if (mask & 0x08 > 0)
                cout << std::setw(padding) << "ID: " << "<" << oneBlock->ints[0] << ">\n";
            if (mask & 0x04 > 0)
                cout << std::setw(padding) << "ID МАШИНЫ: " << "<" << oneBlock->ints[1] << ">\n";
            if (mask & 0x02 > 0)
                cout << std::setw(padding) << "ДАТА ПРОДАЖИ: " << "<" << oneBlock->strings[0] << ">\n";
            if (mask & 0x01 > 0)
                cout << std::setw(padding) << "КОММЕНТАРИЙ: " << "<" << oneBlock->strings[1] << ">\n";
            break;

        case TABLE_CLIENTS:
            if (mask & 0x80 > 0)
                cout << std::setw(padding) << "ID: " << "<"  << oneBlock->ints[0] << ">\n";
            if (mask & 0x40 > 0)
                cout << std::setw(padding) << "СТАТУС ПОСТОЯННОСТИ: " << "<"  << oneBlock->ints[1] << ">\n";
            if (mask & 0x20 > 0)
                cout << std::setw(padding) << "ПРОЦЕНТ СКИДКИ: " << "<"  << oneBlock->ints[2] << ">\n";
            if (mask & 0x10 > 0)
                cout << std::setw(padding) << "ФИО: " << "<"  << oneBlock->strings[0] << ">\n";
            if (mask & 0x08 > 0)
                cout << std::setw(padding) << "ТЕЛЕФОН: " << "<"  << oneBlock->strings[1] << ">\n";
            if (mask & 0x04 > 0)
                cout << std::setw(padding) << "ГОД РОЖДЕНИЯ: " << "<"  << oneBlock->strings[2] << ">\n";
            if (mask & 0x02 > 0)
                cout << std::setw(padding) << "ПАСПОРТНЫЕ ДАННЫЕ: " << "<"  << oneBlock->strings[3] << ">\n";
            if (mask & 0x01 > 0)
                cout << std::setw(padding) << "КОММЕНТАРИЙ: " << "<"  << oneBlock->strings[4] << ">\n";
            break;

        default:
            cout << "ошибка в базе\n";
            break;
        }
    }
    cout << "_______________________\n";
    return;
}

 vector<rowData *> Interface::_showPrecentage(vector<rowData *> input, int target, bool less)
{
     vector<rowData *> result;
     for (rowData *oneBlock : input)
     {
         switch (less)
         {
         case true:
             if (oneBlock->ints[2] < target)
                result.push_back(oneBlock);

             break;
         
         case false:
            if (oneBlock->ints[2] > target)
                result.push_back(oneBlock);

            break;
         }
     }
     return result;
}
void Interface::_insert(short curr)
{
    DEBUGER("select INSERT !!!!!!!!!!", "")
    struct rowData req;

    switch (curr)
    {
        case 3: //model
            req.tableID = TABLE_CARS;
            req.ints.push_back(_getNumber("введите id (целое): "));
            req.strings.push_back(_getString("введите модель: "));
            req.strings.push_back(_getString("введите год: "));
            req.strings.push_back(_getString("введите цвет: "));
            req.strings.push_back(_getString("введите характеристики: "));
            req.strings.push_back(_getString("введите комплектации: "));
            req.strings.push_back(_getString("введите цену относительно комплектаций: "));
            req.strings.push_back(_getString("введите комментарий: "));
            break;

        case 4: //manager
            req.tableID = TABLE_MANAGERS;
            req.ints.push_back(_getNumber("введите id (целое): "));
            req.ints.push_back(_getNumber("введите количество сделок (целое): "));
            req.ints.push_back(_getNumber("введите общая сумма дохода от сделок (целое): "));
            req.strings.push_back(_getString("введите ФИО менеджера: "));
            req.strings.push_back(_getString("введите дату рождения: "));
            req.strings.push_back(_getString("введите комментарий: "));
            break;

        case 5: //deal
            req.tableID = TABLE_SALES;
            req.ints.push_back(_getNumber("введите id (целое): "));
            req.ints.push_back(_getNumber("введите id машины (целое): "));
            req.strings.push_back(_getString("введите дату продажи: "));
            req.strings.push_back(_getString("введите комментарий: "));
            break;

        case 6: //client
            req.tableID = TABLE_CLIENTS;
            req.ints.push_back(_getNumber("введите id (целое): "));
            req.ints.push_back(_getNumber("введите статус постоянности (целое): "));
            req.ints.push_back(_getNumber("введите процент скидки (целое): "));
            req.strings.push_back(_getString("введите ФИО покупателья: "));
            req.strings.push_back(_getString("введите номер телефона (пример: 89349214543): "));
            req.strings.push_back(_getString("введите дату рождения: "));
            req.strings.push_back(_getString("введите папортные данные: "));
            req.strings.push_back(_getString("введите комментарий: "));
            break;

        default:
            cout << "! неверный аргумент !\n";
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
    fields[TABLE_CARS] = "модель машины";
    fields[TABLE_MANAGERS] = "ФИО менеджера";
    fields[TABLE_SALES] = "Введите id продажи (целое): ";
    fields[TABLE_CLIENTS] = "ФИО клиента";

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
        cout << "! неверный аргумент !\n";
        return;
    }

    if (curr != 5)
    {
        if (std::cin.rdbuf()->in_avail() > 0)
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 

        cout << "Введите " << fields[req.tableID] << ": ";
        string str;
        cin >> str;
        req.strings.push_back(str);
    }
    else
    {
        int data = _getNumber(fields[req.tableID]);
        req.ints.push_back(data);
    }

    cout << "Успешность удаления: " << db->REMOVE(req) << "\n";
}

void Interface::_help(vector<string> cmds)
{
    cout << "\n_____________справка_________________\n";
    cout << "2 секции меню:\n";
    cout << "первая секция:\n";
    cout << "команда '" << cmds[3] << "' - ВЫБРАТЬ\n";
    cout << "команда '" << cmds[4] << "' - ВСТАВИТЬ или ПЕРЕЗАПИСАТЬ\n";
    cout << "команда '" << cmds[5] << "' - АНАЛИТИКА (следующее меню в даной секции аналогично устроено и имеет средства для выбора данных)\n";
    cout << "команда '" << cmds[5] << "' - УДАЛИТЬ\n-----------------------------\n";
    cout << "ВТОРАЯ СЕКЦИЯ - ВЫБОР ТАБЛИЦЫ:\n";
    cout << "команда '" << cmds[3] << "' - МАШИНЫ\n";
    cout << "команда '" << cmds[4] << "' - МЕНЕДЖЕРЫ\n";
    cout << "команда '" << cmds[5] << "' - ПРОДАЖИ\n";
    cout << "команда '" << cmds[6] << "' - КЛИЕНТЫ\n";
    cout << "-----------------------------------\n";
    cout << "Общая логика: выбираете команду, потом таблицу \n\n";
    cout << "для сохранения и выхода '" << cmds[0] << "', для возврата в начальное меню '" << cmds[2] << "', и '" << cmds[1] << "' для просмотра этой справки\n";
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
            cout << "\n<<!НЕ INT!>>\n\n";

        return flag;
    }
    catch (...)
    {
        cout << "слишком большое число.... надо меньше\n";
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
