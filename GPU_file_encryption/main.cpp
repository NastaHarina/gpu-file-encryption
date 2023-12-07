#include "Header.h"

int main()
{	

	AEScipher path("C:/Users/Matthew/Desktop/GPU AES/GPU_file_encryption/GPU_file_encryption/key.txt", "C:/Users/Matthew/Desktop/GPU AES/GPU_file_encryption/GPU_file_encryption/data");
	unsigned char * encfile;

	std::cout << "key: ";

	for (int i = 0; path.key[i] != '\0'; ++i) {
		std::cout << "Character at index " << i << ": " << path.key[i] << std::endl;
	}

	std::cout << "data file: " << std::endl;

	for (int i = 0; path.file[i] != '\0'; ++i) {
		std::cout << "Character at index " << i << ": " << path.file[i] << std::endl;
	}

	std::cout << "Input: " << std::endl;

	path.printArray(path.file, 64);

	std::cout << "Encrypted: " << std::endl;

	encfile = path.EncryptionAES();
	path.printArray(encfile, 64);

	std::cout << std::endl << "Decrypted: " << std::endl;

	encfile = path.DecryptionAES();
	path.printArray(encfile, 64);

	// write to file
	path.WriteFile(path.key, "C:/Users/Matthew/Desktop/GPU AES/GPU_file_encryption/GPU_file_encryption/keyforcheck.bin");

	// read file
	std::vector<char> filestr = path.ReadFile("C:/Users/Matthew/Desktop/GPU AES/GPU_file_encryption/GPU_file_encryption/keyforcheck.bin");

	for (char c : filestr) {
		std::cout << c;
	}

	return 0;
}

