#pragma once
#include "Date.h"

/**
    Клас Product, който служи за имплементация на продукт и съответно съдържа информация за продукта.
*/
class Product {
private:
    string name;                                                                         ///Символен низ, показващ името на продукта.
    Date expiryDate;                                                                     ///Дата, която представлява срока на годност на продукта.
    Date dateOfReceipt;                                                                  ///Дата, която представлява деня, в който продуктът се зарежда в склада.
    string manufacturersName;                                                            ///Символен низ, показващ името на производителя.
    string unitOfMeasure;                                                                ///Символен низ, представляващ мерната единица на продукта.
    float quantity;                                                                      ///Дробно число, представляващо количеството на продукта
    unsigned short int* position;                                                        ///Масив от цели естествени числа, който показва къде се намира продукта - секция, рафт, отделение.
    string comment;                                                                      ///Незадължителен символен низ, представляващ коментар за продукта.

    void copy(const Product& product)                                                    ///Функция, която копира стойностите на подадения обект.
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
    Product();                                                                           ///Конструктор по подразбиране.
    Product(string, Date&, Date&, string, 
            string, float, string);                                                      ///Конструктор с параметри.
    Product(const Product&);                                                             ///Копиращ конструктор.
    Product& operator=(const Product&);                                                  ///Предефиниране на оператор за присвояване =
    inline bool operator==(const Product&);                                              ///Предефиниране на оператор за сравнение ==

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
    
    const string getPositionString();                                                    ///Функция, която преобразува позицията на продукта (масива) в символен низ.
    const bool isFit(Date& date);                                                        ///Функция, която проверява дали срока на годност на текущия продукт е изтекъл или предстои скоро да изтече.

    friend ostream& operator<<(std::ostream&, const Product&);                           ///Предефиниране на оператор за вмъкване <<
};

/**
    Конструктор по подразбиране за класа Product.
    Датите с техните стойности по подразбиране, а имената, мерната единица и коментара - празни символни низове.
    Позицията приема нулеви стойности за секция, рафт и отделение, както и количеството.
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
    Конструктор с параметри за класа Product.
    По подадени име на продукта, срок на годност, дата на зареждане, име на производител, мерна единица, количество и коментар.
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