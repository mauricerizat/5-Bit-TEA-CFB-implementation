/*
CFB TEA
*/

#include "header.h"

//Perform XOR on bits stored in string
string stringXor(string a, string b)
{
	bitset<GLOBAL_CONST_K> aBits(stol(a, 0, 2)); //Store in bitset
	bitset<GLOBAL_CONST_K> bBits(stol(b, 0, 2)); //Store in bitset
	bitset<GLOBAL_CONST_K> xorResult  (aBits ^ bBits); //Perform XOR
	string afterXor = xorResult.to_string(); //Convert result to string
	return afterXor;
}

//Add padding to input to be compitable with K
void padInput(string& input, int factor)
{
	int n = input.length();
	while (n % factor != 0)
	{
		input = input + "0";
		n = input.length();
	}
}

//Make key be a 128-bit block
void padKey(string& key)
{
	if (key.length() > 128) //If key length exceeds 128 bits, read first 128 bits
	{
		key = key.substr(0, 128);
		return;
	}
	
	int n = key.length(); 
	
	while (n < 128) //If key length is less than 128 bits, add padding of zeroes
	{
		key = key + "0";
		n = key.length();
	}
}

//Convert string of bits to ASCII text
string toText(string stream)
{
	string text = "";	
	
	for (int i = 0; i < stream.length();)
	{
	 	string charAt = stream.substr(i, 8); //Take 8 bits
		char charAct = (uint8_t)stoi(charAt, 0, 2); //Convert 8 bits to character
		text = text + charAct; //Store in text string
		i += 8; //Increment index
	}
	
	return text;
}

//Convert ASCII string to stream of binary bits
string toBits(string input)
{
	string bits = "";
	
	for (int i = 0; i < input.length(); ++i)
	{
		bits = bits + bitset<8>((uint8_t)input[i]).to_string(); //Convert char to bitset and then string
	}
	
	return bits;
}

/*
string hexToBits (string hexVal)
{
	string bits = "";
	
	for (int i = 0; i < hexVal.length();)
	{
		string hexByte = hexVal.substr(i, 2);
		i += 2;
		
		int byteVal = stoi(hexByte, 0, 16);
		
		bits = bits + bitset<8>(byteVal).to_string();
	}
	
	return bits;
}

string bitsToHex (string bits)
{	
	string hexVal = "";
	
	for (int i = 0; i < bits.length();)
	{
		string byteBits = bits.substr(i, 8);
		i += 8;
		 
		int byteVal = stoi(byteBits, 0, 2);
		
		stringstream ss;
		
		if (byteVal > 15)		
			ss << hex << byteVal;
		else
			ss << "0" << hex << byteVal;
			
		hexVal = hexVal + ss.str();
	}
	
	return hexVal;
}
*/

