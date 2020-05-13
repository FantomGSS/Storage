#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include "Section.h"
#include "Log.h"
using namespace std;

const unsigned short int LINES_DIFFERENCE = 9;
const unsigned short int MAX_SECTIONS = 12;
const unsigned short int SCOPE_OF_PRODUCT = 2;

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
    for (int i = 0; i < str.length(); i++) {
        if (!isdigit(str[i]))
        {
            return false;
        }
    }
    return true;
}

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
        product.setQuantity(stof(quantity));
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

void completeLogFile(const char* filePath, vector<Log> logs)
{
    ofstream outputFileStream;
    outputFileStream.open(filePath, ios::app);

    if (!outputFileStream.good())
    {
        ofstream outputFileStream;
        outputFileStream.open(filePath, ios::in);
        outputFileStream.close();
        outputFileStream.open(filePath, ios::app);
    }

    if (outputFileStream.is_open()) {
        for (int i = 0; i < logs.size(); i++)
        {
            outputFileStream << logs[i];
        }
        outputFileStream.close();
        printSuccessMessage(filePath);
    }
    else {
        printErrorMessage(filePath);
    }
}

Product readProductFromInput()
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
        else if (!(a >= '0' && a <= '9'))
        {
            cout << "This date was entered incorrectly! Follow this example: dd.mm.yyyy" << endl;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
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

    float quantity;
    string quantityString;
    while (1)
    {
        cout << "Quantity: ";
        getline(cin, quantityString);
        if (quantityString.size() > 0 && quantityString.size() <= 7)  
        {
            if (quantityString[0] == '-')
            {
                cout << "The quantity must be a positive number." << endl;
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
                        cout << "The program works with numbers limited to the third decimal places!" << endl;
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
                        cout << "You have entered an invalid number entry!" << endl;
                    }
                }
            }
            else
            {
                cout << "You have entered an invalid number entry!" << endl;
            }
        }
        else if (quantityString.size() > 7)
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

    Product product(name.c_str(), expiryDate, dateOfReceipt, manufacturersName.c_str(), unitOfMeasure.c_str(), quantity, comment.c_str());
    return product;
}

Product readRemovalProductFromInput()
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

    float quantity;
    string quantityString;
    while (1)
    {
        cout << "Quantity: ";
        getline(cin, quantityString);
        if (quantityString.size() > 0 && quantityString.size() <= 7)
        {
            if (quantityString[0] == '-')
            {
                cout << "The quantity must be a positive number." << endl;
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
                        cout << "The program works with numbers limited to the third decimal places!" << endl;
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
                        cout << "You have entered an invalid number entry!" << endl;
                    }
                }
            }
            else
            {
                cout << "You have entered an invalid number entry!" << endl;
            }
        }
        else if (quantityString.size() > 7)
        {
            cout << "You have entered an invalid number entry!" << endl;
        }
        else
        {
            cout << "You have not entered a quantity!" << endl;
        }
    }

    Product product = Product();
    product.setName(name.c_str());
    product.setQuantity(quantity);
    product.setManufacturersName("default");
    product.setUnitOfMeasure("default");
    product.setComment("default");
    return product;
}

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

void positioning(Product& product, Section*& section, bool& productSuccessfullyAdded, unsigned short int indexSection, int k, int t)
{
    unsigned short int position[3] = { indexSection + 1, k + 1, t + 1 };
    product.setPosition(position);
    section[indexSection].getShelves()[k].getCompartments()[t].addProduct(product);
    productSuccessfullyAdded = true;
}

void separation(Product& product, Section*& section, bool& productSuccessfullyAdded, unsigned short int indexSection, int k, int t, float freeQuantity)
{
    Product newProduct = product;
    newProduct.setQuantity(freeQuantity);
    unsigned short int position[3] = { indexSection + 1, k + 1, t + 1 };
    newProduct.setPosition(position);
    section[indexSection].getShelves()[k].getCompartments()[t].addProduct(newProduct);
    product.setQuantity(product.getQuantity() - freeQuantity);
}

const float getOccupiedQuantity(Product product, Section* section, unsigned short int indexSection, unsigned short int startingShelf)
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

void findFirstProduct(bool& isExisting, Position& positionFirstProduct, Section* section, Product product)
{
    for (int i = 0; i < MAX_SECTIONS; i++)
    {
        for (int k = 0; k < MAX_SHELVES; k++)
        {
            for (int t = 0; t < MAX_COMPARTMENTS; t++)
            {
                if (section[i].getShelves()[k].getCompartments()[t].getProducts().size() != 0)
                {
                    for (int p = 0; p < section[i].getShelves()[k].getCompartments()[t].getProducts().size() && !isExisting; p++)
                    {
                        if (compareChars(section[i].getShelves()[k].getCompartments()[t].getProducts()[p].getName(), product.getName()))
                        {
                            isExisting = true;
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

void determiningStartingShelf(unsigned short int& startingShelf, Position positionFirstProduct)
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
                    separation(product, section, productSuccessfullyAdded, indexSection, k, t, freeQuantity);
                }
            }
        }
    }
}

void storeWiselyWhereThereIsSpace(Product& product, Section*& section, bool& productSuccessfullyAdded, unsigned short int indexSection, unsigned short int startingShelf)
{
    for (int k = startingShelf; k < startingShelf + SCOPE_OF_PRODUCT; k++)
    {
        for (int t = 0; t < MAX_COMPARTMENTS && !productSuccessfullyAdded; t++)
        {
            float occupiedQuantity = section[indexSection].getShelves()[k].getCompartments()[t].getCapacity();
            if (occupiedQuantity <= MAX_CAPACITY - 5)
            {
                if (section[indexSection].getShelves()[k].getCompartments()[t].isThereEnoughCapacity(product))
                {
                    positioning(product, section, productSuccessfullyAdded, indexSection, k, t);
                }
                else
                {
                    float freeQuantity = MAX_CAPACITY - occupiedQuantity;
                    separation(product, section, productSuccessfullyAdded, indexSection, k, t, freeQuantity);
                }
            }
        }
    }
}

void findPlaceForNewProduct(Section* section, bool& placeFound, unsigned short int& countFreeCompartments, unsigned short int& indexSection, unsigned short int& startingShelf)
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
                            separation(product, section, productSuccessfullyAdded, indexSection, k, t, freeQuantity);
                        }
                        break;
                    }
                }
            }
        }
    }
}

void addProduct(Product product, Section*& section, vector<Log>& logs)
{
    float allowedQuantity = MAX_CAPACITY * SCOPE_OF_PRODUCT * MAX_COMPARTMENTS;
    if (product.getQuantity() > allowedQuantity)
    {
        cout << "The product cannot be added because its quantity exceeds the maximum allowed for one product! The allowed quantity is: " << allowedQuantity << product.getUnitOfMeasure() << endl;
        return;
    }

    Product productInfoForLog = product;

    bool isExisting = false;
    Position positionFirstProduct(0, 0, 0);

    findFirstProduct(isExisting, positionFirstProduct, section, product);

    bool productSuccessfullyAdded = false;
    bool noPlaceFound = false;
    if (isExisting)
    {
        unsigned short int indexSection = positionFirstProduct.sect;
        unsigned short int startingShelf = 0;
        determiningStartingShelf(startingShelf, positionFirstProduct);

        if (product.getQuantity() > allowedQuantity - getOccupiedQuantity(product, section, indexSection, startingShelf))
        {
            cout << "The product cannot be added because its quantity exceeds the maximum allowed for this product! You can only add: ";
            cout << allowedQuantity - getOccupiedQuantity(product, section, indexSection, startingShelf) << product.getUnitOfMeasure() << endl;
            return;
        }

        positioningInRelationToExpiryDate(product, section, productSuccessfullyAdded, indexSection, startingShelf);

        if (!productSuccessfullyAdded)
        {
            storeInSeparateCompartment(product, section, productSuccessfullyAdded, indexSection, startingShelf);
        }
        
        if (!productSuccessfullyAdded)
        {
            storeWiselyWhereThereIsSpace(product, section, productSuccessfullyAdded, indexSection, startingShelf);
        }
    }
    else
    {
        unsigned short int countFreeCompartments = 0;
        unsigned short int indexSection = 0;
        unsigned short int startingShelf = -1;
        bool placeFound = false;
        
        findPlaceForNewProduct(section, placeFound, countFreeCompartments, indexSection, startingShelf);

        if (startingShelf == -1)
        {
            noPlaceFound = true;
        }
        else
        {
            storeInSeparateCompartment(product, section, productSuccessfullyAdded, indexSection, startingShelf);

            if (!productSuccessfullyAdded)
            {
                storeWiselyWhereThereIsSpace(product, section, productSuccessfullyAdded, indexSection, startingShelf);
            }
        }
    }

    if (productSuccessfullyAdded)
    {
        Log log(productInfoForLog.getDateOfReceipt(), "add", productInfoForLog);
        logs.push_back(log);
        cout << "The product has been successfully added to the storage!" << endl;
    }
    else if (!productSuccessfullyAdded && noPlaceFound)
    {
        cout << "There are already enough different types of products. No suitable place can be found for your product." << endl;
    }
    else
    {
        cout << "As much of this product as possible has been added to the storage, but for the rest, the arrangement will become very chaotic!" << endl;
        cout << "Therefore, this quantity (" << product.getQuantity() << product.getUnitOfMeasure() << ") cannot be stored." << endl;
    }
}

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
                return 0;
            }
        }
    }
}

void getExpiryDates(Section* section, vector<Date>& vectorExpiryDates, unsigned short int indexSection, unsigned short int startingShelf)
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

float calcTotalQuantityAccordingExpiryDate(Section* section, Date expiryDate, unsigned short int indexSection, unsigned short int startingShelf)
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

void performRemoval(Section*& section, Date* sortedExpiryDates, float quantity, Product productInfoForLog, unsigned short int indexSection, int v, int k, int t, int p)
{
    cout << "The product with a quantity of " << quantity << productInfoForLog.getUnitOfMeasure()
        << " of the lot " << sortedExpiryDates[v] << " was successfully removed from the storage" << endl;
    Product removalProduct = section[indexSection].getShelves()[k].getCompartments()[t].getProducts()[p];
    section[indexSection].getShelves()[k].getCompartments()[t].removeProduct(removalProduct);
}

void removeEntireQuantity(Section*& section, vector<Log>& logs, vector<Date> vectorExpiryDates, Date* sortedExpiryDates, unsigned short int indexSection, unsigned short int startingShelf, Product& productInfoForLog)
{
    float totalQuantityOfProduct = 0;
    for (int i = 0; i < vectorExpiryDates.size(); i++)
    {
        totalQuantityOfProduct += calcTotalQuantityAccordingExpiryDate(section, sortedExpiryDates[i], indexSection, startingShelf);
    }
    productInfoForLog.setQuantity(totalQuantityOfProduct);
    Log log(getTodaysDate(), "remove", productInfoForLog);
    logs.push_back(log);

    for (int k = startingShelf; k < startingShelf + SCOPE_OF_PRODUCT; k++)
    {
        for (int t = 0; t < MAX_COMPARTMENTS; t++)
        {
            int size = section[indexSection].getShelves()[k].getCompartments()[t].getProducts().size();
            if (size != 0)
            {
                section[indexSection].getShelves()[k].getCompartments()[t] = Compartment();
            }
        }
    }

    if (vectorExpiryDates.size() != 1)
    {
        cout << "The products have been removed successfully!" << endl;
    }
    else
    {
        cout << "The product has been removed successfully!" << endl;
    }
}

void removeProduct(Product product, Section*& section, vector<Log>& logs)
{
    Product productInfoForLog = product;

    bool isExisting = false;
    Position positionFirstProduct(0, 0, 0);

    findFirstProduct(isExisting, positionFirstProduct, section, product);

    if (isExisting)
    {
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
        sort(sortedExpiryDates, sortedExpiryDates + vectorExpiryDates.size(), compareDates);

        if (product.getQuantity() > getOccupiedQuantity(product, section, indexSection, startingShelf))
        {
            cout << "The product cannot be removed because the quantity you entered exceeds available in the storage. You can only remove: ";
            cout << getOccupiedQuantity(product, section, indexSection, startingShelf) << product.getUnitOfMeasure() << endl;
            
            for (int i = 0; i < vectorExpiryDates.size(); i++)
            {
                cout << "Lot " << i + 1 << " of the product with a quantity of " << calcTotalQuantityAccordingExpiryDate(section, sortedExpiryDates[i], indexSection, startingShelf)
                     << " with an expiry date: " << sortedExpiryDates[i] << endl;
            }
            
            cout << "Do you want to remove the quantity that is available in the storage from this product ?" << endl;
            string answer;
            while (1)
            {
                cout << "Answer: ";
                getline(cin, answer);
                if (answer.size() > 0)
                {
                    if (answer == "Yes" || answer == "No")
                    {
                        break;
                    }
                    else
                    {
                        cout << "Allowed answers are Yes or No." << endl;
                    }
                }
                else
                {
                    cout << "You have not entered a answer!" << endl;
                }
            }
            
            if (answer == "Yes")
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
            bool productSuccessfullyAdded = false;
            bool unitOfMeasureSet = false;
            for (int v = 0; v < vectorExpiryDates.size(); v++)
            {
                for (int k = startingShelf; k < startingShelf + SCOPE_OF_PRODUCT; k++)
                {
                    for (int t = 0; t < MAX_COMPARTMENTS; t++)
                    {
                        if (section[indexSection].getShelves()[k].getCompartments()[t].getProducts().size() != 0)
                        {
                            for (int p = 0; p < section[indexSection].getShelves()[k].getCompartments()[t].getProducts().size() && !productSuccessfullyAdded; p++)
                            {
                                if (!unitOfMeasureSet)
                                {
                                    productInfoForLog.setUnitOfMeasure(section[indexSection].getShelves()[k].getCompartments()[t].getProducts()[p].getUnitOfMeasure());
                                    unitOfMeasureSet = true;
                                }

                                Date dateFromSection = section[indexSection].getShelves()[k].getCompartments()[t].getProducts()[p].getExpiryDate();
                                if (dateFromSection == sortedExpiryDates[v])
                                {
                                    float quantity = section[indexSection].getShelves()[k].getCompartments()[t].getProducts()[p].getQuantity();
                                    if (quantity > product.getQuantity())
                                    {
                                        cout << "The quantity of product (" << quantity << productInfoForLog.getUnitOfMeasure() 
                                             << ") in section " << indexSection + 1 << ", shelf " << k + 1 
                                             << ", compartment " << t + 1 << " of the lot " << sortedExpiryDates[v] << " was reduced by " 
                                             << product.getQuantity() << productInfoForLog.getUnitOfMeasure() << endl;
                                        section[indexSection].getShelves()[k].getCompartments()[t].getProducts()[p].setQuantity(quantity - product.getQuantity());
                                        section[indexSection].getShelves()[k].getCompartments()[t].reduceCapacity(product.getQuantity());
                                        productSuccessfullyAdded = true;
                                    }
                                    else if (quantity == product.getQuantity())
                                    {
                                        performRemoval(section, sortedExpiryDates, quantity, productInfoForLog, indexSection, v, k, t, p);
                                        productSuccessfullyAdded = true;
                                    }
                                    else
                                    {
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

            Log log(getTodaysDate(), "remove", productInfoForLog);
            logs.push_back(log);
        }
    }
    else
    {
        cout << "This product does not exist in the storage! Make sure you enter the name correctly." << endl;
    }
}

void getTotalQuantityOfProduct(Section* section, bool& getFirstProduct, Product& product, float& totalQuantity, int i, int k, int t)
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

void print(Section*& section)
{
    float totalQuantity = 0;
    Product product = Product();
    bool getFirstProduct = false;
    vector<Position> positions;
    for (int i = 0; i < MAX_SECTIONS; i++)
    {
        for (int k = 0; k < MAX_SHELVES; k+=SCOPE_OF_PRODUCT)
        {
            totalQuantity = 0;
            for (int t = 0; t < MAX_COMPARTMENTS; t++)
            {
                getTotalQuantityOfProduct(section, getFirstProduct, product, totalQuantity, i, k, t);

                Position position = Position(i + 1, k + 1, t + 1);
                positions.push_back(position);

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
                cout << "Name: " << product.getName() << endl;
                cout << "Quantity: " << totalQuantity << product.getUnitOfMeasure() << endl;

                if (positions.size() != 1)
                {
                    cout << "Position: ";
                }
                else
                {
                    cout << "Positions: ";
                }

                for (int v = 0; v < positions.size(); v++)
                {
                    if (v == positions.size() - 1)
                    {
                        cout << "[" << positions[v].sect << "/" << positions[v].shelf << "/" << positions[v].comp << "]" << endl;
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

int main()
{
    const char* filePathStorage = "Products.txt";
    const char* filePathLogs = "Logs.txt";
    vector<Log> logs;
    vector<string> lines;
    //getLinesFromFile(filePath, lines);
    vector<Product> products;
    //readProductsFromFile(products, lines);

    //Product productAdd = readProductFromInput();
    //Product productRemove = readRemovalProductFromInput();

    Section* section = new Section[MAX_SECTIONS];
    Date today = getTodaysDate();
    Product productOne("potatoes", Date(24, 05, 2020), today, "Kompir", "kg", 22, "HIGH QUALITY POTATOES FROM SAMOKOV SCROLL DOWN");
    Product productTwo("potatoes", Date(24, 05, 2020), today, "Kompir", "kg", 30, "HIGH QUALITY POTATOES FROM SAMOKOV SCROLL DOWN");
    Product productThree("potatoes", Date(26, 05, 2020), today, "Kompir", "kg", 50, "HIGH QUALITY POTATOES FROM SAMOKOV SCROLL DOWN");
    Product productFour("potatoes", Date(27, 05, 2020), today, "Kompir", "kg", 60, "HIGH QUALITY POTATOES FROM SAMOKOV SCROLL DOWN");
    //Product productFour("potatoes", Date(27, 05, 2020), today, "Kompir", "kg", 600, "HIGH QUALITY POTATOES FROM SAMOKOV SCROLL DOWN");
    addProduct(productOne, section, logs);
    addProduct(productTwo, section, logs);
    addProduct(productThree, section, logs);
    addProduct(productFour, section, logs);

    removeProduct(productFour, section, logs);
    removeProduct(productOne, section, logs);

    /*
    Product productFive("carrots", Date(20, 05, 2020), today, "AGRO_ALEKSANDRA", "kg", 22, "The sweetest carrots!");
    Product productSix("carrots", Date(21, 05, 2020), today, "AGRO_ALEKSANDRA", "kg", 30, "The sweetest carrots!");
    Product productSeven("carrots", Date(27, 05, 2020), today, "AGRO_ALEKSANDRA", "kg", 50, "The sweetest carrots!");
    Product productEight("carrots", Date(22, 05, 2020), today, "AGRO_ALEKSANDRA", "kg", 600, "The sweetest carrots!");
    addProduct(productFive, section, logs);
    addProduct(productSix, section, logs);
    addProduct(productSeven, section, logs);
    addProduct(productEight, section, logs);
    */

    print(section);

    cout << endl;

    for (int i = 0; i < MAX_SECTIONS; i++)
    {
        for (int k = 0; k < MAX_SHELVES; k++)
        {
            for (int t = 0; t < MAX_COMPARTMENTS; t++)
            {
                for (int p = 0; p < section[i].getShelves()[k].getCompartments()[t].getProducts().size(); p++)
                {
                    cout << section[i].getShelves()[k].getCompartments()[t].getProducts()[p] << endl;
                }
            }
        }
    }
    
    completeLogFile(filePathLogs, logs);
}