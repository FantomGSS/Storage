#pragma once
#include "Date.h"

/**
    ���� Product, ����� ����� �� ������������� �� ������� � ��������� ������� ���������� �� ��������.
*/
class Product {
private:
    string name;                                                                         ///�������� ���, �������� ����� �� ��������.
    Date expiryDate;                                                                     ///����, ����� ������������ ����� �� ������� �� ��������.
    Date dateOfReceipt;                                                                  ///����, ����� ������������ ����, � ����� ��������� �� ������� � ������.
    string manufacturersName;                                                            ///�������� ���, �������� ����� �� �������������.
    string unitOfMeasure;                                                                ///�������� ���, ������������� ������� ������� �� ��������.
    float quantity;                                                                      ///������ �����, �������������� ������������ �� ��������
    unsigned short int* position;                                                        ///����� �� ���� ���������� �����, ����� ������� ���� �� ������ �������� - ������, ����, ���������.
    string comment;                                                                      ///�������������� �������� ���, ������������� �������� �� ��������.

    void copy(const Product& product)                                                    ///�������, ����� ������ ����������� �� ��������� �����.
    {
        this->name = product.name;
        this->expiryDate = product.expiryDate;
        this->dateOfReceipt = product.dateOfReceipt;
        this->manufacturersName = product.manufacturersName;
        this->unitOfMeasure = product.unitOfMeasure;
        this->quantity = product.quantity;
        this->position = new unsigned short int[3];
        for (int i = 0; i < 3; i++)
        {
            this->position[i] = product.position[i];
        }
        this->comment = product.comment;
    }

public:
    Product();                                                                           ///����������� �� ������������.
    Product(string, Date&, Date&, string, 
            string, float, string);                                                      ///����������� � ���������.
    Product(const Product&);                                                             ///������� �����������.
    Product& operator=(const Product&);                                                  ///������������� �� �������� �� ����������� =
    inline bool operator==(const Product&);                                              ///������������� �� �������� �� ��������� ==

    void setName(string);
    void setExpiryDate(Date);
    void setDateOfReceipt(Date);
    void setManufacturersName(string);
    void setUnitOfMeasure(string);
    void setQuantity(const float);
    void setPosition(unsigned short int*);
    void setComment(string);

    const string getName() const;
    const Date getExpiryDate() const;
    const Date getDateOfReceipt() const;
    const string getManufacturersName() const;
    const string getUnitOfMeasure() const;
    const float getQuantity() const;
    const unsigned short int* getPosition() const;
    const string getComment() const;
    
    const string getPositionString();                                                    ///�������, ����� ����������� ��������� �� �������� (������) � �������� ���.
    const bool isFit(Date& date);                                                        ///�������, ����� ��������� ���� ����� �� ������� �� ������� ������� � ������� ��� �������� ����� �� ������.

    friend ostream& operator<<(std::ostream&, const Product&);                           ///������������� �� �������� �� �������� <<
};

/**
    ����������� �� ������������ �� ����� Product.
    ������ � ������� ��������� �� ������������, � �������, ������� ������� � ��������� - ������ �������� ������.
    ��������� ������ ������ ��������� �� ������, ���� � ���������, ����� � ������������.
*/
Product::Product() {
    this->name = "";
    this->expiryDate = Date();
    this->dateOfReceipt = Date();
    this->manufacturersName = "";
    this->unitOfMeasure = "";
    this->quantity = 0;
    this->position = new unsigned short int[3];
    for (int i = 0; i < 3; i++)
    {
        this->position[i] = 0;
    }
    this->comment = "";
}

/**
    ����������� � ��������� �� ����� Product.
    �� �������� ��� �� ��������, ���� �� �������, ���� �� ���������, ��� �� ������������, ����� �������, ���������� � ��������.
*/
Product::Product(string name, Date& expiryDate, Date& dateOfReceipt, string manufacturersName,
                 string unitOfMeasure, float quantity, string comment) {
    this->name = name;
    this->expiryDate = expiryDate;
    this->dateOfReceipt = dateOfReceipt;
    this->manufacturersName = manufacturersName;
    this->unitOfMeasure = unitOfMeasure;
    this->quantity = quantity;
    this->position = new unsigned short int[3];
    for (int i = 0; i < 3; i++)
    {
        this->position[i] = 0;
    }
    this->comment = comment;
}

/**
    ������� ����������� �� ����� Log.
    ��������� ��������� copy ����� ������.
*/
Product::Product(const Product& product) {
    this->copy(product);
}

/**
    ������������� �� �������� �� ����������� =
    @param[in] product � �������, ����� �� �����������.
    @return ����� ������� �����, ����� ����� � �������� ��������� =
*/
Product& Product::operator=(const Product& product) {
    if (this != &product) {                                                             ///��� ���������� ������ � ������� ������, ������������ ���������� ������� ������ => ���� ����� �� ��������.
        this->copy(product);
    }
    return *this;
}

/**
    ������������� �� �������� �� ��������� ==
    @param[in] product � �������, ����� �� ����������� �� ����������.
    @return ����� �������� �� ���������, � ���������� ���� ����������� �� ������� ������� �������� � ����������� �� ���������.
*/
inline bool Product::operator==(const Product& product) {
    if (this->name == product.name && this->expiryDate == product.expiryDate && this->dateOfReceipt == product.dateOfReceipt
        && this->manufacturersName == product.manufacturersName && this->unitOfMeasure == product.unitOfMeasure
        && this->quantity == product.quantity && this->comment == product.comment)
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

void Product::setName(string name) {
    this->name = name;
}

void Product::setExpiryDate(Date expiryDate) {
    this->expiryDate = expiryDate;
}

void Product::setDateOfReceipt(Date dateOfReceipt) {
    this->dateOfReceipt = dateOfReceipt;
}

void Product::setManufacturersName(string manufacturersName) {
    this->manufacturersName = manufacturersName;
}

void Product::setUnitOfMeasure(string unitOfMeasure) {
    this->unitOfMeasure = unitOfMeasure;
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

void Product::setComment(string comment) {
    this->comment = comment;
}

const string Product::getName() const {
    return this->name;
}

const Date Product::getExpiryDate() const {
    return this->expiryDate;
}

const Date Product::getDateOfReceipt() const {
    return this->dateOfReceipt;
}

const string Product::getManufacturersName() const {
    return this->manufacturersName;
}

const string Product::getUnitOfMeasure() const {
    return this->unitOfMeasure;
}

const float Product::getQuantity() const {
    return this->quantity;
}

const unsigned short int* Product::getPosition() const {
    return this->position;
}

const string Product::getComment() const {
    return this->comment;
}

const string Product::getPositionString() {
    string positionString = "";
    positionString.append(to_string(this->position[0]));
    positionString.append("/");
    positionString.append(to_string(this->position[1]));
    positionString.append("/");
    positionString.append(to_string(this->position[2]));

    return positionString;
}

/**
    ����� ���������� ��������, ���� ���� �������� � ������ ����� �� ����� �� ������� �� ������� ������� � �������� ����,
    ���� ��� ����� �� ������� ������� ����, ���� �� ����� �� �������� ��������.
    ������������, ��� ���� ������� ����� �� ������� �� ��������, �� - ����� �� �� ��������.
*/
const bool Product::isFit(Date& date) {
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

/**
    ������������� �� ��������� << �� ����������� ������� �����.
    @param[in, out] output � �������, ����� ����� � �������� <<
    @param[in] product � �������, ����� ���� �� ����� �� ���������.
    @return ����� ������ ������� �� ���������.
*/
ostream& operator<<(ostream& output, const Product& product)
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