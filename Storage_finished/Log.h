#pragma once
#include <iostream>
#include "Date.h"
#include "Product.h"
using namespace std;

class Log {
private:
    Date date;
    char* command;
    Product product;

    void copy(const Log& log)
    {
        this->date = log.date;

        this->command = new char[strLength(log.command) + 1];
        strcpy_s(this->command, strLength(log.command) + 1, log.command);

        this->product = log.product;
    }

    void erase()
    {
        delete[] this->command;
    }

public:
    Log();
    Log(Date, const char*, Product);
    Log(const Log&);
    Log& operator=(const Log&);
    ~Log();

    friend ostream& operator<<(ostream&, const Log&);
};

Log::Log() {
    this->date = Date();
    this->command = nullptr;
    this->product = Product();
}

Log::Log(Date date, const char* command, Product product) {
    this->date = date;

    this->command = new char[strLength(command) + 1];
    strcpy_s(this->command, strLength(command) + 1, command);

    this->product = product;
}

Log::Log(const Log& log) {
    this->copy(log);
}

Log& Log::operator=(const Log& log) {
    if (this != &log) {
        this->erase();
        this->copy(log);
    }
    return *this;
}

Log::~Log() {
    this->erase();
}

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