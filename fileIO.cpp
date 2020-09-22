/*
CFB TEA
*/

#include "header.h"

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





