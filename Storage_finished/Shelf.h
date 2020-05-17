#pragma once
#include<iostream>
#include "Compartment.h"
using namespace std;

const unsigned short int MAX_COMPARTMENTS = 4;

class Shelf {
private:
    Compartment* compartments;

    void copy(const Shelf& shelf)
    {
        this->compartments = new Compartment[MAX_COMPARTMENTS];
        for (int i = 0; i < MAX_COMPARTMENTS; i++)
        {
            this->compartments[i] = shelf.compartments[i];
        }
    }

    void erase()
    {
        delete[] this->compartments;
    }
public:
    Shelf();
    Shelf(const Shelf&);
    Shelf& operator=(const Shelf&);
    ~Shelf();

    Compartment* getCompartments() const;
};

Shelf::Shelf() {
    this->compartments = new Compartment[MAX_COMPARTMENTS];
}

Shelf::Shelf(const Shelf& shelf) {
    this->copy(shelf);
}

Shelf& Shelf::operator=(const Shelf& shelf) {
    if (this != &shelf)
    {
        this->erase();
        this->copy(shelf);
    }
    return *this;
}

Shelf::~Shelf() {
    this->erase();
}

Compartment* Shelf::getCompartments() const {
    return this->compartments;
}