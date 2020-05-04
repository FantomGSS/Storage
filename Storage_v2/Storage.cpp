#include <iostream>
#include <ctime>
#include "Section.h"

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

bool checkUnitOfMeasure(char* unitOfMeasure) 
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

int main()
{
    unsigned short int abc[3] = { 1, 2, 3 };
    Product productOne = Product("ABC", Date(10, 05, 2020), Date(10, 03, 2020), "TEK", "kg", 20, abc, "QWERTY");
    Product productTwo = Product("SAD", Date(10, 05, 2020), Date(10, 04, 2020), "TEK", "l", 20, abc, "QWERTY");
    Product productThree = Product("TAB", Date(10, 05, 2020), Date(10, 03, 2020), "TEK", "kg", 20, abc, "QWERTY");
    cout << productOne << endl;
    cout << productTwo << endl;

    if (productOne == productTwo) cout << true << endl;
    else cout << false << endl;
    
    Section section = Section();
    section.getShelves()[0].getCompartments()[0].addProduct(productOne);
    section.getShelves()[0].getCompartments()[0].addProduct(productTwo);
    section.getShelves()[0].getCompartments()[0].addProduct(productThree);
    cout << section.getShelves()[0].getCompartments()[0].getProducts()[0] << endl;
    cout << section.getShelves()[0].getCompartments()[0].getProducts()[1] << endl;
    cout << section.getShelves()[0].getCompartments()[0].getProducts()[2] << endl;


    section.getShelves()[0].getCompartments()[0].removeProduct(productOne);
    section.getShelves()[0].getCompartments()[0].removeProduct(productThree);
    cout << section.getShelves()[0].getCompartments()[0].getProducts()[0] << endl;

    section.getShelves()[0].getCompartments()[0].getProducts()[0].reduceQuantity(20);
    cout << section.getShelves()[0].getCompartments()[0].getProducts()[0] << endl;
    section.getShelves()[0].getCompartments()[0].reduceCapacity(20);
    cout << section.getShelves()[0].getCompartments()[0].getCapacity() << endl;
}