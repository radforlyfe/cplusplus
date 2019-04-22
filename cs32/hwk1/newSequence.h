//
//  newSequence.hpp
//  cs32_Assignment1
//
//  Created by Radhika Nayar on 4/15/19.
//  Copyright © 2019 Radhika Nayar. All rights reserved.
//

#ifndef newSequence_H
#define newSequence_H

#include<string>
#include<iostream>
#include <cstdlib>

using ItemType = unsigned long;
const int DEFAULT_MAX_ITEMS = 250;

class Sequence
{
public:
    Sequence(); //default constructor
    Sequence(int cap); //dynamically allocated array constructor with default
    Sequence(const Sequence&); //copy constructor
    Sequence& operator=(const Sequence& rhs); //assignment constructor
    ~Sequence(); //destructor
    
    bool empty() const;
    int size() const;
    int insert(int pos, const ItemType& value);
    int insert(const ItemType& value);
    bool erase(int pos);
    int remove(const ItemType& value);
    bool get(int pos, ItemType& value) const;
    bool set(int pos, const ItemType& value);
    int find(const ItemType& value) const;
    void swap(Sequence& other);
    void dump() const;
    
private:
    ItemType * m_array = nullptr;
    int m_size;
    int m_capacity;
    
};

#endif // newSequence_H
