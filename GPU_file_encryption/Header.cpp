#include "Header.h"
#include <fstream>
#include <filesystem>
#include <string>
#include <iostream>
#include <sstream>


namespace fs = std::filesystem;

//empty construct
//AEScipher::AEScipher() {
//	this->key = " ";
//	this->file = " ";
//}



AEScipher::AEScipher(std::string pathkey, std::string folder)
{
	std::string KeyData;

	KeyData = ReadFile(pathkey);

	ToHex(KeyData, key);

	std::string filestr;

	// read folder
	for (const auto& entry : fs::directory_iterator(folder)) {
		//std::cout << entry.path() << std::endl;
		std::string en = entry.path().generic_string();
		filestr += ReadFile(en);

	}

	ToHex(filestr, file);


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

void AEScipher::ToHex(const std::string str, std::string hexstr[4096])
{
	//hexstr.resize(str.size() * 2);
	//const size_t a = capital ? 'A' - 1 : 'a' - 1;

	////std::cout <<  << std::endl;

	//for (size_t i = 0, c = str[0] & 0xFF; i < hexstr.size(); c = str[i / 2] & 0xFF)
	//{
	//	hexstr[i++] = c > 0x9F ? (c / 16 - 9) | a : c / 16 | '0';
	//	hexstr[i++] = (c & 0xF) > 9 ? (c % 16 - 9) | a : c % 16 | '0' + ' ';
	//}
	for (int i = 0; str[i] != '\0'; ++i) {
		std::stringstream ss;
		ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(str[i]);
		hexstr[i] = ss.str();
	}
}

void AEScipher::ToString(const std::string str[])
{
	for (int i = 0; str[i] != ""; ++i) {
		std::istringstream iss(str[i]);
		int asciiCode;
		iss >> std::hex >> asciiCode;
		char character = static_cast<char>(asciiCode);
		std::cout << character;
	}
}

void AEScipher::PrintData(std::string fil[])
{
	for (int i = 1; fil[i+1] != ""; ++i) {
		if (fil[i-1] == "0a") {
			std::cout<<std::endl;
		}
		std::cout << fil[i] << " ";
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
