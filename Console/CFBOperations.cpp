/*
CFB TEA
*/

#include "header.h"

//Perform CFB TEA Decryption
void decryptCFB (string cipherStream, string keyStream, string& outStream)
{
	string IVStream = cipherStream.substr(0, 64); //Extrace IV from ciphertext
	cipherStream = cipherStream.substr(64);
	
	for (int i = 0; i < cipherStream.size();)
	{
		string decryptedIVStream = "";
		encrypt (IVStream, keyStream, decryptedIVStream); //Encrypt IV
		string firstKCipherBits = cipherStream.substr(i, GLOBAL_CONST_K); //Extract first K bits from ciphertext
		i += GLOBAL_CONST_K; //Increment index
		string firstKDecryptedIVBits = decryptedIVStream.substr(0, GLOBAL_CONST_K); //Extracr first K bits from IV
		string nextKPlainBits = stringXor(firstKCipherBits, firstKDecryptedIVBits); //XOR
		outStream += nextKPlainBits; //Add K bit XOR result to decrypted text
		IVStream = IVStream.substr(GLOBAL_CONST_K) + firstKCipherBits; //Update IV
	}
}

//Perform CFB TEA Encryption
void encryptCFB (string inputStream, string keyStream, string& outStream)
{
	//Generate pseudorandom 64-bit IV
	srand(time(0));
	uint64_t IV = rand() % 0xffffffff;
	string IVStream = bitset<64>(IV).to_string(); //Convert IV to bits
	outStream += IVStream; //Insert IV in ciphertext
	
	for (int i = 0; i < inputStream.size();)
	{
		string encryptedIVStream = ""; //Encrypt IV
		encrypt (IVStream, keyStream, encryptedIVStream);	
		string firstKInputBits = inputStream.substr(i, GLOBAL_CONST_K); //Extract first K bits from plaintext
		i += GLOBAL_CONST_K; //Increment index
		string firstKEncryptedIVBits = encryptedIVStream.substr(0, GLOBAL_CONST_K); //Extracr first K bits from IV
		string nextKCipherBits = stringXor(firstKInputBits, firstKEncryptedIVBits); //XOR
		outStream += nextKCipherBits; //Add K bit XOR result to decrypted text
		IVStream = IVStream.substr(GLOBAL_CONST_K) + nextKCipherBits; //Update IV
	}
}
