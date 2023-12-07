#include "Header.h"

int main()
{
	AEScipher path("C:/Users/Anastasia/Desktop/GPU_file_encryption/GPU_file_encryption/GPU_file_encryption/key.txt", "C:/Users/Anastasia/Desktop/GPU_file_encryption/GPU_file_encryption/GPU_file_encryption/data");

	std::cout << "key: ";

	for (int i = 0; path.key[i] != '\0'; ++i) {
		std::cout << "Character at index " << i << ": " << path.key[i] << std::endl;
	}


	std::cout <<"file: "<<std::endl;

	for (int i = 0; path.file[i] != '\0'; ++i) {
		std::cout << "Character at index " << i << ": " << path.file[i] << std::endl;
	}

	path.WriteFile(path.key, "C:/Users/Anastasia/Desktop/GPU_file_encryption/GPU_file_encryption/GPU_file_encryption/keyforcheck.bin");

	// read file
	std::vector<char> filestr = path.ReadFile("C:/Users/Anastasia/Desktop/GPU_file_encryption/GPU_file_encryption/GPU_file_encryption/keyforcheck.bin");


	for (char c : filestr) {
		std::cout << c;
	}


	return 0;
}

