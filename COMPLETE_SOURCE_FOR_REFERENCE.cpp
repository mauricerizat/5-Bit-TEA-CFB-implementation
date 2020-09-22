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

const int GLOBAL_CONST_K = 5;

int main()
{
	//Welcome
	cout << "\nWelcome to " << GLOBAL_CONST_K << "-bit CFB TEA Program " << endl;
	cout << "--------------------------------------------------------------" << endl;
	
	string option = ""; //Stores menu choice
	while(option[0] != '3')
	{
		//Menu
		while (true)
		{
			cout << "\nPerform:\n\t1. Encryption\n\t2. Decryption\n\t3. Exit" << endl;
			cout << "\nYour choice: ";
			cin >> option;
			
			if (option[0] != '1' && option[0] != '2' && option[0] != '3') //Invalid option entered
			{
				cout << "Wrong choice. Please try again" << endl; 
				continue;
			}
			
			break;
		}
		
		if (option[0] == '3') //Exit
			break;
		
		//Receiving input and key and processing accordingly
		string inputFileName = "";
		string input = "";
		string key = "";
		cout << "\nEnter input file name: ";
		cin >> inputFileName;
		
		input = readFileData(inputFileName); //Read from input file
		if (input == "__!#*(+_")
			return 0;
		
		cout << "\nEnter key: ";
		cin >> key;
		
		//input = inputFileName; //Irrelevant - for testing
		 
		string inputStream = toBits(input); //Store input as bits - ASCII
		string keyStream = toBits(key); //Store key as bits
		padInput(inputStream, GLOBAL_CONST_K); //Pad input for K
		padKey(keyStream); //Make sure key is 128 bit block
		
		string outputStream = "";
		string outputInHex = "";
		string inputInBits = "";
		string outputFileName = "";
		
		switch(option[0])
		{
		case '1': 	
			{	//ENCRYPTION
				cout << "\nEncrypting..." << endl;
				encryptCFB (inputStream, keyStream, outputStream); //CFB encryption
				cout << "\nEncryption Complete!" << endl;
				cout << "\nEncrypted:\n" << outputStream << endl; //Display encrypted ciphertext
				//Writing ciphertext to file
				cout << "\nEnter file name to write to: ";
				cin >> outputFileName;
				writeFileData(outputFileName, outputStream);	
				cout << "\nEncrypted data written to file " << outputFileName << endl;		
				break;
			}	
		case '2':
			{	//DECRYPTION
				cout << "\nDecrypting..." << endl;
				decryptCFB (input, keyStream, outputStream); //CFB decryption
				cout << "\nDecryption Complete!" << endl;
				string decrypted = toText(outputStream); //Display decrypted text
				cout << "\nDecrypted:\n" << decrypted << endl;
				//Writing decrypted text to file
				cout << "\nEnter file name to write to: ";
				cin >> outputFileName;
				writeFileData(outputFileName, decrypted);
				cout << "\nDecrypted data written to file " << outputFileName << endl;
				break;
			}
		
		case '3':	break;
					
		default:	break;
		

		}
		
		string redo = "";
		
		cout << "\nReturn to main menu? Y/N: ";
		cin >> redo;
		
		if (redo == "N" || redo == "n")
			option = "3";
	}
	
	cout << "\nThank you for using the program " << endl;
	
}

//Write data to given file
void writeFileData(string fileName, string data)
{
	ofstream writeFile;
	writeFile.open ("data/" + fileName);
	writeFile << data << endl;
	writeFile.close();
}

//Read data from given file
string readFileData(string fileName)
{
	string data = "";
	
	ifstream readFile("data/" + fileName); //File to be located in "data" sub-folder
	if (!(readFile.is_open())) //Input file cannot be opened or does not exist
	{
		cout << "\n\tFile named \"" << fileName;
		cout << "\" cannot be opened or does not exist.";
		cout << "\n\tPlease try again with a valid file name.\n" << endl;
		return "__!#*(+_";
	}	
	else //Input file exists
	{	
		//Reading Input file
		try 
		{
			string line;
			while (getline(readFile, line))
				data += (line + "\n");
			
			data = data.substr(0, data.size()-1);
			
		readFile.close();
		} 
		catch (exception& e) //Handles errors that occurs during file reading
		{
			cout << "An error occured while reading file. Please try again.\n" << endl;
			return "__!#*(+_";
		}
	}
	
	return data;
}

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

