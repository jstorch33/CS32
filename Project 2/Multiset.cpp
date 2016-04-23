//
//  Multiset.cpp
//  Project 2
//
//  Created by Jack Storch on 1/23/15.
//  Copyright (c) 2015 Jack Storch. All rights reserved.
//

#include "Multiset.h"

Multiset::Multiset()
{}

Multiset::~Multiset()
{
    if(head != nullptr)     //Makes sure that the multiset being destroyed isnt empty
    {
        Node* p = head;
        while(p->m_next != nullptr)
        {
            Node* temp = p->m_next;
            delete p;
            p = temp;
        }
        delete p;
    }
}

Multiset::Multiset(const Multiset& other)
{
    Node* p;
    for(p = other.head; p->m_next != nullptr; p = p->m_next)    //make all new nodes
    {
        for(int pos = 0; pos < p->m_count; pos++)
        {
            this->insert(p->m_data);
        }
    }
    for(int pos2 = 0; pos2 < p->m_count; pos2++)
    {
        this->insert(p->m_data);
    }
}

Multiset& Multiset::operator=(const Multiset& copy)
{
    if(this != &copy)       //makes suer they dont point to the same address
    {
        Multiset temp(copy);    //make a copy
        this->swap(temp);       //swap the copy
    }
    return *this;
}

bool Multiset::empty() const
{
    if(head == nullptr)
    {
        return true;
    }
    return false;
}

int Multiset::size() const
{
    int c = 0;
    if(!empty())
    {
        Node* p;
        for (p = head; p->m_next != nullptr; p = p->m_next)
        {
            c += p->m_count;
        }
        c+=p->m_count;          //this line enables the last item to be in it as well
    }
    return c;
}

int Multiset::uniqueSize() const
{
    int c = 0;
    if(!empty())
    {
        for (Node* p = head; p->m_next != nullptr; p = p->m_next)
        {
            c++;
        }
        c++;
    }
    return c;
}

bool Multiset::insert(const ItemType& value)
{
    if(empty())
    {
        Node* newBrah = new Node();         //make a new node and sets head and tail
        head = newBrah;
        tail = newBrah;
        newBrah->m_data = value;
        newBrah->m_count++;
    }
    else if(contains(value))
    {
        Node* p;
        for (p = head; p->m_next != nullptr && p->m_data != value; p = p->m_next)
        {
            ;                       //this code looks for value in the multiset
        }
        p->m_count++;
    }
    else
    {
        Node* newBrah = new Node();
        tail->m_next = newBrah;
        newBrah->m_last = tail;
        tail = newBrah;
        newBrah->m_data = value;
        newBrah->m_count++;
    }
    return true;
}

int Multiset::erase(const ItemType& value)
{
    Node* p;
    for (p = head; p->m_next != nullptr && p->m_data != value; p = p->m_next)
    {
        ;               //looks for where it is if at all
    }
    if(p->m_data == value)
    {
        if(p->m_count > 1)
        {
            p->m_count--;
        }
        else if(uniqueSize() == 1)
        {
            head = nullptr;
            tail = nullptr;
            delete p;
        }
        else if(p->m_last == nullptr)
        {
            head = p->m_next;                   //if only has one instance left then delete the node
            p->m_next->m_last = nullptr;
            delete p;
        }
        else if(p->m_next == nullptr)
        {
            tail = p->m_last;
            p->m_last->m_next = nullptr;
            delete p;
        }
        else
        {
            p->m_next->m_last = p->m_last;
            p->m_last->m_next = p->m_next;
            delete p;
        }
        return 1;
    }
    return 0;
}

int Multiset::eraseAll(const ItemType& value)
{
    Node* p;
    for (p = head; p->m_next != nullptr && p->m_data != value; p = p->m_next)
    {
        ;
    }
    if(p->m_data == value)
    {
        int c = p->m_count;
        if(uniqueSize() == 1)
        {
            head = nullptr;
            tail = nullptr;            //always delete the node
            delete p;
        }
        else if(p->m_last == nullptr)
        {
            head = p->m_next;
            p->m_next->m_last = nullptr;
            delete p;
        }
        else if(p->m_next == nullptr)
        {
            tail = p->m_last;
            p->m_last->m_next = nullptr;
            delete p;
        }
        else
        {
            p->m_next->m_last = p->m_last;
            p->m_last->m_next = p->m_next;
            delete p;
        }
        return c;
    }
    return 0;
}

bool Multiset::contains(const ItemType& value) const
{
    Node* p;
    for (p = head; p->m_next != nullptr && p->m_data != value; p = p->m_next)
    {
        ;
    }
    if(p->m_data == value && p->m_count != 0)
    {
        return true;
    }
    return false;
}


int Multiset::count(const ItemType& value) const
{
    Node* p;
    for (p = head; p->m_next != nullptr && p->m_data != value; p = p->m_next)
    {
        ;
    }
    if(p->m_data == value)
    {
        return p->m_count;
    }
    return 0;
}

int Multiset::get(int i, ItemType& value) const
{
    Node* p = head;
    for (int pos = 0; pos < i; pos++)
    {
        if(p->m_next != nullptr)
        {
            p = p->m_next;                  //uses a for loop since cant check as easy as an array
        }
        else
        {
            return 0;
        }
    }
    value = p->m_data;
    return p->m_count;
}

void Multiset::swap(Multiset& other)
{
    Node* temp = other.head;            //swap the head and tail pointers
    other.head = head;
    head = temp;
    Node* temp2 = other.tail;
    other.tail = tail;
    tail = temp2;
}

void combine(const Multiset& ms1, const Multiset& ms2, Multiset& result)
{
    if(&ms1 == &result)                         //check for aliasing of ms1 and result
    {
        Multiset* tempMultiset =  new Multiset(ms1);    //make result to a new multset
        result = *tempMultiset;                         //combats aliasing
        for(int pos = 0; pos < ms2.uniqueSize(); pos++)
        {
            ItemType temp;
            int c = ms2.get(pos,temp);
            for(int number = 0; number < c; number++)   //add ms2
            {
                result.insert(temp);
            }
        }
    }
    else                                        //aliasing for ms2 and result
    {
        Multiset* tempMultiset =  new Multiset(ms2);
        result = *tempMultiset;
        for(int pos = 0; pos < ms1.uniqueSize(); pos++)
        {
            ItemType temp;
            int c = ms1.get(pos,temp);          //does the opposite as above loop ^
            for(int number = 0; number < c; number++)
            {
                result.insert(temp);
            }
        }
    }
}

void subtract(const Multiset& ms1, const Multiset& ms2, Multiset& result)
{
    Multiset* tempMultiset =  new Multiset(ms1);
    result = *tempMultiset;
    for(int pos = 0; pos < ms2.uniqueSize(); pos++)
    {
        ItemType temp;
        int c = ms2.get(pos, temp);
        for(int number = 0; number < c; number++)
        {
            result.erase(temp);         //only changed line from combine
        }
    }
}

