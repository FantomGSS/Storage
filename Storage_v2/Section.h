#pragma once
#include<iostream>
#include "Shelf.h"
using namespace std;

const unsigned short int MAX_SHELVES = 10;

class Section {
private:
    Shelf* shelves;

    void copy(const Section& section)
    {
        this->shelves = new Shelf[MAX_SHELVES];
        for (int i = 0; i < MAX_SHELVES; i++)
        {
            this->shelves[i] = section.shelves[i];
        }
    }

    void erase()
    {
        delete[] this->shelves;
    }
public:
    Section();
    Section(const Section&);
    Section& operator=(const Section&);
    ~Section();

    Shelf* getShelves() const;
};

Section::Section() {
    this->shelves = new Shelf[MAX_SHELVES];
}

Section::Section(const Section& section) {
    this->copy(section);
}

Section& Section::operator=(const Section& section) {
    if (this != &section)
    {
        this->erase();
        this->copy(section);
    }
    return *this;
}

Section::~Section() {
    this->erase();
}

Shelf* Section::getShelves() const {
    return this->shelves;
}