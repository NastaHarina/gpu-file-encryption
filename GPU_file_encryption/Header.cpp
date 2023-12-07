#include "Header.h"
#include <fstream>
#include <filesystem>
#include <string>
#include <iostream>
#include <sstream>


namespace fs = std::filesystem;



AEScipher::AEScipher(std::string pathkey, std::string folder)
{
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
