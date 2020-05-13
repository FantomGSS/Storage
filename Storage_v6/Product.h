#pragma once
#include<iostream>
#include <ctime>
#include "Date.h"
using namespace std;

int strLength(const char* str)
{
    int i = -1;
    while (str[++i]);
    return i;
}

bool compareChars(const char* charsOne, const char* charsTwo)
{
    if (strLength(charsOne) != strLength(charsTwo))
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

class Product {
private:
    char* name;
    Date expiryDate;
    Date dateOfReceipt;
    char* manufacturersName;
    char* unitOfMeasure;
    float quantity;
    unsigned short int* position;
    char* comment;

    void copy(const Product& product)
    {
        this->name = new char[strLength(product.name) + 1];
        strcpy_s(this->name, strLength(product.name) + 1, product.name);

        this->expiryDate = product.expiryDate;
        this->dateOfReceipt = product.dateOfReceipt;

        this->manufacturersName = new char[strLength(product.manufacturersName) + 1];
        strcpy_s(this->manufacturersName, strLength(product.manufacturersName) + 1, product.manufacturersName);

        this->unitOfMeasure = new char[strLength(product.unitOfMeasure) + 1];
        strcpy_s(this->unitOfMeasure, strLength(product.unitOfMeasure) + 1, product.unitOfMeasure);

        this->quantity = product.quantity;
        this->position = new unsigned short int[3];
        for (int i = 0; i < 3; i++)
        {
            this->position[i] = product.position[i];
        }

        this->comment = new char[strLength(product.comment) + 1];
        strcpy_s(this->comment, strLength(product.comment) + 1, product.comment);
    }

    void erase()
    {
        delete[] this->name;
        delete[] this->manufacturersName;
        delete[] this->unitOfMeasure;
        delete[] this->comment;
    }

public:
    Product();
    Product(const char*, Date, Date, const char*, const char*, float, const char*);
    Product(const Product&);
    Product& operator=(const Product&);
    inline bool operator==(const Product&);
    ~Product();

    void setName(const char*);
    void setExpiryDate(Date);
    void setDateOfReceipt(Date);
    void setManufacturersName(const char*);
    void setUnitOfMeasure(const char*);
    void setQuantity(const float);
    void setPosition(unsigned short int*);
    void setComment(const char*);

    const char* getName() const;
    const Date getExpiryDate() const;
    const Date getDateOfReceipt() const;
    const char* getManufacturersName() const;
    const char* getUnitOfMeasure() const;
    const float getQuantity() const;
    const unsigned short int* getPosition() const;
    const char* getComment() const;

    const bool isFit(Date date);

    friend ostream& operator<<(std::ostream&, const Product&);
};

Product::Product() {
    this->name = nullptr;
    this->expiryDate = Date();
    this->dateOfReceipt = Date();
    this->manufacturersName = nullptr;
    this->unitOfMeasure = nullptr;
    this->quantity = 0;
    this->position = new unsigned short int[3];
    for (int i = 0; i < 3; i++)
    {
        this->position[i] = 0;
    }
    this->comment = nullptr;
}

Product::Product(const char* name, Date expiryDate, Date dateOfReceipt, const char* manufacturersName, 
                 const char* unitOfMeasure, float quantity, const char* comment) {
    this->name = new char[strLength(name) + 1];
    strcpy_s(this->name, strLength(name) + 1, name);

    this->expiryDate = expiryDate;
    this->dateOfReceipt = dateOfReceipt;

    this->manufacturersName = new char[strLength(manufacturersName) + 1];
    strcpy_s(this->manufacturersName, strLength(manufacturersName) + 1, manufacturersName);

    this->unitOfMeasure = new char[strLength(unitOfMeasure) + 1];
    strcpy_s(this->unitOfMeasure, strLength(unitOfMeasure) + 1, unitOfMeasure);

    this->quantity = quantity;
    this->position = new unsigned short int[3];
    for (int i = 0; i < 3; i++)
    {
        this->position[i] = 0;
    }

    this->comment = new char[strLength(comment) + 1];
    strcpy_s(this->comment, strLength(comment) + 1, comment);
}

Product::Product(const Product& product) {
    this->copy(product);
}

Product& Product::operator=(const Product& product) {
    if (this != &product) {
        this->erase();
        this->copy(product);
    }
    return *this;
}

inline bool Product::operator==(const Product& product) {
    if (compareChars(this->name, product.name) && this->expiryDate == product.expiryDate && this->dateOfReceipt == product.dateOfReceipt
        && compareChars(this->manufacturersName, product.manufacturersName) && compareChars(this->unitOfMeasure, product.unitOfMeasure)
        && this->quantity == product.quantity && compareChars(this->comment, product.comment))
    {
        if (this->position[0] == product.position[0] && this->position[1] == product.position[1] && this->position[2] == product.position[2])
        {
            return 1;
        }
        else 
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }
}

Product::~Product() {
    this->erase();
}

void Product::setName(const char* name) {
    delete[] this->name;
    this->name = new char[strLength(name) + 1];
    strcpy_s(this->name, strLength(name) + 1, name);
}

void Product::setExpiryDate(Date expiryDate) {
    this->expiryDate = expiryDate;
}

void Product::setDateOfReceipt(Date dateOfReceipt) {
    this->dateOfReceipt = dateOfReceipt;
}

void Product::setManufacturersName(const char* manufacturersName) {
    delete[] this->manufacturersName;
    this->manufacturersName = new char[strLength(manufacturersName) + 1];
    strcpy_s(this->manufacturersName, strLength(manufacturersName) + 1, manufacturersName);
}

void Product::setUnitOfMeasure(const char* unitOfMeasure) {
    delete[] this->unitOfMeasure;
    this->unitOfMeasure = new char[strLength(unitOfMeasure) + 1];
    strcpy_s(this->unitOfMeasure, strLength(unitOfMeasure) + 1, unitOfMeasure);
}

void Product::setQuantity(const float quantity) {
    this->quantity = quantity;
}

void Product::setPosition(unsigned short int* position) {
    this->position = new unsigned short int[3];
    for (int i = 0; i < 3; i++)
    {
        this->position[i] = position[i];
    }
}

void Product::setComment(const char* comment) {
    delete[] this->comment;
    this->comment = new char[strLength(comment) + 1];
    strcpy_s(this->comment, strLength(comment) + 1, comment);
}

const char* Product::getName() const {
    return this->name;
}

const Date Product::getExpiryDate() const {
    return this->expiryDate;
}

const Date Product::getDateOfReceipt() const {
    return this->dateOfReceipt;
}

const char* Product::getManufacturersName() const {
    return this->manufacturersName;
}

const char* Product::getUnitOfMeasure() const {
    return this->unitOfMeasure;
}

const float Product::getQuantity() const {
    return this->quantity;
}

const unsigned short int* Product::getPosition() const {
    return this->position;
}

const char* Product::getComment() const {
    return this->comment;
}

const bool Product::isFit(Date date) {
    if (this->expiryDate.getYear() != date.getYear())
    {
        return this->expiryDate.getYear() > date.getYear();
    }
    else
    {
        if (this->expiryDate.getMonth() != date.getMonth())
        {
            return this->expiryDate.getMonth() > date.getMonth();
        }
        else
        {
            if (this->expiryDate.getDay() != date.getDay())
            {
                return this->expiryDate.getDay() > date.getDay();
            }
            else
            {
                return 0;
            }
        }
    }
}

ostream& operator<<(std::ostream& output, const Product& product)
{
    output << "Name: " << product.name << endl;
    output << "Expiry Date: " << product.expiryDate << endl;
    output << "Date of Receipt: " << product.dateOfReceipt << endl;
    output << "Manufacturer's Name: " << product.manufacturersName << endl;
    output << "Unit of Measure: " << product.unitOfMeasure << endl;
    output << "Quantity: " << product.quantity << endl;
    output << "Position: " << product.position[0] << "/" << product.position[1] << "/" << product.position[2] << endl;
    output << "Comment: " << product.comment << endl;
    return output;
}

