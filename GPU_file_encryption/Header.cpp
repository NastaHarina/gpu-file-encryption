#include "Header.h"
#include <fstream>
#include <filesystem>
#include <string>
#include <iostream>


namespace fs = std::filesystem;

//AEScipher::AEScipher() {
//	this->key = " ";
//	this->file = " ";
//}



AEScipher::AEScipher(std::string pathkey, std::string folder)
{
	key= ReadFile(pathkey);
	ToHex(key, key);

	// read folder
	for (const auto& entry : fs::directory_iterator(folder)) {
		//std::cout << entry.path() << std::endl;
		std::string en = entry.path().generic_string();
		file += ReadFile(en);

	}

	ToHex(file, file);


}


std::string AEScipher::ReadFile(std::string path) 
{
	std::ifstream fin;
	fin.open(path);

	std::string str, str1 = "";

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

void AEScipher::ToHex(const std::string str, std::string& hexstr, bool capital)
{
	hexstr.resize(str.size() * 2);
	const size_t a = capital ? 'A' - 1 : 'a' - 1;

	//std::cout <<  << std::endl;

	for (size_t i = 0, c = str[0] & 0xFF; i < hexstr.size(); c = str[i / 2] & 0xFF)
	{
		hexstr[i++] = c > 0x9F ? (c / 16 - 9) | a : c / 16 | '0';
		hexstr[i++] = (c & 0xF) > 9 ? (c % 16 - 9) | a : c % 16 | '0' + ' ';
	}
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
