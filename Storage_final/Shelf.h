#pragma once
#include "Compartment.h"

const unsigned short int MAX_COMPARTMENTS = 4;                                              ///Максимален брой отделения на един рафт.

/**
    Клас Shelf, който служи за имплементация на рафт в секцията и съответно съдържа масив от отделения.
*/
class Shelf {
private:
    Compartment* compartments;                                                              ///Динамичен масив от отделения.

    void copy(const Shelf& shelf)                                                           ///Функция, която копира стойностите на подадения обект.
    {
        this->compartments = new Compartment[MAX_COMPARTMENTS];
        for (int i = 0; i < MAX_COMPARTMENTS; i++)
        {
            this->compartments[i] = shelf.compartments[i];
        }
    }

    void erase()                                                                            ///Освобождава динамично заделената памет от масива.
    {
        delete[] this->compartments;
    }
public:
    Shelf();                                                                                ///Конструктор по подразбиране.
    Shelf(const Shelf&);                                                                    ///Копиращ конструктор.
    Shelf& operator=(const Shelf&);                                                         ///Предефиниране на оператор за присвояване =
    ~Shelf();                                                                               ///Деструктор

    Compartment*& getCompartments();
};

/**
    Конструктор по подразбиране за класа Shelf.
    Създаваме масив от отделения по подразбиране.
*/
Shelf::Shelf() {
    this->compartments = new Compartment[MAX_COMPARTMENTS];
}

/**
    Копиращ конструктор за класа Shelf.
    Прилагаме функцията copy върху обекта.
*/
Shelf::Shelf(const Shelf& shelf) {
    this->copy(shelf);
}

/**
    Предефиниране на оператор за присвояване =
    @param[in] shelf е обектът, който ще присвояваме.
    @return Връща текущия обект, върху който е приложен оператора =
*/
Shelf& Shelf::operator=(const Shelf& shelf) {
    if (this != &shelf)
    {
        this->erase();
        this->copy(shelf);
    }
    return *this;
}

/**
    Деструктор, който освобождава динамично заделената памет след приключване на работа с обектът.
*/
Shelf::~Shelf() {
    this->erase();
}

Compartment*& Shelf::getCompartments() {
    return this->compartments;
}