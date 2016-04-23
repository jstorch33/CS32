#include "provided.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;

const size_t BITS_PER_UNSIGNED_SHORT = 16;

string convertNumberToBitString(unsigned short number);
bool convertBitStringToNumber(string bitString, unsigned short& number);

string BinaryConverter::encode(const vector<unsigned short>& numbers)
{
    string binary,final;
    for(int i = 0; i < numbers.size(); i++)
    {
        binary += convertNumberToBitString(numbers[i]);
    }
    for(int j = 0; j < binary.size(); j++)
    {
        if(binary[j] == '0')
        {
            final += ' ';
        }
        else
        {
            final += '\t';
        }
    }
    
    return final;
}

bool BinaryConverter::decode(const string& bitString,
							 vector<unsigned short>& numbers)
{
    string binary;
    unsigned short value = 0;
    if(bitString.size()%16 != 0)
        return false;
    
    for(int i = 0; i < bitString.size(); i++)
    {
        if(bitString[i] == ' ')
        {
            binary += '0';
        }
        else if(bitString[i] == '\t')
        {
            binary += '1';
        }
        else
        {
            return false;
        }
    }

    for(int j = 0; j < binary.size(); j+=16)
    {
        convertBitStringToNumber(binary.substr(j,16), value);
        numbers.push_back(value);
    }
    return true;
}

string convertNumberToBitString(unsigned short number)
{
	string result(BITS_PER_UNSIGNED_SHORT, '0');
	for (size_t k = BITS_PER_UNSIGNED_SHORT; number != 0; number /= 2)
	{
		k--;
		if (number % 2 == 1)
			result[k] = '1';
	}
	return result;
}

bool convertBitStringToNumber(string bitString, unsigned short& number)
{
	if (bitString.size() != BITS_PER_UNSIGNED_SHORT)
		return false;
	number = 0;
	for (size_t k = 0; k < bitString.size(); k++)
	{
		number *= 2;
		if (bitString[k] == '1')
			number++;
		else if (bitString[k] != '0')
			return false;
	}
	return true;
}
