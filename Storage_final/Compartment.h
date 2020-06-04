#pragma once
#include<vector> 
#include <algorithm>
#include "Product.h"

const float MAX_CAPACITY = 40;                                                          ///���������� ��������� �� ���� ��������� � �����.

/**
    ���� Compartment, ����� ����� �� ������������� �� ��������� � ����� � ��������� ������� ������ �� ���������� � ������� ���������.
*/
class Compartment {
private:
    vector<Product> products;                                                           ///������ �� ��������, ������ �� �� ����� ���������� � �����������.
    float capacity;                                                                     ///������ �����, �������������� ���������� �� �����������.

    void copy(const Compartment& compartment)                                           ///�������, ����� ������ ����������� �� ��������� �����.
    {
        this->products = compartment.products;
        this->capacity = compartment.capacity;
    }

public:
    Compartment();                                                                      ///����������� �� ������������.
    Compartment(const Compartment&);                                                    ///������� �����������.
    Compartment& operator=(const Compartment&);                                         ///������������� �� �������� �� ����������� =

    void addProduct(Product&);                                                          ///�������, ����� ������ ����� �� ��� Product � �� ������ ��� ������� �� �������� �� �������� ���������.
    void removeProduct(Product&);                                                       ///�������, ����� ������ ����� �� ��� Product � �� �������� �� ������� �� �������� �� �������� ���������.
    void reduceCapacity(float);                                                         ///�������, ����� ������ ������ ����� � �������� ���������� �� �������� ����������� � ���� ��������.
    void setCapacity(float);

    const bool isThereEnoughCapacity(Product&);                                         ///�������, ����� ������ ����� �� ��� Product � ��������� ���� � �������� ����������� ��� ���������� ����� �� ����.
    
    vector<Product>& getProducts();
    const float getCapacity() const;
}; 

/**
    ����������� �� ������������ �� ����� Compartment.
    ������������� �� ������� �� �������� � ��������� �� ������ �������� �� ����������. 
*/
Compartment::Compartment() {
    this->products;
    this->capacity = 0;
}

/**
    ������� ����������� �� ����� Compartment.
    ��������� ��������� copy ����� ������.
*/
Compartment::Compartment(const Compartment& compartment) {
    this->copy(compartment);
}

/**
    ������������� �� �������� �� ����������� =
    @param[in] compartment � �������, ����� �� �����������.
    @return ����� ������� �����, ����� ����� � �������� ��������� =
*/
Compartment& Compartment::operator=(const Compartment& compartment) {
    if (this != &compartment)                                                           ///��� ���������� ������ � ������� ������, ������������ ���������� ������� ������ => ���� ����� �� ��������.
    {
        this->copy(compartment);
    }
    return *this;
}

/**
    ���� ���������� �� �������� ��� �������, ��������� �� � ���������� �� �������� �����������.
*/
void Compartment::addProduct(Product& product) {
    this->products.push_back(product);
    this->capacity += product.getQuantity();
}

/**
    ���� ������������ �� �������� �� �������, �������� �� � ���������� �� �������� �����������.
*/
void Compartment::removeProduct(Product& product) {
    this->products.erase(remove(products.begin(), products.end(), product), products.end());
    this->capacity -= product.getQuantity();
}

void Compartment::reduceCapacity(float capacity) {
    this->capacity -= capacity;
}

/**
    ���� ���������� �� ���������� ������ �����, ��� � ��-������ �� ����������� �������� ���������, �� ������ �� �������� ����.
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