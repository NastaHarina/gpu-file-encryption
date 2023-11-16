#include "Header.h"
#include <fstream>
#include <filesystem>
#include <string>
#include <iostream>

//using namespace std;

namespace fs = std::filesystem;

//AEScipher::AEScipher() {
//	this->key = " ";
//	this->file = " ";
//}



AEScipher::AEScipher(string pathkey, string folder)
{

	key = ReadFile(pathkey);
	// read folder
	for (const auto& entry : fs::directory_iterator(folder)) {
		//std::cout << entry.path() << std::endl;
		string en = entry.path().generic_string();
		file += ReadFile(en);

	}


}


string AEScipher::ReadFile(string path) 
{
	ifstream fin;
	fin.open(path);

	string str, str1 = "";

	if (!fin.is_open()) {
		//std::cout << "Error" << std::endl;
	}
	else {

		//std::cout << "Good" << std::endl;

		
		while (!fin.eof()) {
			str = "";
			std::getline(fin, str);
			str1 +=str +"\n";
			//cout << str << endl;
			//key = str;
		}
	}


	fin.close();
	return str1;
}

//void AEScipher::Checksum()
//{
//
//}

void AEScipher::EncryptionAES(/*std::string filetext*/) 
{

}

void AEScipher::Descripthion(/*std::string filetext*/) 
{

}
