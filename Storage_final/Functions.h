#pragma once
#include <fstream>
#include <string>
#include "Section.h"
#include "Log.h"
#include "Messages.h"

const unsigned short int LINES_DIFFERENCE = 9;                                      ///��������� ����� ���� � ���� ��������� �� �������, ����� �� ������� � ���� �� ����� � ����������.
const unsigned short int MAX_SECTIONS = 12;                                         ///���������� ���� ������ �� ��� �� ��� �����, ���� �� ������ ��������� � 2 * 12 = 24 ������.
const unsigned short int SCOPE_OF_PRODUCT = 2;                                      ///���� ������� � ������� ��� ���� �� �� ������� �� �������� ��� �����,
                                                                                    ///����� ������������ ���������� �� ��������: SCOPE_OF_PRODUCT * MAX_CAPACITY * MAX_COMPARTMENTS = 320.
const unsigned short int RANGE_OF_DAYS = 5;                                         ///��� � ���������� 5 ����, ����� �� ������� �� �������� ������, ��� ������ �� ���� ���������.
const string LOGS_PATH = "Logs.txt";                                                ///�����, � ����� �� �� �������� �������� �� ��������� � �����������.
const string ANSWERS[2] = { "No", "Yes" };                                          ///����������� �������� ��� ������� ������.
const string UNITS_OF_MEASUREMENT[2] = { "kg", "l" };                               ///����������� ����� �������.


/**
    �������, ����� �� ������� �������� ��� (��� ��� ��������� ������� � �����, � ������������ �� �����)
    ����� ���� ����� � ������������ �� �����.
*/
string getNameFile(string filePath)
{
    int index = filePath.find_last_of('\\');
    string name;
    if (index != -1)
    {
        name = filePath.substr(index + 1);
    }
    else
    {
        name = filePath;
    }

    return name;
}

/**
    ������� ������ ������� �� ���������, ��������� ��� ������� ��������� �������� ��� ��� ������, ������ �� ������ � �������.
*/
void printErrorMessage(string filePath) {
    cerr << "\n";
    cerr << "There was a problem opening file with name: " << getNameFile(filePath) << endl;
    cerr << "\n";
}

void printSuccessSaveMessage(string filePath) {
    cout << "===========================================================" << endl;
    cout << "All changes are saved successfully in the file " << getNameFile(filePath) << "!" << endl;
    cout << "===========================================================" << endl;
}

void printSuccessReadMessage(string filePath) {
    cout << "===========================================================" << endl;
    cout << "Successfully opened " << getNameFile(filePath) << "!" << endl;
    cout << "===========================================================" << endl;
}

void printSuccessCreateMessage(string filePath) {
    cout << "===========================================================" << endl;
    cout << "Successfully created " << getNameFile(filePath) << "!" << endl;
    cout << "===========================================================" << endl;
}

/**
    �������, ����� �� ������� �������� ��� (��� ��� ��������� ������� � �����, � ������������ �� �����)
    ��������� ���� ���������� ����� ����.
*/
bool fileExists(string filePath)
{
    bool fileExists = false;
    ifstream inputFileStream;
    inputFileStream.open(filePath, ios::in);

    if (inputFileStream.good())
    {
        fileExists = true;
        inputFileStream.close();
    }

    return fileExists;
}

/**
    �������, ����� �� ������� �������� ��� (��� ��� ��������� ������� � �����, � ������������ �� �����)
    ��������� ���� ��� � �������.
*/
bool checkFilePath(string filePath)
{
    bool validFilePath = true;
    if (filePath.find(">") != -1 || filePath.find("<") != -1
        || filePath.find("/") != -1 || filePath.find("|") != -1)
    {
        cout << INVALID_PATH << endl;
        validFilePath = false;
    }

    return validFilePath;
}

/**
    �������� ���� ������ � �������. (��������� ������, ���� �� ����� � ��������, ���� �� �������� � ��������)
*/
bool checkDate(unsigned short int day, unsigned short int month, unsigned short int year)
{
    if (day < 1 || day > 31)
    {
        cout << INVALID_DAY << endl;
        return 0;
    }
    if (month < 1 || month > 12)
    {
        cout << INVALID_MONTH << endl;
        return 0;
    }
    if (year < 2000 || year > 2100)
    {
        cout << INVALID_YEAR << endl;
        return 0;
    }

    bool isLeapYear = false;
    if (year % 400 == 0)
    {
        isLeapYear = 1;
    }
    else if (year % 100 == 0)
    {
        isLeapYear = 0;
    }
    else if (year % 4 == 0)
    {
        isLeapYear = 1;
    }
    else
    {
        isLeapYear = 0;
    }

    if (month == 2)
    {
        if (isLeapYear && day <= 29)
        {
            return 1;
        }
        else if (!isLeapYear && day <= 28)
        {
            return 1;
        }
        else
        {
            cout << LEAP_YEAR_FEBRUARY << endl;
            return 0;
        }
    }

    if (month == 4 || month == 6 || month == 9 || month == 11)
    {
        if (day <= 30)
        {
            return 1;
        }
        else
        {
            cout << WRONG_NUMBER_DAYS << endl;
            return 0;
        }
    }
    else
    {
        return 1;
    }
}

/**
    �������� ���� ������� ������� ���������� �� ������������ �� ������, ��������� ��������� ��� �����.
*/
bool checkUnitOfMeasure(string unitOfMeasure)
{
    if (find(begin(UNITS_OF_MEASUREMENT), end(UNITS_OF_MEASUREMENT), unitOfMeasure) != end(UNITS_OF_MEASUREMENT))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
    �������, ����� ����� ��������� �� ��� Date ��� �������� ������ ����.
*/
const Date getTodaysDate()
{
    time_t now = time(0);
    struct tm timeInfo;
    localtime_s(&timeInfo, &now);
    unsigned short int day = (&timeInfo)->tm_mday;
    unsigned short int month = 1 + (&timeInfo)->tm_mon;
    unsigned short int year = 1900 + (&timeInfo)->tm_year;
    return Date(day, month, year);
}

/**
    �������, ����� ����� ��������� �� ��� Date ��� �������� ����,
    ����� ��������� ����� �� ���� ���� ����������� ���� ���, ������� �� ����.
    ������������ ���� ��� � ����������� RANGE_OF_DAYS.
*/
const Date getDayAfterFewDays()
{
    const time_t daySeconds = 24 * 60 * 60;
    time_t now = time(0);
    struct tm timeInfo;
    time_t newDate = now + RANGE_OF_DAYS * daySeconds;
    localtime_s(&timeInfo, &newDate);
    unsigned short int day = (&timeInfo)->tm_mday;
    unsigned short int month = 1 + (&timeInfo)->tm_mon;
    unsigned short int year = 1900 + (&timeInfo)->tm_year;
    return Date(day, month, year);
}

/**
    �������, ����� �� ������� �������� ��� (��� ��� ��������� ������� � �����, � ������������ �� �����)
    ������ ���� ��� ��� �� ���������� ����� - ������� �� ���� ����� � �������� ��� � ����������.
    ��� ����������, ������� ������������ �� � ����� �������� �� ����� ��� ������ lines.
*/
void getLinesFromFile(string filePath, vector<string>& lines)
{
    string line;
    int lineCounter = 0;
    ifstream inputFileStream;
    inputFileStream.open(filePath, ios::in);

    if (inputFileStream.is_open()) {
        while (getline(inputFileStream, line))
        {
            lines.push_back(line);
        }
        inputFileStream.close();
        printSuccessReadMessage(filePath);
    }
    else if (!inputFileStream.good()) {
        ofstream outputFileStream;
        outputFileStream.open(filePath, ios::out);
        outputFileStream.close();
        printSuccessCreateMessage(filePath);
    }
    else {
        printErrorMessage(filePath);
    }
}

/**
    �������, ����� �� ������� �������� ��� (��� ��� ��������� ������� � �����, � ������������ �� �����)
    ������� ������������ �� ���� �� ���� ����� � �������� ��� � ����������.
    ���������� �����, ������������� �� � ��������� � ������.
*/
void overwriteFile(string filePath, Section*& sectionKG, Section*& sectionL) {
    ofstream outputFileStream;
    outputFileStream.open(filePath, ios::out);
    if (outputFileStream.is_open()) {
        for (int i = 0; i < MAX_SECTIONS; i++)
        {
            for (int k = 0; k < MAX_SHELVES; k++)
            {
                for (int t = 0; t < MAX_COMPARTMENTS; t++)
                {
                    int size = sectionKG[i].getShelves()[k].getCompartments()[t].getProducts().size();
                    if (size != 0)
                    {
                        for (int p = 0; p < size; p++)
                        {
                            outputFileStream << sectionKG[i].getShelves()[k].getCompartments()[t].getProducts()[p] << endl;
                        }
                    }
                }
            }
        }

        for (int i = 0; i < MAX_SECTIONS; i++)
        {
            for (int k = 0; k < MAX_SHELVES; k++)
            {
                for (int t = 0; t < MAX_COMPARTMENTS; t++)
                {
                    int size = sectionL[i].getShelves()[k].getCompartments()[t].getProducts().size();
                    if (size != 0)
                    {
                        for (int p = 0; p < size; p++)
                        {
                            outputFileStream << sectionL[i].getShelves()[k].getCompartments()[t].getProducts()[p] << endl;
                        }
                    }
                }
            }
        }
        outputFileStream.close();
        printSuccessSaveMessage(filePath);
    }
    else {
        printErrorMessage(filePath);
    }
}

/**
    �������, ����� ������ �������� ���, ���� ����� ���� ��� �������� �������� ���� ��������� ���
    �� ������ ���� �� ����� ��� ��� �������, �� �� ������ � �� �������� � ����� �� ���������� ��� ��� ����.
*/
const unsigned short int readNum(string numStr)
{
    unsigned short int num = 0;
    for (int i = 0; i < numStr.size(); i++)
    {
        num += (unsigned short int)((numStr[i] - 48) * pow(10, numStr.size() - i - 1));
    }
    return num;
}

/**
    �������, ����� ������ �������� ���, ���� ����� ���� ��� �������� �������� ���� ��������� ���
    �������� �� ������� �� ������ ��� ��� �������, �� �������� �� ������� � �� �������� � ����.
*/
const Date readDate(string dateStr)
{
    unsigned short int year = readNum(dateStr.substr(0, 4));
    unsigned short int month = readNum(dateStr.substr(5, 2));
    unsigned short int day = readNum(dateStr.substr(8, 2));

    return Date(day, month, year);
}

/**
    �������, ����� ������ �������� ��� � ��������� ���� �� ������ ���� �� �����.
*/
bool isInteger(string str) {
    for (int i = 0; i < str.length(); i++) {
        if (!isdigit(str[i]))
        {
            return false;
        }
    }
    return true;
}

/**
    �������, ����� ������ �������� ���, ���� ����� ���� ��� �������� �������� ���� ��������� ��� �������� �� ������� �� �������
    ��� ��� �������, �� �������� � �� �������� � ����� �� ����� �� ���������� ��� ��� ����.
*/
unsigned short int* readPosition(string positionStr)
{
    unsigned short int* position = new unsigned short int[3];
    unsigned short int place = positionStr.find("/");
    position[0] = readNum(positionStr.substr(0, place)) - 1;
    positionStr = positionStr.substr(place + 1);
    place = positionStr.find("/");
    position[1] = readNum(positionStr.substr(0, place)) - 1;
    position[2] = readNum(positionStr.substr(place + 1)) - 1;

    return position;
}

/**
    �������, ����� ������ ������� �� �������� � �������� ������, ���� �� ����� �������� ��� �� ������� ���� ��������� ���� �� ���� ��������� �� �������
    � �� ���� ����� ���� ��������� �� ������ ��������� ������� �������� � �� ���� ��� ������� �� ��������.
*/
void readProductsFromFile(vector<Product>& products, vector<string>& lines)
{
    string name, expiryDate, dateOfReceipt, manufacturersName, unitOfMeasure, quantity, position, comment;
    Product product = Product();
    int lineName = 0;
    int lineExpiryDate = 1;
    int lineDateOfReceipt = 2;
    int lineManufacturersName = 3;
    int lineUnitOfMeasure = 4;
    int lineQuantity = 5;
    int linePosition = 6;
    int lineComment = 7;
    for (int i = 0; i < lines.size() / 9; i++)
    {
        name = lines[lineName].substr(6);
        expiryDate = lines[lineExpiryDate].substr(13);
        dateOfReceipt = lines[lineDateOfReceipt].substr(17);
        manufacturersName = lines[lineManufacturersName].substr(21);
        unitOfMeasure = lines[lineUnitOfMeasure].substr(17);
        quantity = lines[lineQuantity].substr(10);
        position = lines[linePosition].substr(10);
        comment = lines[lineComment].substr(9);

        product.setName(name);
        product.setExpiryDate(readDate(expiryDate));
        product.setDateOfReceipt(readDate(dateOfReceipt));
        product.setManufacturersName(manufacturersName);
        product.setUnitOfMeasure(unitOfMeasure);
        product.setQuantity(stof(quantity));
        product.setPosition(readPosition(position));
        product.setComment(comment);

        products.push_back(product);
        lineName += LINES_DIFFERENCE;
        lineExpiryDate += LINES_DIFFERENCE;
        lineDateOfReceipt += LINES_DIFFERENCE;
        lineManufacturersName += LINES_DIFFERENCE;
        lineUnitOfMeasure += LINES_DIFFERENCE;
        lineQuantity += LINES_DIFFERENCE;
        linePosition += LINES_DIFFERENCE;
        lineComment += LINES_DIFFERENCE;
    }
}

/**
    �������, ����� ������ ����� �� ������ � ������ �� ��������� � ������� �� ����� ��������,
    ���� �� ����� ������� ����� ������� �����, ������������� �� � ��������� ��.
*/
void arrangeProductsInStorage(Section*& section, vector<Product>& products)
{
    for (int i = 0; i < MAX_SECTIONS; i++)
    {
        for (int k = 0; k < MAX_SHELVES; k++)
        {
            for (int t = 0; t < MAX_COMPARTMENTS; t++)
            {
                for (int p = 0; p < products.size(); p++)
                {
                    Product product = products[p];
                    if (i == product.getPosition()[0] && k == product.getPosition()[1] && t == product.getPosition()[2])
                    {
                        unsigned short int position[3] = { i + 1, k + 1, t + 1 };
                        product.setPosition(position);
                        section[i].getShelves()[k].getCompartments()[t].addProduct(product);
                    }
                }
            }
        }
    }
}

/**
    �������, ����� �� ������� �������� ��� (��� ��� ��������� ������� � �����, � ������������ �� �����) �
    ������ �� ������, ������ ���� � �� ������� � ���� ������, ��� �� ������� �������� �������� ����������.
*/
void completeLogFile(string filePath, vector<Log>& logs)
{
    ofstream outputFileStream;
    outputFileStream.open(filePath, ios::app);

    if (outputFileStream.is_open()) {
        for (int i = 0; i < logs.size(); i++)
        {
            outputFileStream << logs[i];
        }
        outputFileStream.close();
    }
    else {
        printErrorMessage(filePath);
    }
}

/**
    �������, ����� ���� �� ����� �������� ��� � �� �����, ���� ������������
    ������ �� ���� �������� ����, ����� ���� ������ � ������ ������ �� �� ������ ��������� ���.
*/
string readNameFromInput()
{
    string name;
    while (1)
    {
        cout << ENTER_NAME;
        getline(cin, name);
        if (name.size() > 0)
        {
            break;
        }
        else
        {
            cout << NOT_ENTERED_NAME << endl;
        }
    }

    return name;
}

/**
    �������, ����� ������ �������� ���, ����� ������ � ����� ���� ����� �� ���� � ���� �� �����.
    �� ������ ��� ������� �������� ���� � ��� ������� ������ � ���� �� � ������� ������ ���������� �� ����.
    ������, ��� �� ���� �������� ����, ����� � ��� �� �������� �� ���������, �� ���� ������ � ������ ������ �� �� ������� ����.
*/
Date readDateFromInput(string text)
{
    char dash;
    unsigned short int year, month, day;
    bool error;
    while (1)
    {
        error = false;
        cout << text;
        char a = cin.get();
        if (a == '\n')
        {
            cout << NOT_ENTERED_DATE << endl;
        }
        else if (!(a >= '0' && a <= '9'))
        {
            cout << INCORRECTLY_DATE << endl;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
        }
        else
        {
            cin >> year >> dash >> month >> dash >> day;
            if (cin.fail())
            {
                error = true;
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                cout << INCORRECTLY_DATE << endl;
            }

            if (!error)
            {
                if (a > '0' && a <= '9')
                {
                    year = year + 1000 * (a - 48);
                }

                if (checkDate(day, month, year))
                {
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');
                    break;
                }
                else
                {
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');
                }
            }
        }
    }
    Date date = Date(day, month, year);
    return date;
}

/**
    �������, ����� �������� ��� ����. ��� ������� �������� � ��-����� �� ������� ��� ������� � ���, �� �� �� ����� ������.
*/
bool compareDates(Date& dateOne, Date& dateTwo)
{
    if (dateOne.getYear() != dateTwo.getYear())
    {
        return dateOne.getYear() < dateTwo.getYear();
    }
    else
    {
        if (dateOne.getMonth() != dateTwo.getMonth())
        {
            return dateOne.getMonth() < dateTwo.getMonth();
        }
        else
        {
            if (dateOne.getDay() != dateTwo.getDay())
            {
                return dateOne.getDay() < dateTwo.getDay();
            }
            else
            {
                return 1;
            }
        }
    }
}

/**
    �������, ����� ���� �� ����� ����� � ������� ������, ��������� ���� � �������� �������� � ��� ������ � �����, �� �����.
    ����� �� ������� ������.
*/
float readQuantityFromInput()
{
    float quantity;
    string quantityString;
    int sizeFloat = to_string(MAX_COMPARTMENTS * MAX_CAPACITY * SCOPE_OF_PRODUCT).size() + 1 + 3; // Max capacity product + point + three decimal places
    while (1)
    {
        cout << ENTER_QUANTITY;
        getline(cin, quantityString);
        if (quantityString.size() > 0 && quantityString.size() <= sizeFloat)
        {
            if (quantityString[0] == '-')
            {
                cout << QUANTITY_MUST_POSITIVE << endl;
            }
            else if (quantityString.find_first_of(".") == quantityString.find_last_of("."))
            {
                int indexPoint = quantityString.find_first_of(".");
                if (indexPoint != -1 && isInteger(quantityString.substr(0, indexPoint)) && isInteger(quantityString.substr(indexPoint + 1)))
                {
                    if (quantityString.substr(indexPoint + 1).size() <= 3)  // .125, 25.250, 350.500
                    {
                        quantity = stof(quantityString);
                        break;
                    }
                    else
                    {
                        cout << THIRD_DECIMAL_PLACES << endl;
                    }
                }
                else
                {
                    if (isInteger(quantityString))
                    {
                        quantity = stof(quantityString);
                        break;
                    }
                    else
                    {
                        cout << INVALID_NUMBER_ENTRY << endl;
                    }
                }
            }
            else
            {
                cout << INVALID_NUMBER_ENTRY << endl;
            }
        }
        else if (quantityString.size() > sizeFloat && isInteger(quantityString))
        {
            cout << EXCESSIVE_NUMBER << sizeFloat << endl;
        }
        else if (quantityString.size() > sizeFloat)
        {
            cout << INVALID_NUMBER_ENTRY << endl;
        }
        else
        {
            cout << NOT_ENTERED_QUANTITY << endl;
        }
    }

    return quantity;
}

/**
    �������, ����� ������� ����������� ��� ����������� ������� �� �����.
*/
void answering(string& answer)
{
    while (1)
    {
        cout << ENTER_ANSWER;
        getline(cin, answer);
        if (answer.size() > 0)
        {
            if (find(begin(ANSWERS), end(ANSWERS), answer) != end(ANSWERS))
            {
                break;
            }
            else
            {
                cout << ALLOWED_ANSWERS << endl;
            }
        }
        else
        {
            cout << NOT_ENTERED_ANSWER << endl;
        }
    }
}

/**
    �������, ����� ���� �� ����� ����������� �� �������, ���� ������ �� ������������, ��� ���������. ��� ���� ������� ������ �������� ���,
    �� �� ������� ���������, ��� ���� �� �� ������ ��� �� ������ ���� ������, �� ������� ������ � ������ ������ �� �� �������.
*/
Product readProductFromInput()
{
    Date todaysDate = getTodaysDate();

    string name = readNameFromInput();

    Date expiryDate = Date();
    while (1)
    {
        expiryDate = readDateFromInput(ENTER_EXPIRY_DATE);
        if (expiryDate == todaysDate)
        {
            cout << DATE_EXPIRIES_TODAY << endl;
            string answer;
            answering(answer);
            if (answer == ANSWERS[1])
            {
                break;
            }
            else
            {
                cout << WRONG_DATE << endl;
            }
        }
        else if (compareDates(todaysDate, expiryDate))
        {
            break;
        }
        else
        {
            cout << DATE_ALREADY_EXPIRED << endl;
        }
    }


    Date dateOfReceipt = getTodaysDate();

    string manufacturersName;
    while (1)
    {
        cout << ENTER_MANUFACTURERS_NAME;
        getline(cin, manufacturersName);
        if (manufacturersName.size() > 0)
        {
            break;
        }
        else
        {
            cout << NOT_ENTERED_MANUFACTURERS_NAME << endl;
        }
    }

    string unitOfMeasure;
    while (1)
    {
        cout << ENTER_UNIT_OF_MEASURE;
        getline(cin, unitOfMeasure);
        if (unitOfMeasure.size() > 0)
        {
            if (checkUnitOfMeasure(unitOfMeasure))
            {
                break;
            }
            else
            {
                cout << ALLOWED_UNITS_OF_MEASURE << endl;
            }
        }
        else
        {
            cout << NOT_ENTERED_UNITS_OF_MEASURE << endl;
        }
    }

    float quantity = readQuantityFromInput();

    string comment;
    cout << ENTER_COMMENT;
    getline(cin, comment);
    if (comment.size() == 0)
    {
        comment = IF_NOT_ENTERED_COMMENT;
    }

    Product product(name, expiryDate, dateOfReceipt, manufacturersName, unitOfMeasure, quantity, comment);
    return product;
}

/**
    �������, ����� ���� �� ����� ����� � ������������ �� ��������, ����� ������ �� ������.
    ������, ��� ����� �� �� ������, �� ������ ������ � ������ �� ������ �� �� �������.
*/
Product readRemovalProductFromInput()
{
    string name = readNameFromInput();

    float quantity = readQuantityFromInput();

    Product product = Product();
    product.setName(name);
    product.setQuantity(quantity);
    product.setManufacturersName(DEFAULT_VALUE);
    product.setUnitOfMeasure(DEFAULT_VALUE);
    product.setComment(DEFAULT_VALUE);
    return product;
}

/**
    ���������, ����� � ������������� �� ��������� �� �������� - ������� ��� ����������� ���� ��� ����.
    � ����������� �� ������������ � ����������� � ���������.
*/
struct Position
{
    unsigned short int sect;
    unsigned short int shelf;
    unsigned short int comp;

    Position()
    {
        this->sect = 0;
        this->shelf = 0;
        this->comp = 0;
    }

    Position(unsigned short int sect, unsigned short int shelf, unsigned short int comp)
    {
        this->sect = sect;
        this->shelf = shelf;
        this->comp = comp;
    }
};

/**
    �������, ����� ������� ��������� ������� � ������ � �������� ���������� �� �������,
    ��� ���� ���������� ������ �� �������� �� 1.
*/
void positioning(Product& product, Section*& section, bool& productSuccessfullyAdded, unsigned short int indexSection, int k, int t)
{
    unsigned short int position[3] = { indexSection + 1, k + 1, t + 1 };
    product.setPosition(position);
    section[indexSection].getShelves()[k].getCompartments()[t].addProduct(product);
    productSuccessfullyAdded = true;
}

/**
    �������, ����� ������� ���� ������� �� ��� � ���������� �� ���������� ����������,
    ����� ���� �� �� ����� � ����������� � �������� ���������� �� �������.
*/
void separation(Product& product, Section*& section, unsigned short int indexSection, int k, int t, float freeQuantity)
{
    Product newProduct = product;
    newProduct.setQuantity(freeQuantity);
    unsigned short int position[3] = { indexSection + 1, k + 1, t + 1 };
    newProduct.setPosition(position);
    section[indexSection].getShelves()[k].getCompartments()[t].addProduct(newProduct);
    product.setQuantity(product.getQuantity() - freeQuantity);
}

/**
    �������, ����� �������� ����� � ������� ���������� �� ��� ����� � ��������.
*/
const float getOccupiedQuantity(Section*& section, unsigned short int indexSection, unsigned short int startingShelf)
{
    float occupiedQuantity = 0;
    for (int k = startingShelf; k < startingShelf + SCOPE_OF_PRODUCT; k++)
    {
        for (int t = 0; t < MAX_COMPARTMENTS; t++)
        {
            occupiedQuantity += section[indexSection].getShelves()[k].getCompartments()[t].getCapacity();
        }
    }

    return occupiedQuantity;
}

/**
    �������, ����� ������� ���� �� ������ ��������� ������� � ��������, ���� ������� �������� �������.
*/
void findFirstProduct(Position& positionFirstProduct, Section*& section, Product& product)
{
    bool productIsFound = false;
    for (int i = 0; i < MAX_SECTIONS; i++)
    {
        for (int k = 0; k < MAX_SHELVES; k++)
        {
            for (int t = 0; t < MAX_COMPARTMENTS; t++)
            {
                if (section[i].getShelves()[k].getCompartments()[t].getProducts().size() != 0)
                {
                    for (int p = 0; p < section[i].getShelves()[k].getCompartments()[t].getProducts().size() && !productIsFound; p++)
                    {
                        if (section[i].getShelves()[k].getCompartments()[t].getProducts()[p].getName() == product.getName())
                        {
                            productIsFound = true;
                            positionFirstProduct.sect = i;
                            positionFirstProduct.shelf = k;
                            positionFirstProduct.comp = t;
                        }
                    }
                }
            }
        }
    }
}

/**
    �������, ����� �� �������� ������� ������� ������� ����, �� �����
    ������� ������������ �� ����� ���������� ������� � ���� �������.
*/
void determiningStartingShelf(unsigned short int& startingShelf, Position& positionFirstProduct)
{
    if (positionFirstProduct.shelf % SCOPE_OF_PRODUCT == 1)
    {
        startingShelf = positionFirstProduct.shelf - 1;
    }
    else
    {
        startingShelf = positionFirstProduct.shelf;
    }
}

/**
    �������, ����� ���������� ��������� ���������� ������� � �������� ���������,
    ���� ��� � ����� ���������� �� ��������, �� �� �����.
*/
void storeInSeparateCompartment(Product& product, Section*& section, bool& productSuccessfullyAdded, unsigned short int indexSection, unsigned short int startingShelf)
{
    for (int k = startingShelf; k < startingShelf + SCOPE_OF_PRODUCT; k++)
    {
        for (int t = 0; t < MAX_COMPARTMENTS && !productSuccessfullyAdded; t++)
        {
            float occupiedQuantity = section[indexSection].getShelves()[k].getCompartments()[t].getCapacity();
            if (occupiedQuantity == 0)
            {
                if (section[indexSection].getShelves()[k].getCompartments()[t].isThereEnoughCapacity(product))
                {
                    positioning(product, section, productSuccessfullyAdded, indexSection, k, t);
                }
                else
                {
                    float freeQuantity = MAX_CAPACITY - occupiedQuantity;
                    separation(product, section, indexSection, k, t, freeQuantity);
                }
            }
        }
    }
}

/**
    �������, ����� ���������� ��������� ���������� ������� ������ ����, �� ��� ��� ���������� �� �� ���������� ������ ��������,
    �� �� �� ������ ���� ������� ���� �� ���� ��� ���� �� �� ������ ������ � ���������� �� ������� ����������.
*/
void storeWiselyWhereThereIsSpace(Product& product, Section*& section, bool& productSuccessfullyAdded, unsigned short int indexSection, unsigned short int startingShelf, bool& partOfProductIsAdded)
{
    for (int k = startingShelf; k < startingShelf + SCOPE_OF_PRODUCT; k++)
    {
        for (int t = 0; t < MAX_COMPARTMENTS && !productSuccessfullyAdded; t++)
        {
            float occupiedQuantity = section[indexSection].getShelves()[k].getCompartments()[t].getCapacity();
            if (occupiedQuantity <= MAX_CAPACITY - 5)
            {
                partOfProductIsAdded = true;
                if (section[indexSection].getShelves()[k].getCompartments()[t].isThereEnoughCapacity(product))
                {
                    positioning(product, section, productSuccessfullyAdded, indexSection, k, t);
                }
                else
                {
                    float freeQuantity = MAX_CAPACITY - occupiedQuantity;
                    separation(product, section, indexSection, k, t, freeQuantity);
                }
            }
        }
    }
}

/**
    �������, ����� ����� ���� ���� �� �� ������ ��� �������, ���� �������� ���� ������ ������� �� ����� ������� - (0, 2, 4)
*/
void findPlaceForNewProduct(Section*& section, bool& placeFound, unsigned short int& countFreeCompartments, unsigned short int& indexSection, unsigned short int& startingShelf)
{
    for (int i = 0; i < MAX_SECTIONS; i++)
    {
        for (int k = 0; k < MAX_SHELVES - 1 && !placeFound; k += SCOPE_OF_PRODUCT)
        {
            for (int t = 0; t < MAX_COMPARTMENTS; t++)
            {
                if (section[i].getShelves()[k].getCompartments()[t].getProducts().size() == 0 && section[i].getShelves()[k + 1].getCompartments()[t].getProducts().size() == 0)
                {
                    countFreeCompartments++;
                }
            }
            if (countFreeCompartments == MAX_COMPARTMENTS)
            {
                indexSection = i;
                startingShelf = k;
                placeFound = true;
            }
            else
            {
                countFreeCompartments = 0;
            }
        }
    }
}

/**
    �������, ����� ���������� ��������� ���������� �������, �������� ������� ������� ���� �� �������.
    ��� � ������ ���� ��� ���������� ������� � ���� ����, ��������� �� ������ �� �� ������ � ������ ���������,
    �� ��� ���� ������� ����� �������� �� ������� � ����� ���������, � ��� ��� ������� ����� - �������� �� �������.
*/
void positioningInRelationToExpiryDate(Product& product, Section*& section, bool& productSuccessfullyAdded, unsigned short int indexSection, unsigned short int startingShelf)
{
    for (int k = startingShelf; k < startingShelf + SCOPE_OF_PRODUCT; k++)
    {
        for (int t = 0; t < MAX_COMPARTMENTS; t++)
        {
            float occupiedQuantity = section[indexSection].getShelves()[k].getCompartments()[t].getCapacity();
            if (section[indexSection].getShelves()[k].getCompartments()[t].getProducts().size() != 0 && occupiedQuantity < MAX_CAPACITY)
            {
                for (int p = 0; p < section[indexSection].getShelves()[k].getCompartments()[t].getProducts().size() && !productSuccessfullyAdded; p++)
                {
                    Date expiryDate = section[indexSection].getShelves()[k].getCompartments()[t].getProducts()[p].getExpiryDate();
                    if (expiryDate == product.getExpiryDate())
                    {
                        if (section[indexSection].getShelves()[k].getCompartments()[t].isThereEnoughCapacity(product))
                        {
                            positioning(product, section, productSuccessfullyAdded, indexSection, k, t);
                        }
                        else
                        {
                            float freeQuantity = MAX_CAPACITY - occupiedQuantity;
                            separation(product, section, indexSection, k, t, freeQuantity);
                        }
                        break;
                    }
                }
            }
        }
    }
}

/**
    �������, ����� ������ ������� ������� � ������.
*/
void addProduct(Product& product, Section*& section, vector<Log>& logs, string operation)
{
    float allowedQuantity = MAX_CAPACITY * SCOPE_OF_PRODUCT * MAX_COMPARTMENTS;
    if (product.getQuantity() > allowedQuantity)                                    ///�������� ���� ������������ �� ��������� ������� ��������� �����������.    
    {
        cout << "The product cannot be added because its quantity exceeds the maximum allowed for one product! The allowed quantity is: " << allowedQuantity << product.getUnitOfMeasure() << endl;
        return;
    }

    Product productInfoForLog = product;

    bool isExisting = false;
    Position positionFirstProduct(0, 0, 65535);

    findFirstProduct(positionFirstProduct, section, product);
    if (positionFirstProduct.comp != 65535)
    {
        isExisting = true;
    }

    bool partOfProductIsAdded = false;
    bool productSuccessfullyAdded = false;
    bool noPlaceFound = false;
    if (isExisting)                                                                  ///��� ��������� ����������, �� ��������� ���� ������������ �� �� ��������� �����������,
    {                                                                                ///���� ���� �� ���� ������� ���� ��� � �������� � ��� ���, ���� �� �� ����� ����� � �� ������� � ������.
        unsigned short int indexSection = positionFirstProduct.sect;
        unsigned short int startingShelf = 0;
        determiningStartingShelf(startingShelf, positionFirstProduct);

        if (product.getQuantity() > allowedQuantity - getOccupiedQuantity(section, indexSection, startingShelf))
        {
            cout << PRODUCT_CANNOT_BE_ADDED;
            cout << allowedQuantity - getOccupiedQuantity(section, indexSection, startingShelf) << product.getUnitOfMeasure() << endl;
            return;
        }

        positioningInRelationToExpiryDate(product, section, productSuccessfullyAdded, indexSection, startingShelf);

        if (!productSuccessfullyAdded)
        {
            storeInSeparateCompartment(product, section, productSuccessfullyAdded, indexSection, startingShelf);
        }

        if (!productSuccessfullyAdded)
        {
            storeWiselyWhereThereIsSpace(product, section, productSuccessfullyAdded, indexSection, startingShelf, partOfProductIsAdded);
        }
    }
    else                                                                             ///��� ��������� �� ����������, ������������ ������ ���� ���� �� �� ������� � �� ��������� � ������.
    {
        unsigned short int countFreeCompartments = 0;
        unsigned short int indexSection = 0;
        unsigned short int startingShelf = 65535;
        bool placeFound = false;

        findPlaceForNewProduct(section, placeFound, countFreeCompartments, indexSection, startingShelf);

        if (startingShelf == 65535)                                                  ///��� �� � �������� ����� ������ � ������.
        {
            noPlaceFound = true;
        }
        else
        {
            storeInSeparateCompartment(product, section, productSuccessfullyAdded, indexSection, startingShelf);

            if (!productSuccessfullyAdded)
            {
                storeWiselyWhereThereIsSpace(product, section, productSuccessfullyAdded, indexSection, startingShelf, partOfProductIsAdded);
            }
        }
    }

    if (productSuccessfullyAdded)                                                    ///��� ��������� � ������� �������, ������ �� �� ������� ����� �� ��������� � ����������� �� ������.
    {
        if (operation == "add")
        {
            Log log(productInfoForLog.getDateOfReceipt(), "add", productInfoForLog); ///������� �� ��� �� ��� �������� � �� ���� ��� ������� �� ������.
            logs.push_back(log);
            cout << SUCCESSFULLY_ADDED << endl;
        }
    }
    else if (!productSuccessfullyAdded && noPlaceFound)                              ///��� ��������� �� � �������, ������ ���� ����� � ������.
    {
        cout << NO_SUITABLE_PLACE << endl;
    }
    else                                                                             ///��� ������ ��������� �� � ������� �������, ������ �� �� ���������� ������ �������� ��� �� �� � ������� ������.
    {
        if (partOfProductIsAdded)
        {
            cout << VERY_CHAOTIC << endl;
            cout << "Therefore, this quantity (" << product.getQuantity() << product.getUnitOfMeasure() << ") cannot be stored." << endl;
        }
        else
        {
            cout << ENOUGH_PRODUCT << endl;
        }
    }
}

/**
    �������, ����� ����� ��� ������ ��������� �� ������� �� ������ ���������� ��������,
    ����� ���� �� ���������� �� ��� �����.
*/
void getExpiryDates(Section*& section, vector<Date>& vectorExpiryDates, unsigned short int indexSection, unsigned short int startingShelf)
{
    for (int k = startingShelf; k < startingShelf + SCOPE_OF_PRODUCT; k++)
    {
        for (int t = 0; t < MAX_COMPARTMENTS; t++)
        {
            int size = section[indexSection].getShelves()[k].getCompartments()[t].getProducts().size();
            if (size != 0)
            {
                for (int p = 0; p < size; p++)
                {
                    bool expiryDateExists = false;
                    Date dateFromSection = section[indexSection].getShelves()[k].getCompartments()[t].getProducts()[p].getExpiryDate();
                    for (int v = 0; v < vectorExpiryDates.size(); v++)
                    {
                        if (dateFromSection == vectorExpiryDates[v])
                        {
                            expiryDateExists = true;
                        }
                    }

                    if (!expiryDateExists)
                    {
                        vectorExpiryDates.push_back(section[indexSection].getShelves()[k].getCompartments()[t].getProducts()[p].getExpiryDate());
                    }
                }
            }
        }
    }
}

/**
    �������, ����� ����� ������������ �� ������������ �������� � ������� ������� �� �������.
*/
float calcTotalQuantityAccordingExpiryDate(Section*& section, Date& expiryDate, unsigned short int indexSection, unsigned short int startingShelf)
{
    float totalQuantity = 0;
    for (int k = startingShelf; k < startingShelf + SCOPE_OF_PRODUCT; k++)
    {
        for (int t = 0; t < MAX_COMPARTMENTS; t++)
        {
            int size = section[indexSection].getShelves()[k].getCompartments()[t].getProducts().size();
            if (size != 0)
            {
                for (int p = 0; p < size; p++)
                {
                    Date dateFromSection = section[indexSection].getShelves()[k].getCompartments()[t].getProducts()[p].getExpiryDate();
                    if (dateFromSection == expiryDate)
                    {
                        totalQuantity += section[indexSection].getShelves()[k].getCompartments()[t].getProducts()[p].getQuantity();
                    }
                }
            }
        }
    }
    return totalQuantity;
}

/**
    �������, ����� �������� ��������� ������� �� ���������.
*/
void performRemoval(Section*& section, Date*& sortedExpiryDates, float quantity, Product& productInfoForLog, unsigned short int indexSection, int v, int k, int t, int p)
{
    cout << "The product with a quantity of " << quantity << productInfoForLog.getUnitOfMeasure()
        << " of the lot " << sortedExpiryDates[v] << " was successfully removed from the storage" << endl;
    Product removalProduct = section[indexSection].getShelves()[k].getCompartments()[t].getProducts()[p];
    section[indexSection].getShelves()[k].getCompartments()[t].removeProduct(removalProduct);
}

/**
    �������, ����� �������� ������ ���������� ��������, ����� �������� ���� ��� �����.
*/
void removeEntireQuantity(Section*& section, vector<Log>& logs, vector<Date>& vectorExpiryDates, Date*& sortedExpiryDates, unsigned short int indexSection, unsigned short int startingShelf, Product& productInfoForLog)
{
    float totalQuantityOfProduct = 0;
    for (int i = 0; i < vectorExpiryDates.size(); i++)
    {
        totalQuantityOfProduct += calcTotalQuantityAccordingExpiryDate(section, sortedExpiryDates[i], indexSection, startingShelf);
    }
    productInfoForLog.setQuantity(totalQuantityOfProduct);
    Log log(getTodaysDate(), "remove", productInfoForLog);                                      ///������� �� ��� �� ��� ���������� � �� ���� ��� ������� �� ������.
    logs.push_back(log);

    for (int i = 0; i < SCOPE_OF_PRODUCT; i++)
    {
        section[indexSection].getShelves()[startingShelf + i] = Shelf();
    }

    if (vectorExpiryDates.size() != 1)
    {
        cout << PRODUCTS_REMOVED_SUCCESSFULLY << endl;
    }
    else
    {
        cout << PRODUCT_REMOVED_SUCCESSFULLY << endl;
    }
}

/**
    �������, ����� ����������� ������������ �������� �� ��� �����.
*/
void rearrangingProducts(Section*& section, vector<Log>& logs, unsigned short int indexSection, unsigned short int startingShelf)
{
    vector<Product> products;
    for (int k = startingShelf; k < startingShelf + SCOPE_OF_PRODUCT; k++)
    {
        for (int t = 0; t < MAX_COMPARTMENTS; t++)
        {
            int size = section[indexSection].getShelves()[k].getCompartments()[t].getProducts().size();
            if (size != 0)
            {
                for (int p = 0; p < size; p++)
                {
                    products.push_back(section[indexSection].getShelves()[k].getCompartments()[t].getProducts()[p]);
                }
            }
        }
    }

    for (int i = 0; i < SCOPE_OF_PRODUCT; i++)
    {
        section[indexSection].getShelves()[startingShelf + i] = Shelf();
    }

    if (products.size() > 1)
    {
        for (int i = 0; i < products.size() - 1; i++)
        {
            Product productOne = products[i];
            Product productTwo = products[i + 1];
            Date productOneExpDate = productOne.getExpiryDate();
            Date productTwoExpDate = productTwo.getExpiryDate();
            Date productOneDateReceipt = productOne.getDateOfReceipt();
            Date productTwoDateReceipt = productTwo.getDateOfReceipt();
            if (productOne.getName() == productTwo.getName() && productOneExpDate == productTwoExpDate && productOneDateReceipt == productTwoDateReceipt
                && productOne.getManufacturersName() == productTwo.getManufacturersName() && productOne.getComment() == productTwo.getComment())
            {
                products[i].setQuantity(products[i].getQuantity() + products[i + 1].getQuantity());
                products.erase(remove(products.begin(), products.end(), productTwo), products.end());
                i--;
            }
        }
    }

    for (int i = 0; i < products.size(); i++)
    {
        addProduct(products[i], section, logs, "rearrangement");
    }
}

/**
    �������, ����� �������� ��������� ������� �� ������,
    ���������� ��������� �� ���������� �� ������� �� ���������.
*/
void removeProduct(Product& product, Section*& section, vector<Log>& logs)
{
    Product productInfoForLog = product;
    Position positionFirstProduct(0, 0, 0);
    findFirstProduct(positionFirstProduct, section, product);

    unsigned short int indexSection = positionFirstProduct.sect;
    unsigned short int startingShelf = 0;
    determiningStartingShelf(startingShelf, positionFirstProduct);

    vector<Date> vectorExpiryDates;
    getExpiryDates(section, vectorExpiryDates, indexSection, startingShelf);

    Date* sortedExpiryDates = new Date[vectorExpiryDates.size()];
    for (int i = 0; i < vectorExpiryDates.size(); i++)
    {
        sortedExpiryDates[i] = vectorExpiryDates[i];
    }
    sort(sortedExpiryDates, sortedExpiryDates + vectorExpiryDates.size(), compareDates);                      ///��������� �� ������� �� ��������, 
                                                                                                              ///�� �� ���� �� �� �������� ���������� � ���-����� ������� ����.

    if (product.getQuantity() > getOccupiedQuantity(section, indexSection, startingShelf))                    ///��� ������������, ����� ������ �� �� �������� � ��-������ �� ����, ����� � �������,
    {                                                                                                         ///�� ���� ����� ���� �� �� �������� ������ ��� ��� ��, ������ �� �� ������� ������.
        cout << PRODUCT_CANNOT_BE_REMOVED;
        cout << getOccupiedQuantity(section, indexSection, startingShelf) << product.getUnitOfMeasure() << endl;

        for (int i = 0; i < vectorExpiryDates.size(); i++)
        {
            cout << "Lot " << i + 1 << " of the product with a quantity of " << calcTotalQuantityAccordingExpiryDate(section, sortedExpiryDates[i], indexSection, startingShelf)
                << " with an expiry date: " << sortedExpiryDates[i] << endl;
        }

        cout << DO_YOU_WANT_TO_REMOVE << endl;
        string answer;
        answering(answer);

        if (answer == ANSWERS[1])
        {
            removeEntireQuantity(section, logs, vectorExpiryDates, sortedExpiryDates, indexSection, startingShelf, productInfoForLog);
        }
        else
        {
            return;
        }
    }
    else
    {
        bool productSuccessfullyRemoved = false;
        for (int v = 0; v < vectorExpiryDates.size(); v++)
        {
            for (int k = startingShelf; k < startingShelf + SCOPE_OF_PRODUCT; k++)
            {
                for (int t = 0; t < MAX_COMPARTMENTS; t++)
                {
                    if (section[indexSection].getShelves()[k].getCompartments()[t].getProducts().size() != 0)
                    {
                        for (int p = 0; p < section[indexSection].getShelves()[k].getCompartments()[t].getProducts().size() && !productSuccessfullyRemoved; p++)
                        {
                            Date dateFromSection = section[indexSection].getShelves()[k].getCompartments()[t].getProducts()[p].getExpiryDate();
                            if (dateFromSection == sortedExpiryDates[v])
                            {
                                float quantity = section[indexSection].getShelves()[k].getCompartments()[t].getProducts()[p].getQuantity();
                                if (quantity > product.getQuantity())                                         ///��� ������������, ����� ������ �� �� �����, � ��-����� �� ����, 
                                {                                                                             ///����� ��������� � ����������� ���, �������� ���������� �� ������.
                                    cout << "The quantity of product (" << quantity << productInfoForLog.getUnitOfMeasure()
                                        << ") in section " << indexSection + 1 << ", shelf " << k + 1
                                        << ", compartment " << t + 1 << " of the lot " << sortedExpiryDates[v] << " was reduced by "
                                        << product.getQuantity() << productInfoForLog.getUnitOfMeasure() << endl;
                                    section[indexSection].getShelves()[k].getCompartments()[t].getProducts()[p].setQuantity(quantity - product.getQuantity());
                                    section[indexSection].getShelves()[k].getCompartments()[t].reduceCapacity(product.getQuantity());
                                    productSuccessfullyRemoved = true;
                                }
                                else if (quantity == product.getQuantity())                                   ///��� ������������, ����� ������ �� �� �����, � ������� ����,
                                {                                                                             ///����� ��������� � ����������� ���, ��������� �� ����.
                                    performRemoval(section, sortedExpiryDates, quantity, productInfoForLog, indexSection, v, k, t, p);
                                    productSuccessfullyRemoved = true;
                                }
                                else                                                                          ///��� ������������, ����� ������ �� �� �����, � ������ �� ����, ����� ���������
                                {                                                                             ///� ����������� ���, ��������� �� ���� � �� ������������ �� ������� ������������ �� ��������.
                                    performRemoval(section, sortedExpiryDates, quantity, productInfoForLog, indexSection, v, k, t, p);
                                    product.setQuantity(product.getQuantity() - quantity);
                                    p--;
                                }
                            }
                        }
                    }
                }
            }
        }

        bool shelvesAreEmpty = true;
        for (int k = startingShelf; k < startingShelf + SCOPE_OF_PRODUCT; k++)
        {
            for (int t = 0; t < MAX_COMPARTMENTS; t++)
            {
                int size = section[indexSection].getShelves()[k].getCompartments()[t].getProducts().size();
                if (size != 0)
                {
                    shelvesAreEmpty = false;
                }
            }
        }

        if (!shelvesAreEmpty)                                                                                  ///��� ��������� �� ������, ���� ����� �� ������������.
        {
            rearrangingProducts(section, logs, indexSection, startingShelf);
            cout << SUCCESSFULLY_REARRANGEMENT << endl;
        }

        Log log(getTodaysDate(), "remove", productInfoForLog);                                                 ///������� �� ��� �� ��� ���������� � �� ���� ��� ������� �� ������.
        logs.push_back(log);
    }
}

/**
    �������, ����� ������ ���� �� ������ �������, �������� �� ����� ��� ��������� ��� � ����������.
    � ����� ��� ������ �, ���� � ���� �� ��������� ��� � ���� �� �����.
    ��� �� ������, �� �� ����� � ���������� �� ����� �������.
*/
Product readAndFindWhereIsProduct(Section*& sectionKG, Section*& sectionL)
{
    Product product = Product();
    bool isExisting = false;
    while (!isExisting)
    {
        product = readRemovalProductFromInput();

        for (int i = 0; i < MAX_SECTIONS; i++)
        {
            for (int k = 0; k < MAX_SHELVES; k++)
            {
                for (int t = 0; t < MAX_COMPARTMENTS; t++)
                {
                    for (int p = 0; p < sectionKG[i].getShelves()[k].getCompartments()[t].getProducts().size() && !isExisting; p++)
                    {
                        if (product.getName() == sectionKG[i].getShelves()[k].getCompartments()[t].getProducts()[p].getName())
                        {
                            isExisting = true;
                            product.setUnitOfMeasure(UNITS_OF_MEASUREMENT[0]);
                        }
                    }
                }
            }
        }

        if (!isExisting)
        {
            for (int i = 0; i < MAX_SECTIONS; i++)
            {
                for (int k = 0; k < MAX_SHELVES; k++)
                {
                    for (int t = 0; t < MAX_COMPARTMENTS; t++)
                    {
                        for (int p = 0; p < sectionL[i].getShelves()[k].getCompartments()[t].getProducts().size() && !isExisting; p++)
                        {
                            if (product.getName() == sectionL[i].getShelves()[k].getCompartments()[t].getProducts()[p].getName())
                            {
                                isExisting = true;
                                product.setUnitOfMeasure(UNITS_OF_MEASUREMENT[1]);
                            }
                        }
                    }
                }
            }
        }

        if (!isExisting)
        {
            cout << PRODUCT_NAME_NOT_FOUND << endl;
        }
    }

    return product;
}

/**
    �������, ����� �������� ������ ���������� ����� �� ��������� �������.
*/
void getTotalQuantityOfProduct(Section*& section, bool& getFirstProduct, Product& product, float& totalQuantity, int i, int k, int t)
{
    for (int p = 0; p < section[i].getShelves()[k].getCompartments()[t].getProducts().size(); p++)
    {
        if (!getFirstProduct)
        {
            product = section[i].getShelves()[k].getCompartments()[t].getProducts()[p];
            getFirstProduct = true;
        }
        totalQuantity += section[i].getShelves()[k].getCompartments()[t].getProducts()[p].getQuantity();
    }

    for (int p = 0; p < section[i].getShelves()[k + 1].getCompartments()[t].getProducts().size(); p++)
    {
        if (!getFirstProduct)
        {
            product = section[i].getShelves()[k + 1].getCompartments()[t].getProducts()[p];
            getFirstProduct = true;
        }
        totalQuantity += section[i].getShelves()[k + 1].getCompartments()[t].getProducts()[p].getQuantity();
    }
}

/**
    �������, ����� �������� ���������� �� ����������� � ������.
*/
void print(Section*& section)
{
    float totalQuantity = 0;
    Product product = Product();
    bool getFirstProduct = false;
    vector<Position> positions;
    for (int i = 0; i < MAX_SECTIONS; i++)
    {
        for (int k = 0; k < MAX_SHELVES; k += SCOPE_OF_PRODUCT)
        {
            totalQuantity = 0;
            getFirstProduct = false;
            positions.clear();
            for (int t = 0; t < MAX_COMPARTMENTS; t++)
            {
                getTotalQuantityOfProduct(section, getFirstProduct, product, totalQuantity, i, k, t);

                if (section[i].getShelves()[k].getCompartments()[t].getProducts().size() != 0)
                {
                    Position position = Position(i + 1, k + 1, t + 1);
                    positions.push_back(position);
                }

                if (t == MAX_COMPARTMENTS - 1)
                {
                    for (int c = 0; c < MAX_COMPARTMENTS; c++)
                    {
                        if (section[i].getShelves()[k + 1].getCompartments()[c].getProducts().size() != 0)
                        {
                            Position position = Position(i + 1, k + 2, c + 1);
                            positions.push_back(position);
                        }
                    }
                }
            }

            if (totalQuantity != 0)
            {
                cout << ENTER_NAME << product.getName() << endl;
                cout << ENTER_QUANTITY << totalQuantity << product.getUnitOfMeasure() << endl;

                if (positions.size() != 1)
                {
                    cout << POSITION;
                }
                else
                {
                    cout << POSITIONS;
                }

                for (int v = 0; v < positions.size(); v++)
                {
                    if (v == positions.size() - 1)
                    {
                        cout << "[" << positions[v].sect << "/" << positions[v].shelf << "/" << positions[v].comp << "]" << endl;
                        cout << '\n';
                    }
                    else
                    {
                        cout << "[" << positions[v].sect << "/" << positions[v].shelf << "/" << positions[v].comp << "], ";
                    }
                }
            }
        }
    }
}

/**
    �������, ����� ��������� ����������, ����� ���� �� �� ����� ��� �������� �� �� ������ ����� �� ������� � ���������� 5 ���.
*/
void clean(Section*& section, vector<Log>& logs)
{
    Date todaysDate = getTodaysDate();
    Date dayAfterFewDays = getDayAfterFewDays();
    for (int i = 0; i < MAX_SECTIONS; i++)
    {
        for (int k = 0; k < MAX_SHELVES; k++)
        {
            for (int t = 0; t < MAX_COMPARTMENTS; t++)
            {
                for (int p = 0; p < section[i].getShelves()[k].getCompartments()[t].getProducts().size(); p++)
                {
                    Date dateFromSection = section[i].getShelves()[k].getCompartments()[t].getProducts()[p].getExpiryDate();
                    if (!section[i].getShelves()[k].getCompartments()[t].getProducts()[p].isFit(todaysDate)
                        || compareDates(dateFromSection, dayAfterFewDays))
                    {
                        Product removalProduct = section[i].getShelves()[k].getCompartments()[t].getProducts()[p];
                        cout << "The product " << removalProduct.getName() << " with quantity " << removalProduct.getQuantity()
                            << " at position [" << removalProduct.getPositionString() << "] has been cleaned!" << endl;
                        section[i].getShelves()[k].getCompartments()[t].removeProduct(removalProduct);
                        Log log(getTodaysDate(), "clean", removalProduct);
                        logs.push_back(log);
                        p--;
                    }
                }
            }
        }
    }

    for (int i = 0; i < MAX_SECTIONS; i++)
    {
        for (int k = 0; k < MAX_SHELVES; k += SCOPE_OF_PRODUCT)
        {
            rearrangingProducts(section, logs, i, k);
        }
    }
}

/**
    �������, ����� �� ������� �������� ��� (��� ��� ��������� ������� � �����, � ������������ �� �����)
    ������ ����, ������� ������������ �� � ����� �������� �� ����� ��� ������ lines.
*/
void getLogsFromFile(string filePath, vector<string>& lines, Date& startDate, Date& endDate)
{
    string line;
    ifstream inputFileStream;
    inputFileStream.open(filePath, ios::in);

    if (inputFileStream.is_open()) {
        while (getline(inputFileStream, line))
        {
            Date dateFromFile = readDate(line.substr(0, 10));
            if (compareDates(startDate, dateFromFile) && compareDates(dateFromFile, endDate))
            {
                lines.push_back(line);
            }
        }
        inputFileStream.close();
    }
    else {
        printErrorMessage(filePath);
    }
}

/**
    �������, ����� �� ������� �������� ��� (��� ��� ��������� ������� � �����, � ������������ �� �����)
    ������ ���� ��� ��� ���� �����, �� ������� � �� ��������� ���� �� �����,
    ����� ��� ����� �������� ���������� �� ��������� �������� ���� ���.
    ����� ��� �� ��� ���� � ���� ���� ������ �� � ����� ������ �������� �� �����
    ��� ���� �� � ����� �� ����� �� �����������.
*/
void showLogs(string filePath)
{
    ifstream inputFileStream;
    inputFileStream.open(filePath, ios::in);

    if (!inputFileStream.good()) {
        ofstream outputFileStream;
        outputFileStream.open(filePath, ios::out);
        outputFileStream.close();
        inputFileStream.open(filePath, ios::in);
    }

    if (inputFileStream.is_open() && inputFileStream.peek() == ifstream::traits_type::eof())
    {
        cout << NO_DATA_INSERTED << endl;
        inputFileStream.close();
    }
    else
    {
        cout << DATES_RECEIVE_INFORMATION << endl;
        Date startDate = readDateFromInput(FROM);
        Date endDate = readDateFromInput(TO);

        vector<string> lines;
        getLogsFromFile(filePath, lines, startDate, endDate);

        if (lines.size() > 0)
        {
            for (int i = 0; i < lines.size(); i++)
            {
                cout << lines[i] << endl;
            }
        }
        else
        {
            cout << NO_ACTIONS << endl;
        }
    }
}

/**
    �������, ����� �� ������� �������� ��� (��� ��� ��������� ������� � �����, � ������������ �� �����)
    ������ ���� ��� ��� ���� �����, �������, �� ��� ��� ���� �������� �����.
    ��� ���, �������� �������� �� ��������� �� ����� ��� �� ������� � ���� �� ��������
    ��� ����� ���� ����� �������� ������������ ���������� �� �������� ���� ��������.
*/
void calculateLosses(string filePath)
{
    ifstream inputFileStream;
    inputFileStream.open(filePath, ios::in);
    if (inputFileStream.is_open() && inputFileStream.peek() == ifstream::traits_type::eof())
    {
        cout << NO_DATA_INSERTED << endl;
        inputFileStream.close();
    }
    else
    {
        string name = readNameFromInput();

        float price;
        string priceString;
        while (1)
        {
            cout << PRICE_PER_UNIT_OF_MEASURE;
            getline(cin, priceString);
            if (priceString.size() > 0)
            {
                if (priceString[0] == '-')
                {
                    cout << PRICE_MUST_POSITIVE << endl;
                }
                else if (priceString.find_first_of(".") == priceString.find_last_of("."))
                {
                    int indexPoint = priceString.find_first_of(".");
                    if (indexPoint != -1 && isInteger(priceString.substr(0, indexPoint)) && isInteger(priceString.substr(indexPoint + 1)))
                    {
                        if (priceString.substr(indexPoint + 1).size() <= 2)  // .12, 25.25, 350.50
                        {
                            price = stof(priceString);
                            break;
                        }
                        else
                        {
                            cout << PRICES_LIMITED_SECOND_DECIMAL_PLACES << endl;
                        }
                    }
                    else
                    {
                        if (isInteger(priceString))
                        {
                            price = stof(priceString);
                            break;
                        }
                        else
                        {
                            cout << INVALID_NUMBER_ENTRY << endl;
                        }
                    }
                }
                else
                {
                    cout << INVALID_NUMBER_ENTRY << endl;
                }
            }
            else
            {
                cout << NOT_ENTERED_PRICE << endl;
            }
        }

        cout << DATES_RECEIVE_INFORMATION_LOSSES << endl;
        Date startDate = readDateFromInput("From: ");
        Date endDate = readDateFromInput("To: ");

        vector<string> lines;
        getLogsFromFile(filePath, lines, startDate, endDate);
        int indexCleaned = 0;
        int indexName = 0;
        float discardedQuantity = 0;
        for (int i = 0; i < lines.size(); i++)
        {
            indexCleaned = lines[i].find("cleaned");
            indexName = lines[i].find(name);
            if (indexCleaned != -1 && indexName != -1 && (lines[i].find("of") + 9 + name.size()) == indexCleaned)  // potatoes vs red potatoes...������������ ��������, �� �� �� ������ ������ � ������������
            {
                int indexUnitOfMeasure = lines[i].find(UNITS_OF_MEASUREMENT[0]);
                if (indexUnitOfMeasure == -1)
                {
                    indexUnitOfMeasure = lines[i].find(UNITS_OF_MEASUREMENT[1]);
                }

                string quantityStr = lines[i].substr(13, indexUnitOfMeasure - 13);
                discardedQuantity += stof(quantityStr);
            }
        }

        float losses = (int)(price * discardedQuantity * 100 + 0.5);
        losses = (float)losses / 100;

        if (losses != 0)
        {
            cout << "The losses incurred are equal to the value of: " << losses << " BGN." << endl;
        }
        else
        {
            cout << NO_LOSSES << endl;
        }
    }
}

/**
    �������, ����� ��������� ���� ������ � ������.
*/
bool checkIfStorageIsEmpty(Section*& sectionKG, Section*& sectionL)
{
    bool isEmpty = true;
    for (int i = 0; i < MAX_SECTIONS; i++)
    {
        for (int k = 0; k < MAX_SHELVES; k++)
        {
            for (int t = 0; t < MAX_COMPARTMENTS && isEmpty; t++)
            {
                if (sectionKG[i].getShelves()[k].getCompartments()[t].getProducts().size() != 0
                    || sectionL[i].getShelves()[k].getCompartments()[t].getProducts().size() != 0)
                {
                    isEmpty = false;
                }
            }
        }
    }

    return isEmpty;
}

/**
    �������, ����� ������� ��������� �� ��������,
    �� ����� �������� � ��� ��� ������ ������ �� �� ������ ���������.
*/
void addCommand(Section*& sectionKG, Section*& sectionL, vector<Log>& logs)
{
    Product product = readProductFromInput();
    if (product.getUnitOfMeasure() == UNITS_OF_MEASUREMENT[0])
    {
        addProduct(product, sectionKG, logs, "add");
    }
    else
    {
        addProduct(product, sectionL, logs, "add");
    }
}

/**
    �������, ����� ������� ��������� �� ����������,
    �� ����� �������� �� ��� ��� ������ ������ �� �� �������� ���������.
*/
void removeCommand(Section*& sectionKG, Section*& sectionL, vector<Log>& logs)
{
    Product product = readAndFindWhereIsProduct(sectionKG, sectionL);

    if (product.getUnitOfMeasure() == UNITS_OF_MEASUREMENT[0])
    {
        removeProduct(product, sectionKG, logs);
    }
    else
    {
        removeProduct(product, sectionL, logs);
    }
}

/**
    �������, ����� ������� ��������� �� ����������� �� ������.
*/
void cleanCommand(Section*& sectionKG, Section*& sectionL, vector<Log>& logs)
{
    int sizeCurrentLogs = logs.size();
    clean(sectionKG, logs);
    clean(sectionL, logs);
    if (sizeCurrentLogs < logs.size())
    {
        cout << SUCCESSFULLY_CLEANING_REARRANGING << endl;
    }
    else
    {
        cout << NO_PRODUCTS_NEED_CLEAN << endl;
    }
}

/**
    �������, ����� ����������� ������� �� ����������� �������� �� �����.
*/
void close(Section*& sectionKG, Section*& sectionL, string filePathStorage)
{
    for (int i = 0; i < MAX_SECTIONS; i++)
    {
        for (int k = 0; k < MAX_SHELVES; k++)
        {
            for (int t = 0; t < MAX_COMPARTMENTS; t++)
            {
                sectionKG[i].getShelves()[k].getCompartments()[t].getProducts().clear();
                sectionL[i].getShelves()[k].getCompartments()[t].getProducts().clear();
                sectionKG[i].getShelves()[k].getCompartments()[t].setCapacity(0);
                sectionL[i].getShelves()[k].getCompartments()[t].setCapacity(0);
            }
        }
    }
    cout << "Successfully closed " << getNameFile(filePathStorage) << "!" << endl;
}

/**
    �������, ����� ���� ��������� �� ��������� �� ����� � ���������� � ����������� �� �� ����,
    �� ���������, � ������������� �� � �������� ����� ������, �� ������� � ������.
*/
void openCommand(string filePathStorage, vector<string>& lines, vector<Product>& products, Section*& sectionKG, Section*& sectionL)
{
    if (!checkFilePath(filePathStorage))
    {
        return;
    }

    vector<Product> productsKG;
    vector<Product> productsL;

    getLinesFromFile(filePathStorage, lines);
    readProductsFromFile(products, lines);

    for (int i = 0; i < products.size(); i++)
    {
        if (products[i].getUnitOfMeasure() == UNITS_OF_MEASUREMENT[0])
        {
            productsKG.push_back(products[i]);
        }
        else
        {
            productsL.push_back(products[i]);
        }
    }

    arrangeProductsInStorage(sectionKG, productsKG);
    arrangeProductsInStorage(sectionL, productsL);
}

/**
    �������, ����� �� ������� �������� ��� (��� ��� ��������� ������� � �����, � ������������ �� �����)
    ���������� �����, ���� ������� ��������� � ����������� � ������. �������� �� � ��������, ����
    ��������� completeLogFile.
*/
void saveCommand(string filePathStorage, string filePathLogs, vector<Log>& logs, Section*& sectionKG, Section*& sectionL)
{
    completeLogFile(filePathLogs, logs);
    logs.clear();
    overwriteFile(filePathStorage, sectionKG, sectionL);
}

/**
    �������, ����� ��������� ������� ����� �� ��������� � ������� ��������� ���� ����������� ����
    �� ������ ��������� ��������� �� ����, ����� �� ������� �������.
*/
void closeCommand(string filePathStorage, string filePathLogs, vector<Log>& logs, vector<Product>& products, vector<string>& lines, Section*& sectionKG, Section*& sectionL)
{
    if (!logs.empty())
    {
        string answer;
        cout << DO_YOU_WANT_KEEP_CHANGES << endl;
        answering(answer);
        if (answer == ANSWERS[1])
        {
            saveCommand(filePathStorage, filePathLogs, logs, sectionKG, sectionL);
        }
        else
        {
            logs.clear();
        }
    }

    products.clear();
    lines.clear();

    close(sectionKG, sectionL, filePathStorage);
}

/**
    �������, ����� �� ������� �������� ��� (��� ��� ��������� ������� � �����, � ������������ �� �����)
    ������� ���� �� ���� ����� � ������� ���������� ���������� �� ���������� � ������.
*/
void saveAsCommand(string newFilePathStorage, vector<string>& lines, Section*& sectionKG, Section*& sectionL)
{
    if (checkFilePath(newFilePathStorage))
    {
        if (!fileExists(newFilePathStorage))
        {
            getLinesFromFile(newFilePathStorage, lines);
            overwriteFile(newFilePathStorage, sectionKG, sectionL);
        }
        else
        {
            cout << FILE_EXISTS_SAME_NAME << endl;
        }
    }
}

/**
    �������, ����� ���� ������� ���������� �� ���������� ���������� �� ���������.
*/
void helpCommand()
{
    cout << "The following commands are supported:" << endl;
    cout << "open <file>        opens <file>" << endl;
    cout << "close              closes currently opened file" << endl;
    cout << "save               saves the currently open file" << endl;
    cout << "saveas <file>      saves the currently open file in <file>" << endl;
    cout << "help               prints this information" << endl;
    cout << "exit               exits the program" << '\n' << endl;

    cout << "The commands that are presented below, after entering them, you will receive additional information about what exactly they require" << endl;
    cout << "add               adds a new product to the warehouse" << endl;
    cout << "remove            removes product from Storage" << endl;
    cout << "print             prints information about availability in Storage" << endl;
    cout << "clean             removes products that have expired or are about to expire" << endl;
    cout << "log               displays information about the activities in the storage for a given period" << endl;
    cout << "losses            calculates the losses of a product for a given period" << '\n' << endl;
}

/**
    �������, ����� �������� ��� ������� �� �� ������� � ���������� �� �����.
*/
void commandPattern(bool& storageIsOpen, string filePathLogs, string& filePathStorage, string command, vector<string>& lines, vector<Log>& logs, vector<Product>& products, Section*& sectionKG, Section*& sectionL)
{
    if (command.size() > 0)
    {
        if ((command == "add" || command == "remove" || command == "log" || command == "clean" || command == "print"
            || command == "save" || command.substr(0, 6) == "saveas" || command == "losses") && !storageIsOpen)
        {
            cout << "To execute this command, you must first open the file!" << endl;
        }

        if ((command == "add" || command == "remove" || command == "log" || command == "clean" || command == "print"
            || command == "save" || command.substr(0, 6) == "saveas" || command == "losses") && storageIsOpen)
        {
            if (command == "add")
            {
                addCommand(sectionKG, sectionL, logs);
            }
            else if (command == "remove")
            {
                removeCommand(sectionKG, sectionL, logs);
            }
            else if (command == "log")
            {
                showLogs(filePathLogs);
            }
            else if (command == "clean")
            {
                cleanCommand(sectionKG, sectionL, logs);
            }
            else if (command == "losses")
            {
                calculateLosses(filePathLogs);
            }
            else if (command == "print")
            {
                if (checkIfStorageIsEmpty(sectionKG, sectionL))
                {
                    cout << NO_LOADED_PRODUCTS << endl;
                }
                else
                {
                    print(sectionKG);
                    print(sectionL);
                }
            }
            else if (command == "save")
            {
                saveCommand(filePathStorage, filePathLogs, logs, sectionKG, sectionL);
            }
            else if (command.substr(0, 6) == "saveas" && command.size() > 7)
            {
                string newFilePathStorage = command.substr(7);
                saveAsCommand(newFilePathStorage, lines, sectionKG, sectionL);
            }
            else if (command.substr(0, 6) == "saveas")
            {
                cout << FORGOT_ENTER_PATH << endl;
            }
        }

        if (command == "close" && !storageIsOpen)
        {
            cout << FIRST_OPEN_STORAGE << endl;
        }

        if (command == "close" && storageIsOpen)
        {
            storageIsOpen = false;
            closeCommand(filePathStorage, filePathLogs, logs, products, lines, sectionKG, sectionL);
        }

        if (command.substr(0, 4) == "open" && command.size() > 5)
        {
            filePathStorage = command.substr(5);
            storageIsOpen = true;

            openCommand(filePathStorage, lines, products, sectionKG, sectionL);
        }
        else if (command.substr(0, 4) == "open")
        {
            cout << FORGOT_ENTER_PATH << endl;
        }

        if (command == "help")
        {
            helpCommand();
        }

        if (command == "exit")
        {
            exit(0);
        }

        if (command != "add" && command != "remove" && command != "log" && command != "clean" && command != "print" && command != "close" && command != "losses"
            && command != "save" && command.substr(0, 6) != "saveas" && command != "help" && command != "exit" && command.substr(0, 4) != "open")
        {
            cout << COMMAND_NOT_RECOGNIZED << endl;
        }
    }
    else
    {
        cout << NOT_ENTERED_COMMAND << endl;
    }
}