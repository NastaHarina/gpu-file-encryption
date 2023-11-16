#pragma once
#include <iostream>
#include <vector>
#include <string>
using namespace std;


class AEScipher
{
public:
	// for task
	//std::vector<int> key;
	//std::vector<std::string> file;
	//std::vector <bool> checksum;


	// constructor for read data
	//AEScipher();
	AEScipher(string pathkey, string folder);

	string ReadFile(string path);


	//checking the file for checksums
	//void Checksum();

	// for start
	string key;
	string file;


private:

	void EncryptionAES(/*std::string filetext*/);

	void Descripthion(/*std::string filetext*/);

};
