#include <iostream>
#include <ctime>
#include "Product.h"

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
    Date todayDate = getTodaysDate();
    cout << todayDate << endl;

    Date dateOne = Date(28,02,2021);
    Date dateTwo = Date(19, 04, 2019);
    unsigned short int abc[3] = { 1,2,3 };
    Product product = Product("ABC", dateOne, dateTwo, "HAHAHAHA", "Litri", 23, abc, "Nz kvo e tva");
    cout << product << endl;
    cout << product.isFit(todayDate);
}