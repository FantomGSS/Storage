#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include "Section.h"
using namespace std;

const unsigned short int LINES_DIFFERENCE = 9;

void printErrorMessage(const char* filePath) {
    cerr << "\n";
    cerr << "There was a problem opening file with name: " << filePath << endl;
    cerr << "\n";
}

void printSuccessMessage(const char* filePath) {
    cout << "\n";
    cout << "===========================================================" << endl;
    cout << "All changes are saved successfully in the file " << filePath << "!" << endl;
    cout << "===========================================================" << endl;
    cout << "\n";
}

bool checkDate(unsigned short int day, unsigned short int month, unsigned short int year)
{
    if (day < 1 || day > 31)
    {
        cout << "You have entered an invalid day. Please try again!" << endl;
        return 0;
    }
    if (month < 1 || month > 12)
    {
        cout << "You have entered an invalid month. Please try again!" << endl;
        return 0;
    }
    if (year < 1900 || year > 2100)
    {
        cout << "You have entered an invalid year. It should be in the area between 1900 and 2100." << endl;
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
            cout << "Wrong year or wrong number of days! In the leap years alone, February has 29 days." << endl;
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
            cout << "Wrong number of days for this month! Please try again!" << endl;
            return 0;
        }
    }
    else
    {
        return 1;
    }
}

bool checkUnitOfMeasure(const char* unitOfMeasure) 
{
    if (compareChars(unitOfMeasure, "kg") || compareChars(unitOfMeasure, "l"))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

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

void getLinesFromFile(const char* filePath, vector<string>& lines)
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
    }
    else if (!inputFileStream.good()) {
        ofstream outputFileStream;
        outputFileStream.open(filePath, ios::out);
        outputFileStream.close();
    }
    else {
        printErrorMessage(filePath);
    }
}

const unsigned short int readNum(string numStr)
{
    unsigned short int num = 0;
    for (int i = 0; i < numStr.size(); i++)
    {
        num += (unsigned short int)((numStr[i] - 48) * pow(10, numStr.size() - i - 1));
    }
    return num;
}

const Date readDate(string dateStr)
{
    unsigned short int day = readNum(dateStr.substr(0, 2));
    unsigned short int month = readNum(dateStr.substr(3, 2));
    unsigned short int year = readNum(dateStr.substr(6, 4));

    return Date(day, month, year);
}

bool isInteger(string str) {
    bool state = true;

    for (int i = 0; state && i < str.length(); i++) {
        if (!isdigit(str[i])) {
            state = false;
        }
    }
    return state;
}

unsigned short int* readPosition(string positionStr)
{
    unsigned short int* position = new unsigned short int[3];
    unsigned short int place = positionStr.find("/");
    position[0] = readNum(positionStr.substr(0, place));
    positionStr = positionStr.substr(place + 1);
    place = positionStr.find("/");
    position[1] = readNum(positionStr.substr(0, place));
    position[2] = readNum(positionStr.substr(place + 1));
    
    return position;
}

void readProductsFromFile(vector<Product>& products, vector<string> lines)
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
    for (int i = 0; i < (lines.size() + 1) / 9; i++)
    {
        name = lines[lineName].substr(6);
        expiryDate = lines[lineExpiryDate].substr(13);
        dateOfReceipt = lines[lineDateOfReceipt].substr(17);
        manufacturersName = lines[lineManufacturersName].substr(21);
        unitOfMeasure = lines[lineUnitOfMeasure].substr(17);
        quantity = lines[lineQuantity].substr(10);
        position = lines[linePosition].substr(10);
        comment = lines[lineComment].substr(9);

        product.setName(name.c_str());
        product.setExpiryDate(readDate(expiryDate));
        product.setDateOfReceipt(readDate(dateOfReceipt));
        product.setManufacturersName(manufacturersName.c_str());
        product.setUnitOfMeasure(unitOfMeasure.c_str());
        product.setQuantity(readNum(quantity));
        product.setPosition(readPosition(position));
        product.setComment(comment.c_str());

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

void readProductFromInput()
{
    string name;
    while (1)
    {
        cout << "Name: ";
        getline(cin, name);
        if (name.size() > 0)
        {
            break;
        }
        else
        {
            cout << "You have not entered a name!" << endl;
        }
    }

    char point;
    unsigned short int day, month, year;
    bool error;
    while (1)
    {
        error = false;
        cout << "Expiry Date: ";
        char a = cin.get();
        if (a == '\n')
        {
            cout << "You have not entered a date!" << endl;
        }
        else
        {
            cin >> day >> point >> month >> point >> year;
            if (cin.fail())
            {
                error = true;
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                cout << "This date was entered incorrectly! Follow this example: dd.mm.yyyy" << endl;
            }

            if (!error)
            {
                if (a > '0' && a <= '9')
                {
                    day = day + 10 * (a - 48);
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
    Date expiryDate = Date(day, month, year);

    Date dateOfReceipt = getTodaysDate();

    string manufacturersName;
    while (1)
    {
        cout << "Manufacturer's Name: ";
        getline(cin, manufacturersName);
        if (manufacturersName.size() > 0)
        {
            break;
        }
        else
        {
            cout << "You have not entered a manufacturer's name: !" << endl;
        }
    }

    string unitOfMeasure;
    while (1)
    {
        cout << "Unit of Measure: ";
        getline(cin, unitOfMeasure);
        if (unitOfMeasure.size() > 0)
        {
            if (checkUnitOfMeasure(unitOfMeasure.c_str()))
            {
                break;
            }
            else
            {
                cout << "The allowed units of measure are kg and l!" << endl;
            }
        }
        else
        {
            cout << "You have not entered a unit of measure!" << endl;
        }
    }

    unsigned short int quantity;
    string quantityString;
    while (1)
    {
        cout << "Quantity: ";
        getline(cin, quantityString);
        if (quantityString.size() > 0 && quantityString.size() <= 5)
        {
            if (isInteger(quantityString) && strcmp(quantityString.c_str(), "65535") <= 0 && strcmp("0", quantityString.c_str()) < 0)
            {
                quantity = readNum(quantityString);
                break;
            }
            else
            {
                cout << "You have entered an invalid number entry! The quantity must be a positive number." << endl;
            }
        }
        else if (isInteger(quantityString) && quantityString.size() > 5)
        {
            cout << "You have entered an excessive number!" << endl;
        }
        else if (quantityString.size() > 5)
        {
            cout << "You have entered an invalid number entry!" << endl;
        }
        else
        {
            cout << "You have not entered a quantity!" << endl;
        }
    }

    string comment;
    while (1)
    {
        cout << "Comment: ";
        getline(cin, comment);
        if (comment.size() > 0)
        {
            break;
        }
        else
        {
            cout << "You have not entered a comment!" << endl;
        }
    }

    cout << name << endl << expiryDate << endl << dateOfReceipt << endl << manufacturersName << endl << unitOfMeasure << endl << quantity << endl << comment << endl;
}

int main()
{
    const char* filePath = "Products.txt";
    vector<string> lines;
    getLinesFromFile(filePath, lines);

    vector<Product> products;
    readProductsFromFile(products, lines);

    readProductFromInput();
}