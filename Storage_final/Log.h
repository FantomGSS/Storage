#pragma once
#include "Date.h"
#include "Product.h"

/**
    �������, ����� �������� ��� �������� ����.
*/
bool compareChars(const char* charsOne, const char* charsTwo)
{
    if (strlen(charsOne) != strlen(charsTwo))
    {
        return 0;
    }

    for (int i = 0; charsOne[i] != '\0'; i++)
    {
        if (charsOne[i] != charsTwo[i])
        {
            return 0;
        }
    }
    return 1;
}

/**
    ���� Log, ����� ����� �� ������������� �� ����� �� ������� � ����������� �� ������ � ��������� ������� ���� � ���������� �� ���������.
*/
class Log {
private:
    Date date;                                                                                 ///������, � ����� � ��������� ��������� � �����������.
    char* command;                                                                             ///�������� ���, �������� ����� ����� ������� � ���������.
    Product product;                                                                           ///�������, ����� ��������� � ���������.

    void copy(const Log& log)                                                                  ///�������, ����� ������ ����������� �� ��������� �����.
    {
        this->date = log.date;

        this->command = new char[strlen(log.command) + 1];
        strcpy_s(this->command, strlen(log.command) + 1, log.command);

        this->product = log.product;
    }

    void erase()                                                                               ///����������� ��������� ���������� ����� �� ��������� ���.
    {
        delete[] this->command;
    }

public:
    Log();                                                                                     ///����������� �� ������������.
    Log(Date, const char*, Product&);                                                          ///����������� � ���������.
    Log(const Log&);                                                                           ///������� �����������.
    Log& operator=(const Log&);                                                                ///������������� �� �������� �� ����������� =
    ~Log();                                                                                    ///����������

    friend ostream& operator<<(ostream&, const Log&);                                          ///������������� �� �������� �� �������� <<
};

/**
    ����������� �� ������������ �� ����� Log.
    ������ � ��������� � ������� ��������� �� ������������, � ��������� - ������ �������� ���.
*/
Log::Log() {
    this->date = Date();
    this->command = nullptr;
    this->product = Product();
}

/**
    ����������� � ��������� �� ����� Log.
    �� �������� ����, ������� � �������.
*/
Log::Log(Date date, const char* command, Product& product) {
    this->date = date;

    this->command = new char[strlen(command) + 1];
    strcpy_s(this->command, strlen(command) + 1, command);

    this->product = product;
}

/**
    ������� ����������� �� ����� Log.
    ��������� ��������� copy ����� ������.
*/
Log::Log(const Log& log) {
    this->copy(log);
}

/**
    ������������� �� �������� �� ����������� =
    @param[in] log � �������, ����� �� �����������.
    @return ����� ������� �����, ����� ����� � �������� ��������� =
*/
Log& Log::operator=(const Log& log) {
    if (this != &log) {                                                                        ///��� ���������� ������ � ������� ������, ������������ ���������� ������� ������ => ���� ����� �� ��������.
        this->erase();
        this->copy(log);
    }
    return *this;
}

/**
    ����������, ����� ����������� ��������� ���������� ����� ���� ����������� �� ������ � �������.
*/
Log::~Log() {
    this->erase();
}

/**
    ������������� �� ��������� << �� ����������� ������� �����.
    @param[in, out] output � �������, ����� ����� � �������� <<
    @param[in] log � �������, ����� ���� �� ����� �� ���������.
    @return ����� ������ ������� �� ���������.
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
            output << log.date << " - " << log.product.getQuantity() << log.product.getUnitOfMeasure() << " of " << log.product.getName() << " was cleaned from the storage, because its expiration date has expired or will expire soon!" << endl;
        }
        else
        {
            output << log.date << " - " << log.product.getQuantity() << log.product.getUnitOfMeasure() << " of " << log.product.getName() << " were cleaned from the storage, because its expiration date has expired or will expire soon!" << endl;
        }
    }
    else
    {
        output << "Error!!!" << endl;
    }
    return output;
}