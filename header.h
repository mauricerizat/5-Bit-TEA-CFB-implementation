/*
CFB TEA
*/


#include <iostream>
#include <string>
#include <fstream>
#include <bitset>
#include <sstream>
#include <random>

using namespace std;

string toBits(string);
void padInput(string&, int);
void padKey(string&);
void encrypt(const string, string, string&);
//void decrypt(const string, string, string&); Not required for CFB
string toText(string);
void encryptCFB (string, string, string&);
void decryptCFB (string, string, string&);
string stringXor(string, string);
string readFileData(string);
void writeFileData(string, string);
//string bitsToHex (string); /* Alternative - To store ciphertext as hex
//string hexToBits (string);	and to decrypt from hex ciphertext */

const int GLOBAL_CONST_K = 5; //K bit for CFB


