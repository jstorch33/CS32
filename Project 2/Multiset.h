//
//  Multiset.h
//  Project 2
//
//  Created by Jack Storch on 1/23/15.
//  Copyright (c) 2015 Jack Storch. All rights reserved.
//

#ifndef MULTISET_INCLUDED
#define MULTISET_INCLUDED

#include <string>
#include "OurType.h"
typedef OurType ItemType;

class Multiset
{
public:
    Multiset();
    ~Multiset(); //Destructor
    Multiset(const Multiset& other); //Copy constructor
    Multiset& operator=(const Multiset& copy); //Assignment operator
    bool empty() const;
    int size() const;
    int uniqueSize() const;
    bool insert(const ItemType& value);
    int erase(const ItemType& value);
    int eraseAll(const ItemType& value);
    bool contains(const ItemType& value) const;
    int count(const ItemType& value) const;
    int get(int i, ItemType& value) const;
    void swap(Multiset& other);
private:
    struct Node
    {
        int m_count = 0;
        ItemType m_data;
        Node* m_next = nullptr;
        Node* m_last = nullptr;
    };
    
    Node* head = nullptr;
    Node* tail = nullptr;
};

void combine(const Multiset& ms1, const Multiset& ms2, Multiset& result);
void subtract(const Multiset& ms1, const Multiset& ms2, Multiset& result);

#endif