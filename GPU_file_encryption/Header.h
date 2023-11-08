#pragma once
#include <iostream>
#include <vector>


class AEScipher
{
public:
	// for task
	//std::vector<int> key;
	//std::vector<std::string> file;
	//std::vector <bool> checksum;

	// for start
	int key;
	std::string file;

	// constructor for read data
	AEScipher(std::string pathkey, std::string folder);

	//checking the file for checksums
	//void Checksum();

private:

	void EncryptionAES(/*std::string filetext*/);

	void Descripthion(/*std::string filetext*/);

};
