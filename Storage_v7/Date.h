#pragma once
#include<iostream>
#include<iomanip>
using namespace std;

class Date {
private:
    unsigned short int day;
    unsigned short int month;
    unsigned short int year;

    void copy(const Date& date)
    {
        this->day = date.day;
        this->month = date.month;
        this->year = date.year;
    }

public:
    Date();
    Date(unsigned short int, unsigned short int, unsigned short int);
    Date(const Date&);
    Date& operator=(const Date&);
    inline bool operator==(const Date&);

    const unsigned short int getDay() const;
    const unsigned short int getMonth() const;
    const unsigned short int getYear() const;
    const string getStringDate();

    friend ostream& operator<<(std::ostream&, const Date&);
};

Date::Date() {
    this->day = 1;
    this->month = 1;
    this->year = 2000;
}

Date::Date(unsigned short int day, unsigned short int month, unsigned short int year) {
    this->day = day;
    this->month = month;
    this->year = year;
}

Date::Date(const Date& date) {
    this->copy(date);
}

Date& Date::operator=(const Date& date) {
    if (this != &date)
    {
        this->copy(date);
    }
    return *this;
}

inline bool Date::operator==(const Date& date) {
    if (this->day == date.day && this->month == date.month && this->year == date.year)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

const unsigned short int Date::getDay() const {
    return this->day;
}

const unsigned short int Date::getMonth() const {
    return this->month;
}

const unsigned short int Date::getYear() const {
    return this->year;
}

const string Date::getStringDate() {
    string date = "";
    if (to_string(this->day).size() == 1)
    {
        date.append(to_string(0));
        date.append(to_string(this->day));
    }
    else
    {
        date.append(to_string(this->day));
    }

    date.append(".");

    if (to_string(this->month).size() == 1)
    {
        date.append(to_string(0));
        date.append(to_string(this->month));
    }
    else
    {
        date.append(to_string(this->month));
    }

    date.append(".");
    date.append(to_string(this->year));

    return date;
}

ostream& operator<<(std::ostream& output, const Date& date)
{
    output << date.year << "-" << setw(2) << setfill('0') << date.month << "-" << setw(2) << setfill('0') << date.day;
    return output;
}