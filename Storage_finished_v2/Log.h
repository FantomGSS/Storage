#pragma once
#include <iostream>
#include "Date.h"
#include "Product.h"
using namespace std;

/**
    Клас Log, който служи за имплементация на запис на промяна в наличността на склада и съответно съдържа дата и информация за промяната.
*/
class Log {
private:
    Date date;                                                                                 ///Датата, в която е извършена промяната в наличността.
    char* command;                                                                             ///Символен низ, показващ каква точно промяна е извършена.
    Product product;                                                                           ///Продукт, чиято наличност е променена.

    void copy(const Log& log)                                                                  ///Функция, която копира стойностите на подадения обект.
    {
        this->date = log.date;

        this->command = new char[strLength(log.command) + 1];
        strcpy_s(this->command, strLength(log.command) + 1, log.command);

        this->product = log.product;
    }

    void erase()                                                                               ///Освобождава динамично заделената памет от символния низ.
    {
        delete[] this->command;
    }

public:
    Log();                                                                                     ///Конструктор по подразбиране.
    Log(Date, const char*, Product&);                                                          ///Конструктор с параметри.
    Log(const Log&);                                                                           ///Копиращ конструктор.
    Log& operator=(const Log&);                                                                ///Предефиниране на оператор за присвояване =
    ~Log();                                                                                    ///Деструктор

    friend ostream& operator<<(ostream&, const Log&);                                          ///Предефиниране на оператор за вмъкване <<
};

/**
    Конструктор по подразбиране за класа Log.
    Датата и продуктът с техните стойности по подразбиране, а командата - празен символен низ.
*/
Log::Log() {
    this->date = Date();
    this->command = nullptr;
    this->product = Product();
}

/**
    Конструктор с параметри за класа Log.
    По подадени дата, команда и продукт.
*/
Log::Log(Date date, const char* command, Product& product) {
    this->date = date;

    this->command = new char[strLength(command) + 1];
    strcpy_s(this->command, strLength(command) + 1, command);

    this->product = product;
}

/**
    Копиращ конструктор за класа Log.
    Прилагаме функцията copy върху обекта.
*/
Log::Log(const Log& log) {
    this->copy(log);
}

/**
    Предефиниране на оператор за присвояване =
    @param[in] log е обектът, който ще присвояваме.
    @return Връща текущия обект, върху който е приложен оператора =
*/
Log& Log::operator=(const Log& log) {
    if (this != &log) {                                                                        ///Ако сравняваме обекти с еднакви адреси, следователно сравняваме еднакви обекти => няма нужда от копиране.
        this->erase();
        this->copy(log);
    }
    return *this;
}

/**
    Деструктор, който освобождава динамично заделената памет след приключване на работа с обектът.
*/
Log::~Log() {
    this->erase();
}

/**
    Предефиниране на оператора << за стандартния изходен поток.
    @param[in, out] output е потокът, върху който е приложен <<
    @param[in] log е обектът, който седи от дясно на оператора.
    @return Връща потока подаден на функцията.
*/
ostream& operator<<(ostream& output, const Log& log)
{
    if (compareChars(log.command, "add"))
    {
        if (log.product.getQuantity() == 1)
        {
            output << log.date << " - " << log.product.getQuantity() << log.product.getUnitOfMeasure() << " of " << log.product.getName() << " was added to the storage." << endl;
        }
        else
        {
            output << log.date << " - " << log.product.getQuantity() << log.product.getUnitOfMeasure() << " of " << log.product.getName() << " were added to the storage." << endl;
        }
    }
    else if (compareChars(log.command, "remove"))
    {
        if (log.product.getQuantity() == 1)
        {
            output << log.date << " - " << log.product.getQuantity() << log.product.getUnitOfMeasure() << " of " << log.product.getName() << " was removed from the storage." << endl;
        }
        else
        {
            output << log.date << " - " << log.product.getQuantity() << log.product.getUnitOfMeasure() << " of " << log.product.getName() << " were removed from the storage." << endl;
        }
    }
    else if (compareChars(log.command, "clean"))
    {
        if (log.product.getQuantity() == 1)
        {
            output << log.date << " - " << log.product.getQuantity() << log.product.getUnitOfMeasure() << " of " << log.product.getName() << " was cleared from the storage, because its expiration date has expired or will expire soon!" << endl;
        }
        else
        {
            output << log.date << " - " << log.product.getQuantity() << log.product.getUnitOfMeasure() << " of " << log.product.getName() << " were cleared from the storage, because its expiration date has expired or will expire soon!" << endl;
        }
    }
    else
    {
        output << "Error!!!" << endl;
    }
    return output;
}