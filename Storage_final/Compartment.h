#pragma once
#include<vector> 
#include <algorithm>
#include "Product.h"

const float MAX_CAPACITY = 40;                                                          ///Максимален капацитет на едно отделение в рафта.

/**
    Клас Compartment, който служи за имплементация на отделение в рафта и съответно съдържа вектор от продуктите и неговия капацитет.
*/
class Compartment {
private:
    vector<Product> products;                                                           ///Вектор от продукти, където ще се пазят продуктите в отделението.
    float capacity;                                                                     ///Дробно число, представляващо капацитета на отделението.

    void copy(const Compartment& compartment)                                           ///Функция, която копира стойностите на подадения обект.
    {
        this->products = compartment.products;
        this->capacity = compartment.capacity;
    }

public:
    Compartment();                                                                      ///Конструктор по подразбиране.
    Compartment(const Compartment&);                                                    ///Копиращ конструктор.
    Compartment& operator=(const Compartment&);                                         ///Предефиниране на оператор за присвояване =

    void addProduct(Product&);                                                          ///Функция, която приема обект от тип Product и го добавя във вектора от продукти на текущото отделение.
    void removeProduct(Product&);                                                       ///Функция, която приема обект от тип Product и го премахва от вектора от продукти на текущото отделение.
    void reduceCapacity(float);                                                         ///Функция, която приема дробно число и намалява капацитета на текущото отделението с тази стойност.
    void setCapacity(float);

    const bool isThereEnoughCapacity(Product&);                                         ///Функция, която приема обект от тип Product и проверява дали в текущото отделението има достатъчно място за него.
    
    vector<Product>& getProducts();
    const float getCapacity() const;
}; 

/**
    Конструктор по подразбиране за класа Compartment.
    Инициализация на вектора от продукти и поставяне на нулева стойност на капацитета. 
*/
Compartment::Compartment() {
    this->products;
    this->capacity = 0;
}

/**
    Копиращ конструктор за класа Compartment.
    Прилагаме функцията copy върху обекта.
*/
Compartment::Compartment(const Compartment& compartment) {
    this->copy(compartment);
}

/**
    Предефиниране на оператор за присвояване =
    @param[in] compartment е обектът, който ще присвояваме.
    @return Връща текущия обект, върху който е приложен оператора =
*/
Compartment& Compartment::operator=(const Compartment& compartment) {
    if (this != &compartment)                                                           ///Ако сравняваме обекти с еднакви адреси, следователно сравняваме еднакви обекти => няма нужда от копиране.
    {
        this->copy(compartment);
    }
    return *this;
}

/**
    След добавянето на продукта във вектора, увеличава се и капацитета на текущото отделението.
*/
void Compartment::addProduct(Product& product) {
    this->products.push_back(product);
    this->capacity += product.getQuantity();
}

/**
    След премахването на продукта от вектора, намалява се и капацитета на текущото отделението.
*/
void Compartment::removeProduct(Product& product) {
    this->products.erase(remove(products.begin(), products.end(), product), products.end());
    this->capacity -= product.getQuantity();
}

void Compartment::reduceCapacity(float capacity) {
    this->capacity -= capacity;
}

/**
    След проверката на подаденото дробно число, ако е по-голямо от максималния позволен капацитет, то приема за стойност него.
*/
void Compartment::setCapacity(float capacity) {
    if (capacity <= MAX_CAPACITY)
    {
        this->capacity = capacity;
    }
    else
    {
        this->capacity = MAX_CAPACITY;
    }
}

const bool Compartment::isThereEnoughCapacity(Product& product) {
    if (this->capacity + product.getQuantity() <= MAX_CAPACITY)
    {
        return true;
    }
    else
    {
        return false;
    }
}

vector<Product>& Compartment::getProducts() {
    return this->products;
}

const float Compartment::getCapacity() const {
    return this->capacity;
}