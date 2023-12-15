#include "Header.h"
#include <fstream>
#include <filesystem>
#include <string>
#include <iostream>
#include <sstream>

namespace fs = std::filesystem;

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
		std::cout << "Error" << std::endl;
	}
	else {
    
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
    std::vector<char> keyforcopy;
    keyforcopy = ReadFile(pathkey);
    std::memcpy(key, keyforcopy.data(), keyforcopy.size());

    std::vector<char> filestr;
    // read folder
    // implement for reading more than one file in a directory 
    for (const auto& entry : fs::directory_iterator(folder)) {
      //std::cout << entry.path() << std::endl;
      std::string en = entry.path().generic_string();
      filestr = ReadFile(en);
      std::memcpy(file, filestr.data(), filestr.size());
	}
}

void AEScipher::WriteFile(const char writedata[4096], const std::string path)
{
	std::ofstream outFile(path, std::ios::binary);

	if (!outFile.is_open()) {
		std::cerr << "Unable to open the file." << std::endl;
	}

	outFile << writedata << std::endl;

	outFile.close();
}


std::vector<char> AEScipher::ReadFile(std::string path) {
	std::ifstream inputFile(path, std::ios::binary);

	if (!inputFile.is_open()) {
		std::cerr << "Unable to open the file." << std::endl;
		return std::vector<char>();
	}

	std::vector<char> buffer(4096); 
	inputFile.read(buffer.data(), buffer.size());
	inputFile.close();
  
	return buffer;
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
