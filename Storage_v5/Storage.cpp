#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include "Section.h"
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

    Product product(name.c_str(), expiryDate, dateOfReceipt, manufacturersName.c_str(), unitOfMeasure.c_str(), quantity, comment.c_str());
    return product;
}

struct Position
{
    unsigned short int sect;
    unsigned short int shelf;
    unsigned short int comp;

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

void separation(Product& product, Section*& section, bool& productSuccessfullyAdded, unsigned short int indexSection, int k, int t, unsigned short int freeQuantity)
{
    Product newProduct = product;
    newProduct.setQuantity(freeQuantity);
    unsigned short int position[3] = { indexSection + 1, k + 1, t + 1 };
    newProduct.setPosition(position);
    section[indexSection].getShelves()[k].getCompartments()[t].addProduct(newProduct);
    product.setQuantity(product.getQuantity() - freeQuantity);
}

const unsigned short int getOccupiedQuantity(Product product, Section* section, unsigned short int indexSection, unsigned short int startingShelf)
{
    unsigned short int occupiedQuantity = 0;
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

void storeInSeparateCompartment(Product& product, Section*& section, bool& productSuccessfullyAdded, unsigned short int indexSection, unsigned short int startingShelf)
{
    for (int k = startingShelf; k < startingShelf + SCOPE_OF_PRODUCT; k++)
    {
        for (int t = 0; t < MAX_COMPARTMENTS && !productSuccessfullyAdded; t++)
        {
            unsigned short int occupiedQuantity = section[indexSection].getShelves()[k].getCompartments()[t].getCapacity();
            if (occupiedQuantity == 00)
            {
                if (section[indexSection].getShelves()[k].getCompartments()[t].isThereEnoughCapacity(product))
                {
                    positioning(product, section, productSuccessfullyAdded, indexSection, k, t);
                }
                else
                {
                    unsigned short int freeQuantity = MAX_CAPACITY - occupiedQuantity;
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
            unsigned short int occupiedQuantity = section[indexSection].getShelves()[k].getCompartments()[t].getCapacity();
            if (occupiedQuantity <= MAX_CAPACITY - 10)
            {
                if (section[indexSection].getShelves()[k].getCompartments()[t].isThereEnoughCapacity(product))
                {
                    positioning(product, section, productSuccessfullyAdded, indexSection, k, t);
                }
                else
                {
                    unsigned short int freeQuantity = MAX_CAPACITY - occupiedQuantity;
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
            unsigned short int occupiedQuantity = section[indexSection].getShelves()[k].getCompartments()[t].getCapacity();
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
                            unsigned short int freeQuantity = MAX_CAPACITY - occupiedQuantity;
                            separation(product, section, productSuccessfullyAdded, indexSection, k, t, freeQuantity);
                        }
                        break;
                    }
                }
            }
        }
    }
}

void addProduct(Product product, Section*& section)
{
    unsigned short int allowedQuantity = MAX_CAPACITY * SCOPE_OF_PRODUCT * MAX_COMPARTMENTS;
    if (product.getQuantity() > allowedQuantity)
    {
        cout << "The product cannot be added because its quantity exceeds the maximum allowed for one product! The allowed quantity is: " << allowedQuantity << product.getUnitOfMeasure() << endl;
        return;
    }

    bool isExisting = false;
    Position positionFirstProduct(0, 0, 0);

    findFirstProduct(isExisting, positionFirstProduct, section, product);

    bool productSuccessfullyAdded = false;
    bool noPlaceFound = false;
    if (isExisting)
    {
        unsigned short int indexSection = positionFirstProduct.sect;
        unsigned short int startingShelf = 0;
        if (positionFirstProduct.shelf % SCOPE_OF_PRODUCT == 1)
        {
            startingShelf = positionFirstProduct.shelf - 1;
        }
        else
        {
            startingShelf = positionFirstProduct.shelf;
        }

        if (product.getQuantity() > allowedQuantity - getOccupiedQuantity(product, section, indexSection, startingShelf))
        {
            cout << "The product cannot be added because its quantity exceeds the maximum allowed for one product! You can only add: ";
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

int main()
{
    const char* filePath = "Products.txt";
    vector<string> lines;
    //getLinesFromFile(filePath, lines);
    vector<Product> products;
    //readProductsFromFile(products, lines);

    //Product product = readProductFromInput();

    Section* section = new Section[MAX_SECTIONS];
    Date today = getTodaysDate();
    Product productOne("potatoes", Date(24, 05, 2020), today, "Kompir", "kg", 22, "HIGH QUALITY POTATOES FROM SAMOKOV SCROLL DOWN");
    Product productTwo("potatoes", Date(24, 05, 2020), today, "Kompir", "kg", 30, "HIGH QUALITY POTATOES FROM SAMOKOV SCROLL DOWN");
    Product productThree("potatoes", Date(26, 05, 2020), today, "Kompir", "kg", 50, "HIGH QUALITY POTATOES FROM SAMOKOV SCROLL DOWN");
    Product productFour("potatoes", Date(24, 05, 2020), today, "Kompir", "kg", 60, "HIGH QUALITY POTATOES FROM SAMOKOV SCROLL DOWN");
    addProduct(productOne, section);
    addProduct(productTwo, section);
    addProduct(productThree, section);
    addProduct(productFour, section);

    addProduct(productOne, section);
    addProduct(productTwo, section);
    addProduct(productThree, section);
    addProduct(productFour, section);

    Product productFive("carrots", Date(20, 05, 2020), today, "AGRO_ALEKSANDRA", "kg", 22, "The sweetest carrots!");
    Product productSix("carrots", Date(21, 05, 2020), today, "AGRO_ALEKSANDRA", "kg", 30, "The sweetest carrots!");
    Product productSeven("carrots", Date(27, 05, 2020), today, "AGRO_ALEKSANDRA", "kg", 50, "The sweetest carrots!");
    Product productEight("carrots", Date(22, 05, 2020), today, "AGRO_ALEKSANDRA", "kg", 600, "The sweetest carrots!");
    addProduct(productFive, section);
    addProduct(productSix, section);
    addProduct(productSeven, section);
    addProduct(productEight, section);

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
}