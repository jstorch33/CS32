#include "provided.h"
#include <string>
#include <iostream>
using namespace std;

bool Steg::hide(const string& hostIn, const string& msg, string& hostOut) 
{
    hostOut = "";
    if(hostIn.size() == 0)
        return false;
    
    vector<unsigned short> msgNumbers;
    Compressor::compress(msg, msgNumbers);
    string code = BinaryConverter::encode(msgNumbers);
    
    
    int numberOflines = 0;
    string editedHostIn;
    int lastNewLine = 0;
    int numOfSpacesToBeCut =0;
    int startingPosition = 0;
    int numChar = 0;
    
    
    for(int i = 0; i < hostIn.size(); i++)
    {
        if(hostIn[i] == '\r')
        {
            if(i+1 == hostIn.size() || hostIn[i+1] != '\n')
                return false;
            
            editedHostIn += hostIn.substr(startingPosition,numChar);
            startingPosition = i;
            i++;
            lastNewLine = i+1;
            numberOflines++;
            numOfSpacesToBeCut = 0;
            numChar = 2;
        }
        else if(hostIn[i] == '\n')
        {
            editedHostIn += hostIn.substr(startingPosition, numChar);
            startingPosition = i;
            lastNewLine = i;
            numberOflines++;
            numOfSpacesToBeCut = 0;
            numChar = 1;
        }
        else if(hostIn[i] == ' ' || hostIn[i] == '\t')
        {
            numOfSpacesToBeCut++;
        }
        else
        {
            numChar += numOfSpacesToBeCut+1;
            numOfSpacesToBeCut = 0;
        }
    }
    numOfSpacesToBeCut = 0;
    if(hostIn[hostIn.size()-1] != '\n')
    {
        numberOflines++;
        editedHostIn += hostIn.substr(startingPosition, numChar);
        numChar=0;
    }
    if(numChar != 0)
    {
        editedHostIn += hostIn.substr(startingPosition, numChar);
    }
    
    
    int howManyExtra = code.size()%numberOflines;
    int starting = 0;
    for(int i = 0 ; i < editedHostIn.size(); i++)
    {
        if(editedHostIn[i] == '\n')
        {
            unsigned long pieceLength = code.size()/numberOflines;
            if(howManyExtra > 0)
            {
                pieceLength++;
                howManyExtra--;
            }
            hostOut = hostOut + code.substr(starting, pieceLength);
            starting += pieceLength;
            hostOut += editedHostIn[i];
        }
        else if(editedHostIn[i] == '\r')
        {
            unsigned long pieceLength = code.size()/numberOflines;
            if(howManyExtra > 0)
            {
                pieceLength++;
                howManyExtra--;
            }
            hostOut = hostOut + code.substr(starting, pieceLength);
            starting += pieceLength;
            hostOut += editedHostIn[i];
            hostOut += editedHostIn[i+1];
            i++;
        }
        else
        {
            hostOut += editedHostIn[i];
        }
    }
    unsigned long pieceLength = code.size()/numberOflines;
    if(howManyExtra > 0)
    {
        pieceLength++;
        howManyExtra--;
    }
    if(starting != code.size())
    {
        hostOut = hostOut + code.substr(starting, pieceLength);
        starting += pieceLength;
    }
    return true;
}
//"<html>\nQ \tQQ\nBBB\n\nGG\nBBB\n\nDDD\nEEE </html>"
//"<html>        \nQ \tQQ \t  \t  \nBBB       \n   \t\t  \nGG\t \t    \nBBB     \t\t\n \t\t    \nDDD    \t  \nEEE </html>      \t"
//code	std::__1::string	"         \t  \t            \t\t  \t \t         \t\t \t\t        \t        \t"
//code	std::__1::string	"         \t  \t            \t\t  \t \t         \t\t \t\t    "
bool Steg::reveal(const string& hostIn, string& msg)
{
    int num = 0;
    int lastNewLine = 0;
    bool firstNewLine = true;
    bool switchInSize = false;
    bool spacesBefore = false;
    int numSpaces = 0;
    int firstSpacePosition = 0;
    string code;
    for(int i = 0; i < hostIn.size(); i++)
    {
        if(hostIn[i] == '\n')
        {
            if(firstNewLine)
            {
                lastNewLine = i;
                code += hostIn.substr(firstSpacePosition,numSpaces);
                firstSpacePosition = i+1;
                num = numSpaces;
                numSpaces = 0;
                firstNewLine = false;
                spacesBefore = false;
            }
            else if(!switchInSize)
            {
                lastNewLine = i;
                code += hostIn.substr(firstSpacePosition,numSpaces);
                firstSpacePosition = i+1;
                if(num == numSpaces+1)
                    switchInSize = true;
                else if(num != numSpaces)
                    return false;
                numSpaces = 0;
                spacesBefore = false;
            }
            else
            {
                lastNewLine = i;
                code += hostIn.substr(firstSpacePosition,numSpaces);
                firstSpacePosition = i+1;
                if(numSpaces != num-1)
                    return false;
                numSpaces = 0;
                spacesBefore = false;
            }
        }
        else if (hostIn[i]== '\r')
        {
            i++;
            if(firstNewLine)
            {
                lastNewLine = i;
                code += hostIn.substr(firstSpacePosition,numSpaces);
                firstSpacePosition = i+1;
                num = numSpaces;
                numSpaces = 0;
                firstNewLine = false;
                spacesBefore = false;
            }
            else if(!switchInSize)
            {
                lastNewLine = i;
                code += hostIn.substr(firstSpacePosition,numSpaces);
                firstSpacePosition = i+1;
                if(num == numSpaces+1)
                    switchInSize = true;
                else if(num != numSpaces)
                    return false;
                numSpaces = 0;
                spacesBefore = false;
            }
            else
            {
                lastNewLine = i;
                code += hostIn.substr(firstSpacePosition,numSpaces);
                firstSpacePosition = i+1;
                if(numSpaces != num-1)
                    return false;
                numSpaces = 0;
                spacesBefore = false;
            }
        }
        else if(hostIn[i] == ' ' || hostIn[i] == '\t')
        {
            numSpaces++;
            if(!spacesBefore)
            {
                firstSpacePosition = i;
            }
            spacesBefore = true;
        }
        else
        {
            numSpaces = 0;
            spacesBefore = false;
        }
    }
    
    
    string tempCode;
    for(int j = lastNewLine; j < hostIn.size(); j++)
    {
        if(hostIn[j] == ' ' || hostIn[j] == '\t')
        {
            tempCode += hostIn[j];
        }
        else
        {
            tempCode = "";
        }
    }
    if(tempCode.size() != num && tempCode.size() != 0 && !switchInSize)
    {
        if(tempCode.size() != num-1)
            return false;
    }
    if(switchInSize && tempCode.size()!= num-1 && tempCode.size() != 0)
        return false;

    code += tempCode;
    vector<unsigned short> numbers;
    BinaryConverter::decode(code, numbers);
    Compressor::decompress(numbers, msg);
	return true;
}

