#pragma once
#include<iostream>
#include "Shelf.h"
using namespace std;

const unsigned short int MAX_SHELVES = 6;                                                   ///Максимален брой рафтове в една секция.

/**
    Клас Section, който служи за имплементация на секция в склада и съответно съдържа масив от рафтове.
*/
class Section {
private:
    Shelf* shelves;                                                                         ///Динамичен масив от рафтове.

    void copy(const Section& section)                                                       ///Функция, която копира стойностите на подадения обект.
    {
        this->shelves = new Shelf[MAX_SHELVES];
        for (int i = 0; i < MAX_SHELVES; i++)
        {
            this->shelves[i] = section.shelves[i];
        }
    }

    void erase()                                                                            ///Освобождава динамично заделената памет от масива.
    {
        delete[] this->shelves;
    }
public:
    Section();                                                                              ///Конструктор по подразбиране.
    Section(const Section&);                                                                ///Копиращ конструктор.
    Section& operator=(const Section&);                                                     ///Предефиниране на оператор за присвояване =
    ~Section();                                                                             ///Деструктор

    Shelf*& getShelves();
};

/**
    Конструктор по подразбиране за класа Section.
    Създаваме масив от рафтове по подразбиране.
*/
Section::Section() {
    this->shelves = new Shelf[MAX_SHELVES];
}

/**
    Копиращ конструктор за класа Section.
    Прилагаме функцията copy върху обекта.
*/
Section::Section(const Section& section) {
    this->copy(section);
}

/**
    Предефиниране на оператор за присвояване =
    @param[in] section е обектът, който ще присвояваме.
    @return Връща текущия обект, върху който е приложен оператора =
*/
Section& Section::operator=(const Section& section) {
    if (this != &section)
    {
        this->erase();
        this->copy(section);
    }
    return *this;
}

/**
    Деструктор, който освобождава динамично заделената памет след приключване на работа с обектът.
*/
Section::~Section() {
    this->erase();
}

Shelf*& Section::getShelves() {
    return this->shelves;
}