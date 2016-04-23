//
//  HastTable.h
//  Project 4
//
//  Created by Jack Storch on 3/7/15.
//  Copyright (c) 2015 Jack Storch. All rights reserved.
//

#ifndef Project_4_HastTable_h
#define Project_4_HastTable_h

#include "provided.h"
#include <iostream>
using namespace std;


template <typename KeyType,	typename ValueType>
class HashTable
{
public:
    HashTable(unsigned int numBuckets,	unsigned int capacity);
    ~HashTable();
    bool isFull() const;
    bool set(const KeyType&	key, const ValueType& value, bool permanent = false);
    bool get(const KeyType& key, ValueType& value) const;
    bool touch(const KeyType& key);
    bool discard(KeyType& key,	ValueType& value);
private:
    struct Node
    {
        KeyType m_key;
        ValueType m_value;
        Node* next;
        Node* last;
        Node* nextInLine;
        Node* behindInLine;
    };
    
    Node** arr;
    int max;
    int m_numObjects;
    int m_numBuckets;
    Node* firstInLine;
				//	We	prevent a	HashTable from	being	copied	or	assigned	by	declaring	the
				//	copy	constructor	and	assignment	operator	private	and	not	implementing	them.
    HashTable(const HashTable&);
    HashTable& operator=(const HashTable&);
};

template <typename KeyType,	typename ValueType>
HashTable<KeyType, ValueType>::HashTable(unsigned int numBuckets, unsigned int capacity)
:max(capacity), m_numObjects(0), m_numBuckets(numBuckets), firstInLine(nullptr)
{
    arr = new Node*[numBuckets];
}

template <typename KeyType,	typename ValueType>
bool HashTable<KeyType, ValueType>::isFull() const
{
    return m_numObjects == max;
}

template <typename KeyType,	typename ValueType>
HashTable<KeyType, ValueType>::~HashTable()
{
    for (int i=0; i < m_numBuckets; i++)
    {
        Node* ptr = arr[i];
        if(ptr == nullptr)
            continue;
        while(ptr->next != nullptr)
        {
            Node* p = ptr->next;
            delete ptr;
            ptr = p;
        }
       
    }
    delete [] arr;
}

template <typename KeyType,	typename ValueType>
bool HashTable<KeyType, ValueType>::set(const KeyType&	key, const ValueType& value, bool permanent)
{
    unsigned int heshKey = computeHash(key);
    int bucketKey = heshKey % m_numBuckets;
    
    if(isFull())
        return false;
    
    Node* newguy = new Node();
    newguy->m_value = value;
    newguy->m_key = key;
    newguy->next = nullptr;
    newguy->last = nullptr;
    newguy->nextInLine = nullptr;
    newguy->behindInLine = nullptr;
    
    if(!permanent)
    {
        if(firstInLine == nullptr)
        {
            firstInLine = newguy;
        }
        else
        {
            Node* p = firstInLine;
            for(;p->nextInLine != nullptr;p = p->nextInLine)
            {}
            p->nextInLine = newguy;
            newguy->behindInLine = p;
        }
    }
    
    if(arr[bucketKey] == nullptr)
    {
        arr[bucketKey] = newguy;
        m_numObjects++;
        return true;
    }
    
    Node* p = arr[bucketKey];
    while(p != nullptr)
    {
        if(p->m_key == key)
        {
            if(!permanent)
            {
                if(p->nextInLine != nullptr)
                {
                    p->nextInLine->behindInLine = newguy;
                }
                if(p->behindInLine != nullptr)
                {
                    p->behindInLine->nextInLine = newguy;
                }
                newguy->nextInLine = p->nextInLine;
                newguy->behindInLine = p->behindInLine;
            }
            
            if(p->next != nullptr)
            {
                newguy->next = p->next;
                p->next->last = newguy;
            }
            
            if(p->last != nullptr)
                p->last->next = newguy;
            newguy->last = p->last;
            delete p;
            return true;
        }
        if(p->next == nullptr)
        {
            p->next = newguy;
            newguy->last = p;
            m_numBuckets++;
        }
        p = p->next;
    }
    return true;
}

template <typename KeyType,	typename ValueType>
bool HashTable<KeyType, ValueType>::get(const KeyType& key, ValueType& value) const
{
    unsigned int heshKey = computeHash(key);
    int bucketKey = heshKey % m_numBuckets;
    
    Node* p = arr[bucketKey];
    while(p != nullptr)
    {
        if(p->m_key == key)
        {
            value = p->m_value;
            return true;
        }
        p = p->next;
    }
    return false;
}

template <typename KeyType,	typename ValueType>
bool HashTable<KeyType, ValueType>::touch(const KeyType& key)
{
    Node* p = firstInLine;
    while(p != nullptr)
    {
        if(p->m_key == key)
        {
            if(p->behindInLine != nullptr)
                p->behindInLine->nextInLine = p->nextInLine;
            if(p->nextInLine != nullptr)
                p->nextInLine->behindInLine = p->behindInLine;
            firstInLine->behindInLine = p;
            p->nextInLine = firstInLine;
            p->behindInLine = nullptr;
            firstInLine = p;
            return true;
        }
        p = p->next;
    }
    return false;
}

template <typename KeyType,	typename ValueType>
bool HashTable<KeyType, ValueType>::discard(KeyType& key,	ValueType& value)
{
    if(firstInLine == nullptr)
        return false;
    
    Node* p = firstInLine;
    if(p->last != nullptr)
    {
        p->last->next = p->next;
    }
    if(p->next != nullptr)
    {
        p->next->last = p->last;
    }
    p->nextInLine->behindInLine = nullptr;
    firstInLine = p->nextInLine;
    key = p->m_key;
    value = p->m_value;
    m_numObjects--;
    delete p;
    return true;
}


#endif