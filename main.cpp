/*
CFB TEA
*/

#include "header.h"
#include <chrono> 

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
				auto start = chrono::high_resolution_clock::now(); 
				encryptCFB (inputStream, keyStream, outputStream); //CFB encryption
				auto stop = chrono::high_resolution_clock::now();
				auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
				cout << "Encryption Complete! - Duration: " << duration.count() << "ms " << endl;
				//cout << "\nEncryption Complete!" << endl;
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





