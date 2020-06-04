#pragma once
#include<iostream>
#include<iomanip>
using namespace std;

/**
    ���� Date, ����� ����� �� ������������� �� ���� � ��������� ������� ���, ����� � ������.
*/
class Date {
private:
    unsigned short int day;                                                             ///���� ���������� ����� �� ���.
    unsigned short int month;                                                           ///���� ���������� ����� �� �����.
    unsigned short int year;                                                            ///���� ���������� ����� �� ������.

    void copy(const Date& date)                                                         ///�������, ����� ������ ����������� �� ��������� �����.
    {
        this->day = date.day;
        this->month = date.month;
        this->year = date.year;
    }

public:
    Date();                                                                             ///����������� �� ������������.
    Date(unsigned short int, unsigned short int, unsigned short int);                   ///����������� � ���������.
    Date(const Date&);                                                                  ///������� �����������.
    Date& operator=(const Date&);                                                       ///������������� �� �������� �� ����������� =
    inline bool operator==(const Date&);                                                ///������������� �� �������� �� ��������� ==

    const unsigned short int getDay() const;
    const unsigned short int getMonth() const;
    const unsigned short int getYear() const;

    friend ostream& operator<<(std::ostream&, const Date&);                             ///������������� �� �������� �� �������� <<
};

/**
    ����������� �� ������������ �� ����� Date.
    ������ �� ������� �� ������ ��� �� 2000-���� ������.
*/
Date::Date() {
    this->day = 1;
    this->month = 1;
    this->year = 2000;
}

/**
    ����������� � ��������� �� ����� Date.
    �� �������� ���, �����, ������.
*/
Date::Date(unsigned short int day, unsigned short int month, unsigned short int year) {
    this->day = day;
    this->month = month;
    this->year = year;
}

/**
    ������� ����������� �� ����� Date.
    ��������� ��������� copy ����� ������.
*/
Date::Date(const Date& date) {
    this->copy(date);
}

/**
    ������������� �� �������� �� ����������� =
    @param[in] date � �������, ����� �� �����������.
    @return ����� ������� �����, ����� ����� � �������� ��������� =
*/
Date& Date::operator=(const Date& date) {
    if (this != &date)                                                                  ///��� ���������� ������ � ������� ������, ������������ ���������� ������� ������ => ���� ����� �� ��������.
    {
        this->copy(date);
    }
    return *this;
}

/**
    ������������� �� �������� �� ��������� ==
    @param[in] date � �������, ����� �� ����������� �� ����������.
    @return ����� �������� �� ���������, � ���������� ���� �������� ������ � ����� �� ����������.
*/
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

/**
    ������������� �� ��������� << �� ����������� ������� �����.
    @param[in, out] output � �������, ����� ����� � �������� <<
    @param[in] date � �������, ����� ���� �� ����� �� ���������.
    @return ����� ������ ������� �� ���������.
*/
ostream& operator<<(ostream& output, const Date& date)
{
    output << date.year << "-" << setw(2) << setfill('0') << date.month << "-" << setw(2) << setfill('0') << date.day;
    return output;
}