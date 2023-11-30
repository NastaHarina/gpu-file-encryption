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

	void ToHex(const std::string str, std::string hexstr[4096]);

	//for check, then delete
	void ToString(const std::string str[]);

	// for check, then delete
	void PrintData(std::string fil[]);


	//checking the file for checksums
	//void Checksum();

	// for start
	// size key?
	std::string key [4096];
	std::string file[4096];


private:

	void EncryptionAES(/*std::string filetext*/);

	void Descripthion(/*std::string filetext*/);

};
