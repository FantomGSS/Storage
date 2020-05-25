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

/**
    Клас Product, който служи за имплементация на продукт и съответно съдържа информация за продукта.
*/
class Product {
private:
    char* name;                                                                         ///Символен низ, показващ името на продукта.
    Date expiryDate;                                                                    ///Дата, която представлява срока на годност на продукта.
    Date dateOfReceipt;                                                                 ///Дата, която представлява деня, в който продуктът се зарежда в склада.
    char* manufacturersName;                                                            ///Символен низ, показващ името на производителя.
    char* unitOfMeasure;                                                                ///Символен низ, представляващ мерната единица на продукта.
    float quantity;                                                                     ///Дробно число, представляващо количеството на продукта
    unsigned short int* position;                                                       ///Масив от цели естествени числа, който показва къде се намира продукта - секция, рафт, отделение.
    char* comment;                                                                      ///Незадължителен символен низ, представляващ коментар за продукта.

    void copy(const Product& product)                                                   ///Функция, която копира стойностите на подадения обект.
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

    void erase()                                                                        ///Освобождава динамично заделената памет от символните низове.
    {
        delete[] this->name;
        delete[] this->manufacturersName;
        delete[] this->unitOfMeasure;
        delete[] this->comment;
    }

public:
    Product();                                                                          ///Конструктор по подразбиране.
    Product(const char*, Date&, Date&, const char*, 
            const char*, float, const char*);                                           ///Конструктор с параметри.
    Product(const Product&);                                                            ///Копиращ конструктор.
    Product& operator=(const Product&);                                                 ///Предефиниране на оператор за присвояване =
    inline bool operator==(const Product&);                                             ///Предефиниране на оператор за сравнение ==
    ~Product();                                                                         ///Деструктор

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
    
    const string getPositionString();                                                   ///Функция, която преобразува позицията на продукта (масива) в символен низ.
    const bool isFit(Date& date);                                                       ///Функция, която проверява дали срока на годност на текущия продукт е изтекъл или предстои скоро да изтече.

    friend ostream& operator<<(std::ostream&, const Product&);                          ///Предефиниране на оператор за вмъкване <<
};

/**
    Конструктор по подразбиране за класа Product.
    Датите с техните стойности по подразбиране, а имената, мерната единица и коментара - празни символни низове.
    Позицията приема нулеви стойности за секция, рафт и отделение, както и количеството.
*/
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

/**
    Конструктор с параметри за класа Product.
    По подадени име на продукта, срок на годност, дата на зареждане, име на производител, мерна единица, количество и коментар.
*/
Product::Product(const char* name, Date& expiryDate, Date& dateOfReceipt, const char* manufacturersName, 
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

/**
    Копиращ конструктор за класа Log.
    Прилагаме функцията copy върху обекта.
*/
Product::Product(const Product& product) {
    this->copy(product);
}

/**
    Предефиниране на оператор за присвояване =
    @param[in] product е обектът, който ще присвояваме.
    @return Връща текущия обект, върху който е приложен оператора =
*/
Product& Product::operator=(const Product& product) {
    if (this != &product) {                                                             ///Ако сравняваме обекти с еднакви адреси, следователно сравняваме еднакви обекти => няма нужда от копиране.
        this->erase();
        this->copy(product);
    }
    return *this;
}

/**
    Предефиниране на оператор за сравнение ==
    @param[in] product е обектът, който ще проверяваме за съвпадение.
    @return Връща стойност за истинност, в зависимост дали параметрите на текущия продукт съвпадат с параметрите на подадения.
*/
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

/**
    Деструктор, който освобождава динамично заделената памет след приключване на работа с обектът.
*/
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
    Първо сравняваме годините, след това месеците и накрая дните на срока на годност на текущия продукт и днешната дата,
    като ако срока на годност свършва днес, това се счита за скорошно изтичане.
    Следователно, ако днес свършва срока на годност на продукта, по - добре да се разчисти.
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
    Предефиниране на оператора << за стандартния изходен поток.
    @param[in, out] output е потокът, върху който е приложен <<
    @param[in] product е обектът, който седи от дясно на оператора.
    @return Връща потока подаден на функцията.
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