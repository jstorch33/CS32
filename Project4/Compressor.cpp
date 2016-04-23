#include "provided.h"
#include "HashTable.h"
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

void Compressor::compress(const string& s, vector<unsigned short>& numbers)
{
    numbers.clear();
    unsigned short C = 0;
    
    if(s.size()/2 +512 < 16384)
    {
        C= s.size()/2 +512;
    }
    else
    {
        C = 16384;
    }
    
    HashTable<string, unsigned short>H(C/2, C);
    for(int i = 0; i < 256; i++)
    {
        string s1(1, static_cast<char>(i));
        H.set(s1, i, true);
    }
    
    int nextFreeID = 256;
    string runSoFar;
    unsigned short x = 0;

    for(int j = 0; j < s.size(); j++)
    {
        string c = s.substr(j,1);
        string expandedRun = runSoFar + c;
        unsigned short k = 0;
        if(H.get(expandedRun, k))
        {
            runSoFar = expandedRun;
            continue;
        }
        H.get(runSoFar, x);
        numbers.push_back(x);
        H.touch(runSoFar);
        runSoFar = "";
        unsigned short cv = 0;
        H.get(c, cv);
        numbers.push_back(cv);
        if(!H.isFull())
        {
            H.set(expandedRun, nextFreeID);
            nextFreeID++;
        }
        else
        {
            string key;
            unsigned short value = 0;
            H.discard(key, value);
            H.set(expandedRun, value);
        }
    }
    if(runSoFar != "")
    {
        H.get(runSoFar, x);
        numbers.push_back(x);
    }
    numbers.push_back(C);
}

bool Compressor::decompress(const vector<unsigned short>& numbers, string& s)
{
    if(numbers.size() == 0)
        return false;
    
    unsigned short C = numbers.back();
    HashTable<unsigned short, string>H(C/2,C);
    for(int i = 0; i < 256; i++)
    {
        string s1(1, static_cast<char>(i));
        H.set(i, s1, true);
    }
    
    int nextFreeID = 256;
    string runSoFar, output;
    for(int j = 0; j < numbers.size()-1; j++)
    {
        unsigned short us = numbers[j];
        if(us < 256)
        {
            string usString;
            H.get(us, usString);
            output += usString;
            if(runSoFar == "")
            {
                runSoFar += usString;
                continue;
            }
            
            string expandedRun = runSoFar + usString;
            if(!H.isFull())
            {
                H.set(nextFreeID, expandedRun);
                nextFreeID++;
            }
            else
            {
                string value;
                unsigned short key = 0;
                H.discard(key, value);
                H.set(key, expandedRun);
            }
            runSoFar = "";
            continue;
        }
        else
        {
            string usString;
            if(!H.get(us, usString))
                return false;
            H.touch(us);
            output += usString;
            runSoFar = usString;
            continue;
        }
    }
    s = output;
	return true;
}

unsigned int computeHash(std::string s)
{
    int num = 0;
    for(int i = 0; i < s.size(); i++)
    {
        num +=s[i];
    }
    return num;
}

unsigned int computeHash(int num)
{
    return num;
}
