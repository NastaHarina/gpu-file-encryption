#pragma once
#include <iostream>
#include <vector>
#include <string>


class AEScipher
{
public:
	// for task
	//std::vector<int> key;
	//std::vector<std::string> file;
	//std::vector <bool> checksum;


	// constructor for read data
	//AEScipher();
	AEScipher(std::string pathkey, std::string folder);

	std::string ReadFile(std::string path);

	void ToHex(const std::string str, std::string& hexstr, bool capital = false);


	//checking the file for checksums
	//void Checksum();

	// for start
	std::string key;
	std::string file;


private:

	void EncryptionAES(/*std::string filetext*/);

	void Descripthion(/*std::string filetext*/);

};
