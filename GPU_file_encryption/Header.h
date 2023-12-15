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
	//std::vector <bool> checks
  

	AEScipher(std::string pathkey, std::string folder);

	void WriteFile(const char writedata[4096], const std::string path);

	std::vector<char> ReadFile(std::string path);

	char key [4096];
	char file[4096];


	// for start
	std::string key;
	std::string file;


private:

	void EncryptionAES(/*std::string filetext*/);

	void Descripthion(/*std::string filetext*/);

};
