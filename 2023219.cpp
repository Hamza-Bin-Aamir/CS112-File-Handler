#include <iostream>
#include <fstream> // need this for file handling
#include <exception>

using namespace std;

class file_not_found : public exception{};

struct TokenData{
	string* Ptr;
	int Length;
};

void writeFile(string Loc, string Write)
{
	ofstream file;
	file.open(Loc);

	if (!file.is_open()) 
	{
		cout << "Error opening file: " << Loc << endl;
		return;
  	}

	file << Write;

	file.close();
}

void readFile(string Loc)
{
	ifstream file;
	string line;

	file.open(Loc);

	if (!file.is_open()) 
	{
		cout << "Error opening file: " << Loc << endl;
		return;
  	}

	while(!file.eof()){
		getline(file, line);
		cout << line;
	}

	file.close();
}

void appendFile(string Loc, string Write)
{
	ofstream file;
	file.open(Loc, ios::app);

	if (!file.is_open()) 
	{
		cout << "Error opening file: " << Loc << endl;
		return;
  	}

	file << Write;

	file.close();
}

void overwriteFile(string Loc, string Write)
{
	ofstream file;
	file.open(Loc, ios::trunc);

	if (!file.is_open()) 
	{
		cout << "Error opening file: " << Loc << endl;
		return;
  	}

	file << Write;

	file.close();
}

TokenData splitText(string Loc)
{
	ifstream file;
	string* data = new string[100];
	file.open(Loc);

	if (!file.is_open()) 
	{
		cout << "Error opening file: " << Loc << endl;
		throw new file_not_found;
  	}

	int i = 0;

	while(!file.eof())
	{
		if(i > 99)
		{
			cout << "Warning, a maximum of 100 tokens is allowed, terminating the splitting early";
			break;
		}
		file >> data[i];
		i++;
	}

	TokenData ret;
	ret.Length = i;
	ret.Ptr = data;

	return ret;
}

void readWrite(string Loc, string Write)
{
	fstream file; string line;
	file.open(Loc);

	if (!file.is_open()) 
	{
		cout << "Error opening file: " << Loc << endl;
		return;
  	}

	while(!file.eof()){
		getline(file, line);
		cout << line;
	}

	file << Write;

	file.close();
}

int main()
{
	char userChoice[5]; // we take a string because the user might accidentally enter multiple chars, we will always use first char
	char fileName[100]; char fileData[100];

	cout << "Welcome to File Manager v0.0.1" << endl;

	while(true){
		cout << "Here are your available options: \n 1. Write to a text file (w) \n 2. Read every line from a text file (r)" << endl
			<< " 3. Appending to the end of a text file (a) \n 4. Overwrite the whole file (o) \n 5. Split text file by whitespace (s)" << endl
			<< " 6. Both read file, then write to it (b) \n 7. Exit(e)"
			<< endl << "Please enter your choice: ";	
		cin.getline(userChoice, sizeof(userChoice)); // getline is convenient for line writing and it runs into less errors if you use it everywhere rather than mix it with "<<"

		if(tolower(userChoice[0]) == 'e'){
			break;
		}
		try{
			switch (tolower(userChoice[0])){
				case 'w':
					cout << "Please enter the path to file: ";
					cin.getline(fileName, sizeof(fileName));
					cout << "Please enter the data you will send to the file (max 100 chars): ";
					cin.getline(fileData, sizeof(fileData));

					writeFile(fileName, fileData);
					break;

				case 'r':
					cout << "Please enter the path to file: ";
					cin.getline(fileName, sizeof(fileName));
					readFile(fileName);
					cout << endl;
					break;

				case 'a':
					cout << "Please enter the path to file: ";
					cin.getline(fileName, sizeof(fileName));
					cout << "Please enter the data you will send to the file (max 100 chars): ";
					cin.getline(fileData, sizeof(fileData));

					appendFile(fileName, fileData);

				case 'o':
					cout << "Please enter the path to file: ";
					cin.getline(fileName, sizeof(fileName));
					cout << "Please enter the data you will send to the file (max 100 chars): ";
					cin.getline(fileData, sizeof(fileData));

					overwriteFile(fileName, fileData);

					break;

				case 's':
					cout << "Please enter the path to file: ";
					cin.getline(fileName, sizeof(fileName));
					TokenData returnedInfo;
					returnedInfo = splitText(fileName);

					for(int i = 0; i < returnedInfo.Length; i++){
						cout << "token: " << returnedInfo.Ptr[i] << endl;
					}

					cout << endl;

					break;

				case 'b':
					cout << "Please enter the path to file: ";
					cin.getline(fileName, sizeof(fileName));
					cout << "Please enter the data you will send to the file (max 100 chars): ";
					cin.getline(fileData, sizeof(fileData));

					readWrite(fileName, fileData);

					break;

				default:
					cout << "Invalid input, please try again";
			}
		}	
		catch(const file_not_found& E){
			cout << "Error reading file: not found";
		}
		catch (const ios_base::failure& E){
			cout << "Input/Output failure, is the data too long or did you enter unrecognised special characters (like from unicode)?";
		}
		catch (const fstream::failure& E){
			cout << "General file operation failure";
		}
		catch (...)
		{
			cout << "Unknown error";
		}
	}

	cout << "Successfully exited";
}