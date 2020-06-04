#pragma once
#include<iostream>
#include<iomanip>
using namespace std;

/**
    Клас Date, който служи за имплементация на дата и съответно съдържа ден, месец и година.
*/
class Date {
private:
    unsigned short int day;                                                             ///Цяло естествено число за ден.
    unsigned short int month;                                                           ///Цяло естествено число за месец.
    unsigned short int year;                                                            ///Цяло естествено число за година.

    void copy(const Date& date)                                                         ///Функция, която копира стойностите на подадения обект.
    {
        this->day = date.day;
        this->month = date.month;
        this->year = date.year;
    }

public:
    Date();                                                                             ///Конструктор по подразбиране.
    Date(unsigned short int, unsigned short int, unsigned short int);                   ///Конструктор с параметри.
    Date(const Date&);                                                                  ///Копиращ конструктор.
    Date& operator=(const Date&);                                                       ///Предефиниране на оператор за присвояване =
    inline bool operator==(const Date&);                                                ///Предефиниране на оператор за сравнение ==

    const unsigned short int getDay() const;
    const unsigned short int getMonth() const;
    const unsigned short int getYear() const;

    friend ostream& operator<<(std::ostream&, const Date&);                             ///Предефиниране на оператор за вмъкване <<
};

/**
    Конструктор по подразбиране за класа Date.
    Датата се равнява на първия ден от 2000-ната година.
*/
Date::Date() {
    this->day = 1;
    this->month = 1;
    this->year = 2000;
}

/**
    Конструктор с параметри за класа Date.
    По подадени ден, месец, година.
*/
Date::Date(unsigned short int day, unsigned short int month, unsigned short int year) {
    this->day = day;
    this->month = month;
    this->year = year;
}

/**
    Копиращ конструктор за класа Date.
    Прилагаме функцията copy върху обекта.
*/
Date::Date(const Date& date) {
    this->copy(date);
}

/**
    Предефиниране на оператор за присвояване =
    @param[in] date е обектът, който ще присвояваме.
    @return Връща текущия обект, върху който е приложен оператора =
*/
Date& Date::operator=(const Date& date) {
    if (this != &date)                                                                  ///Ако сравняваме обекти с еднакви адреси, следователно сравняваме еднакви обекти => няма нужда от копиране.
    {
        this->copy(date);
    }
    return *this;
}

/**
    Предефиниране на оператор за сравнение ==
    @param[in] date е обектът, който ще проверяваме за съвпадение.
    @return Връща стойност за истинност, в зависимост дали текущата датата е равна на подадената.
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
    Предефиниране на оператора << за стандартния изходен поток.
    @param[in, out] output е потокът, върху който е приложен <<
    @param[in] date е обектът, който седи от дясно на оператора.
    @return Връща потока подаден на функцията.
*/
ostream& operator<<(ostream& output, const Date& date)
{
    output << date.year << "-" << setw(2) << setfill('0') << date.month << "-" << setw(2) << setfill('0') << date.day;
    return output;
}