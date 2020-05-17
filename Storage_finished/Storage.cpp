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

void printErrorMessage(string filePath) {
    cerr << "\n";
    cerr << "There was a problem opening file with name: " << filePath << endl;
    cerr << "\n";
}

void printSuccessSaveMessage(string filePath) {
    cout << "===========================================================" << endl;
    cout << "All changes are saved successfully in the file " << filePath << "!" << endl;
    cout << "===========================================================" << endl;
}

void printSuccessReadMessage(string filePath) {
    cout << "===========================================================" << endl;
    cout << "Successfully opened " << filePath << "!" << endl;
    cout << "===========================================================" << endl;
}

void printSuccessCreateMessage(string filePath) {
    cout << "===========================================================" << endl;
    cout << "Successfully created " << filePath << "!" << endl;
    cout << "===========================================================" << endl;
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

void overwriteFile(string filePath, Section* sectionKG, Section* sectionL) {
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
    unsigned short int year = readNum(dateStr.substr(0, 4));
    unsigned short int month = readNum(dateStr.substr(5, 2));
    unsigned short int day = readNum(dateStr.substr(8, 2));

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

void completeLogFile(string filePath, vector<Log> logs)
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

string readNameFromInput()
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

    return name;
}

Date readDateFromInput(const char* text)
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
            cout << "You have not entered a date!" << endl;
        }
        else if (!(a >= '0' && a <= '9'))
        {
            cout << "This date was entered incorrectly! Follow this example: yyyy-mm-dd" << endl;
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
                cout << "This date was entered incorrectly! Follow this example: yyyy-mm-dd" << endl;
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

float readQuantityFromInput()
{
    float quantity;
    string quantityString;
    int sizeFloat = to_string(MAX_COMPARTMENTS * MAX_CAPACITY * SCOPE_OF_PRODUCT).size() + 1 + 3; // Max capacity product + point + three decimal places
    while (1)
    {
        cout << "Quantity: ";
        getline(cin, quantityString);
        if (quantityString.size() > 0 && quantityString.size() <= sizeFloat)
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
        else if (quantityString.size() > sizeFloat && isInteger(quantityString))
        {
            cout << "You have entered an excessive number! The allowed number of characters is: " << sizeFloat << endl;
        }
        else if (quantityString.size() > sizeFloat)
        {
            cout << "You have entered an invalid number entry!" << endl;
        }
        else
        {
            cout << "You have not entered a quantity!" << endl;
        }
    }

    return quantity;
}

Product readProductFromInput()
{
    string name = readNameFromInput();

    Date expiryDate = readDateFromInput("Expiry Date: ");

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

    float quantity = readQuantityFromInput();

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
    string name = readNameFromInput();

    float quantity = readQuantityFromInput();

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

void findFirstProduct(Position& positionFirstProduct, Section* section, Product product)
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
                        if (compareChars(section[i].getShelves()[k].getCompartments()[t].getProducts()[p].getName(), product.getName()))
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

void addProduct(Product product, Section*& section, vector<Log>& logs, string operation)
{
    float allowedQuantity = MAX_CAPACITY * SCOPE_OF_PRODUCT * MAX_COMPARTMENTS;
    if (product.getQuantity() > allowedQuantity)
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
        unsigned short int startingShelf = 65535;
        bool placeFound = false;
        
        findPlaceForNewProduct(section, placeFound, countFreeCompartments, indexSection, startingShelf);

        if (startingShelf == 65535)
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
        if (operation == "add")
        {
            Log log(productInfoForLog.getDateOfReceipt(), "add", productInfoForLog);
            logs.push_back(log);
            cout << "The product has been successfully added to the storage!" << endl;
        }
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
                return 1;
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

    for (int i = 0; i < SCOPE_OF_PRODUCT; i++)
    {
        section[indexSection].getShelves()[startingShelf + i] = Shelf();
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
            if (compareChars(productOne.getName(), productTwo.getName()) && productOneExpDate == productTwoExpDate && productOneDateReceipt == productTwoDateReceipt
                && compareChars(productOne.getManufacturersName(), productTwo.getManufacturersName()) && compareChars(productOne.getComment(), productTwo.getComment()))
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

void removeProduct(Product product, Section*& section, vector<Log>& logs)
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

        if (!shelvesAreEmpty)
        {
            rearrangingProducts(section, logs, indexSection, startingShelf);
            cout << "Successful rearrangement completed!" << endl;
        }
        
        Log log(getTodaysDate(), "remove", productInfoForLog);
        logs.push_back(log);
    }
}

Product readAndFindWhereIsProduct(Section* sectionKG, Section* sectionL)
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
                        if (compareChars(product.getName(), sectionKG[i].getShelves()[k].getCompartments()[t].getProducts()[p].getName()))
                        {
                            isExisting = true;
                            product.setUnitOfMeasure("kg");
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
                            if (compareChars(product.getName(), sectionL[i].getShelves()[k].getCompartments()[t].getProducts()[p].getName()))
                            {
                                isExisting = true;
                                product.setUnitOfMeasure("l");
                            }
                        }
                    }
                }
            }
        }

        if (!isExisting)
        {
            cout << "Product name not found! Make sure you enter the name correctly." << endl;
        }
    }

    return product;
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

void clean(Section*& section, vector<Log>& logs)
{
    for (int i = 0; i < MAX_SECTIONS; i++)
    {
        for (int k = 0; k < MAX_SHELVES; k++)
        {
            for (int t = 0; t < MAX_COMPARTMENTS; t++)
            {
                for (int p = 0; p < section[i].getShelves()[k].getCompartments()[t].getProducts().size(); p++)
                {
                    if (!section[i].getShelves()[k].getCompartments()[t].getProducts()[p].isFit(getTodaysDate()))
                    {
                        Product removalProduct = section[i].getShelves()[k].getCompartments()[t].getProducts()[p];
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
        for (int k = 0; k < MAX_SHELVES; k+=SCOPE_OF_PRODUCT)
        {
            rearrangingProducts(section, logs, i, k);
        }
    }
}

void getLogsFromFile(string filePath, vector<string>& lines, Date startDate, Date endDate)
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
        cout << "There is still no data inserted!" << endl;
        inputFileStream.close();
    }
    else
    {
        cout << "Enter the start and end dates of the period from which you want to receive information!" << endl;
        Date startDate = readDateFromInput("From: ");
        Date endDate = readDateFromInput("To: ");

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
            cout << "No actions have been taken during this period!" << endl;
        }
    }
}

void calculateLosses(string filePath)
{
    ifstream inputFileStream;
    inputFileStream.open(filePath, ios::in);
    if (inputFileStream.is_open() && inputFileStream.peek() == ifstream::traits_type::eof())
    {
        cout << "There is still no data inserted!" << endl;
        inputFileStream.close();
    }
    else
    {
        cout << "Enter the start and end dates of the period from which you want to receive information about the losses!" << endl;
        string name = readNameFromInput();

        float price;
        string priceString;
        while (1)
        {
            cout << "Price(BGN) per 1kg(l): ";
            getline(cin, priceString);
            if (priceString.size() > 0)
            {
                if (priceString[0] == '-')
                {
                    cout << "The price must be a positive number." << endl;
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
                            cout << "The program works with prices limited to the second decimal places!" << endl;
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
                            cout << "You have entered an invalid number entry!" << endl;
                        }
                    }
                }
                else
                {
                    cout << "You have entered an invalid number entry!" << endl;
                }
            }
            else
            {
                cout << "You have not entered a price!" << endl;
            }
        }

        Date startDate = readDateFromInput("From: ");
        Date endDate = readDateFromInput("To: ");

        vector<string> lines;
        getLogsFromFile(filePath, lines, startDate, endDate);
        int indexCleared = 0;
        int indexName = 0;
        float discardedQuantity = 0;
        for (int i = 0; i < lines.size(); i++)
        {
            indexCleared = lines[i].find("cleared");
            indexName = lines[i].find(name);
            if (indexCleared != -1 && indexName != -1 && (lines[i].find("of") + 9 + name.size()) == indexCleared)  // potatoes vs red potatoes...допълнителна проверка, за да не стават грешки в изчисленията
            {
                int indexUnitOfMeasure = lines[i].find("kg");
                if (indexUnitOfMeasure == -1)
                {
                    indexUnitOfMeasure = lines[i].find("l");
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
            cout << "No losses were incurred during this period!" << endl;
        }
    }
}

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

void addCommand(Section*& sectionKG, Section*& sectionL, vector<Log>& logs)
{
    Product product = readProductFromInput();
    if (compareChars(product.getUnitOfMeasure(), "kg"))
    {
        addProduct(product, sectionKG, logs, "add");
    }
    else
    {
        addProduct(product, sectionL, logs, "add");
    }
}

void removeCommand(Section*& sectionKG, Section*& sectionL, vector<Log>& logs)
{
    Product product = readAndFindWhereIsProduct(sectionKG, sectionL);

    if (compareChars(product.getUnitOfMeasure(), "kg"))
    {
        removeProduct(product, sectionKG, logs);
    }
    else
    {
        removeProduct(product, sectionL, logs);
    }
}

void cleanCommand(Section*& sectionKG, Section*& sectionL, vector<Log>& logs)
{
    int sizeCurrentLogs = logs.size();
    clean(sectionKG, logs);
    clean(sectionL, logs);
    if (sizeCurrentLogs < logs.size())
    {
        cout << "Successful clearing and rearranging!" << endl;
    }
    else
    {
        cout << "There are still no products that need to be cleared from the storage." << endl;
    }
}

void closeCommand(Section*& sectionKG, Section*& sectionL, string filePathStorage) 
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
    cout << "Successfully closed " << filePathStorage << "!" << endl;
}

void openCommand(string filePathStorage, vector<string> lines, vector<Product> products, Section*& sectionKG, Section*& sectionL)
{
    vector<Product> productsKG;
    vector<Product> productsL;

    getLinesFromFile(filePathStorage, lines);
    readProductsFromFile(products, lines);

    for (int i = 0; i < products.size(); i++)
    {
        if (compareChars(products[i].getUnitOfMeasure(), "kg"))
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

void helpCommand()
{
    cout << "The following commands are supported:" << endl;
    cout << "open <file>        opens <file>" << endl;
    cout << "close              closes currently opened file" << endl;
    cout << "save               saves the currently open file" << endl;
    cout << "saveas <file>      saves the currently open file in <file>" << endl;
    cout << "help               prints this information" << endl;
    cout << "exit               exists the program" << '\n' << endl;

    cout << "The commands that are presented below, after entering them, you will receive additional information about what exactly they require" << endl;
    cout << "add               adds a new product to the warehouse" << endl;
    cout << "remove            removes product from Storage" << endl;
    cout << "print             prints information about availability in Storage" << endl;
    cout << "clean             removes products that have expired or are about to expire" << endl;
    cout << "log               displays information about the activities in the storage for a given period" << endl;
    cout << "losses            calculates the losses for a given period" << endl;
}

int main()
{
    string filePathStorage;
    string filePathLogs = "Logs.txt";
    vector<Log> logs;
    vector<string> lines;
    vector<Product> products;
    Section* sectionKG = new Section[MAX_SECTIONS];
    Section* sectionL = new Section[MAX_SECTIONS];


    cout << "Enter the operation you want to perform." << endl;
    cout << "The options regarding working with files are: open, close, save, save as, help and exit." << endl;
    cout << "Storage options: add, remove, log, clean, losses." << endl;
    bool storageIsOpen = false;
    string command;
    while (1)
    {
        cout << "Command: ";
        getline(cin, command);

        if (command.size() > 0)
        {
            if (command == "add" && storageIsOpen)
            {
                addCommand(sectionKG, sectionL, logs);
            }

            if (command == "remove" && storageIsOpen)
            {
                removeCommand(sectionKG, sectionL, logs);
            }

            if (command == "log" && storageIsOpen)
            {
                showLogs(filePathLogs);
            }

            if (command == "clean" && storageIsOpen)
            {
                cleanCommand(sectionKG, sectionL, logs);
            }

            if (command == "losses" && storageIsOpen)
            {
                calculateLosses(filePathLogs);
            }

            if (command == "print" && storageIsOpen)
            {
                if (checkIfStorageIsEmpty(sectionKG, sectionL))
                {
                    cout << "There are no loaded products in the storage yet!" << endl;
                }
                else
                {
                    print(sectionKG);
                    print(sectionL);
                }
            }

            if (command == "close" && !storageIsOpen)
            {
                cout << "To execute this command, you must first open the file!" << endl;
            }

            if (command == "close" && storageIsOpen)
            {
                storageIsOpen = false;
                products.clear();
                logs.clear();
                lines.clear();

                closeCommand(sectionKG, sectionL, filePathStorage);
            }

            if (command == "save")
            {
                completeLogFile(filePathLogs, logs);
                logs.clear();
                overwriteFile(filePathStorage, sectionKG, sectionL);
            }
            if (command.substr(0, 7) == "save as" && command.size() > 9)
            {
                string newFilePathStorage = command.substr(8);
                getLinesFromFile(newFilePathStorage, lines);
                overwriteFile(newFilePathStorage, sectionKG, sectionL);
            }
            else if (command.substr(0, 7) == "save as")
            {
                cout << "You forgot to enter a path!" << endl;
            }

            if ((command == "add" || command == "remove" || command == "log" || command == "clean" || command == "print" 
                || command == "save" || command.substr(0, 7) == "save as" || command == "losses") && !storageIsOpen)
            {
                cout << "To execute this command, you must first open the file!" << endl;
            }

            if (command.substr(0, 4) == "open" && command.size() > 6)
            {
                filePathStorage = command.substr(5);
                storageIsOpen = true;

                openCommand(filePathStorage, lines, products, sectionKG, sectionL);
            }
            else if (command.substr(0, 4) == "open")
            {
                cout << "You forgot to enter a path!" << endl;
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
                && command != "save" && command.substr(0, 7) != "save as" && command != "help" && command != "exit" && command.substr(0, 4) != "open")
            {
                cout << "This command is not recognized, please make sure you have entered the command correctly!" << endl;
            }
        }
        else
        {
            cout << "You have not entered a command!" << endl;
        }
    }
}