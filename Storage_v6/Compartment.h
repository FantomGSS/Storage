#pragma once
#include<iostream>
#include<vector> 
#include <algorithm>
#include "Product.h"
using namespace std;

const float MAX_CAPACITY = 40;

class Compartment {
private:
    vector<Product> products;
    float capacity;

    void copy(const Compartment& compartment)
    {
        this->products = compartment.products;
        this->capacity = compartment.capacity;
    }

public:
    Compartment();
    Compartment(const Compartment&);
    Compartment& operator=(const Compartment&);

    void addProduct(Product);
    void removeProduct(Product);
    void reduceCapacity(float);

    const bool isThereEnoughCapacity(Product);
    vector<Product>& getProducts();
    const float getCapacity() const;
}; 

Compartment::Compartment() {
    this->products;
    this->capacity = 0;
}

Compartment::Compartment(const Compartment& compartment) {
    this->copy(compartment);
}

Compartment& Compartment::operator=(const Compartment& compartment) {
    if (this != &compartment)
    {
        this->copy(compartment);
    }
    return *this;
}

void Compartment::addProduct(Product product) {
    this->products.push_back(product);
    this->capacity += product.getQuantity();
}

void Compartment::removeProduct(Product product) {
    this->products.erase(remove(products.begin(), products.end(), product), products.end());
    this->capacity -= product.getQuantity();
}

void Compartment::reduceCapacity(float capacity) {
    this->capacity -= capacity;
}

const bool Compartment::isThereEnoughCapacity(Product product) {
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