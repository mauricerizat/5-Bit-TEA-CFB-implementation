/*
CFB TEA
*/

#include "header.h"

//Perform TEA encryption on block
void encrypt(const string in, string k, string& out)
{
	uint32_t v0 = stol(in.substr(0, 32), 0, 2); //First 32 bits
	uint32_t v1 = stol(in.substr(32), 0, 2); //Next 32 bits
	uint32_t k0 = stol(k.substr(0, 32), 0, 2); //Key is split into four blocks of 32 bits each
	uint32_t k1 = stol(k.substr(32, 32), 0, 2);
	uint32_t k2 = stol(k.substr(64, 32), 0, 2);
	uint32_t k3 = stol(k.substr(96), 0, 2);
	uint64_t sum = 0;
	uint64_t delta = 0x9e3779b9;
	int i;
	
	for (i = 0; i < 32; ++i)
	{
		sum += delta;
		v0 += (v1 << 4) + k0 ^ v1 + sum ^ (v1 >> 5) + k1;
		v1 += (v0 << 4) + k2 ^ v0 + sum ^ (v0 >> 5) + k3;
	}
	
	out = out + bitset<32>(v0).to_string(); //Store first 32 bits in output block
	out = out + bitset<32>(v1).to_string();	//Store next 32 bits in output block
}

/*
//Perform TEA encryption on block - Not used in this Task
void decrypt(const string in, string k, string& out)
{
	uint32_t v0 = stol(in.substr(0, 32), 0, 2); //First 32 bits
	uint32_t v1 = stol(in.substr(32), 0, 2); //Next 32 bits
	uint32_t k0 = stol(k.substr(0, 32), 0, 2); //Key is split into four blocks of 32 bits each
	uint32_t k1 = stol(k.substr(32, 32), 0, 2);
	uint32_t k2 = stol(k.substr(64, 32), 0, 2);
	uint32_t k3 = stol(k.substr(96), 0, 2);
	uint64_t sum = 0xC6EF3720;
	uint64_t delta = 0x9e3779b9;
	int i;
	
	for (i = 0; i < 32; ++i)
	{
		v1 -= (v0 << 4) + k2 ^ v0 + sum ^ (v0 >> 5) + k3; 
		v0 -= (v1 << 4) + k0 ^ v1 + sum ^ (v1 >> 5) + k1; 
		sum -= delta;
	}
	
	out = out + bitset<32>(v0).to_string(); //Store first 32 bits in output block
	out = out + bitset<32>(v1).to_string(); //Store next 32 bits in output block
}
*/
