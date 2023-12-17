#include "Header.h"
#include <iomanip>

int main()
{
	AEScipher path("key.txt", "folder");
	//unsigned char* encfile;
	
	std::cout << "Writing kes to a file" << std::endl;
	//Delete empty string
	// Удаление символов '\0' внутри строк
	for (auto& vec : path.keyss) {
		vec.erase(std::remove(vec.begin(), vec.end(), '\0'), vec.end());

	}

	// Удаление пустых строк (пустых векторов)
	path.keyss.erase(std::remove_if(path.keyss.begin(), path.keyss.end(), [](const auto& vec) {
		return vec.empty();
		}), path.keyss.end());


	// Удаление символов '\0' внутри строк
	for (auto& vec : path.files) {
		vec.erase(std::remove(vec.begin(), vec.end(), '\0'), vec.end());
	}

	// Удаление пустых строк (пустых векторов)
	path.files.erase(std::remove_if(path.files.begin(), path.files.end(), [](const auto& vec) {
		return vec.empty();
	}), path.files.end());

	std::vector<unsigned char> combinedData;
	for (const auto& key : path.keyss) {
		combinedData.insert(combinedData.end(), key.begin(), key.end());
	}
	
	// Записать объединенные данные в файл
	path.WriteFile(combinedData, "keysEncript.bin");

	std::cout << "Combined data written to output_combined.bin" << std::endl;


	path.files.erase(std::remove_if(path.files.begin(), path.files.end(), [](const auto& vec) {
		return vec.empty();
		}), path.files.end());

	std::cout << "Writing data to a files: "<<std::endl;

	for (std::size_t i = 0; i < path.files.size(); ++i) {
		std::string filename = "dataEncode/fileEncript" + std::to_string(i) + ".bin";
		path.WriteFile(path.files[i], filename);
		std::cout << "Data written to " << filename << std::endl;
	}

	
	std::cout <<std::endl<< "data file: " << std::endl;


	std::cout << "Input: " << std::endl;


	int j = 1;
	for (const auto& line : path.files) {
		std::cout << "initial data file " << j << std::endl;
		for (unsigned char ch : line) {

			std::cout << std::hex << (int)ch << " ";

		}
		j++;
		std::cout << std::endl;
	}
	
	
	std::cout << "Encrypted: " << std::endl;

	for (std::size_t i = 0; i < path.files.size(); ++i) {
		unsigned char* fileData = path.files[i].data();
		unsigned char* keyData = path.keyss[i].data();

		unsigned char* encryptedData = path.EncryptionAES(fileData, keyData);
		path.filesEncript.push_back({ encryptedData, encryptedData + path.files[i].size() });

	}
	
	int i = 1;
	for (const auto& line : path.filesEncript) {
		std::cout << "Encode file " << i << std::endl;
		for (unsigned char ch : line) {
			
			std::cout << std::hex << (int)ch << " ";
			
		}
		i++;
		std::cout << std::endl;
	}

	std::cout << std::endl << "Decrypted: " << std::endl;


	for (std::size_t i = 0; i < path.files.size(); ++i) {
		unsigned char* fileData = path.files[i].data();


		unsigned char* encryptedData1 = path.DecryptionAES(fileData);
		path.filesDescript.push_back({ encryptedData1, encryptedData1 + path.files[i].size() });

	}

	int k = 1;
	for (const auto& line : path.filesDescript) {
		std::cout << "Encode file " << k << std::endl;
		for (unsigned char ch : line) {

			std::cout << std::hex << (int)ch << " ";

		}
		k++;
		std::cout << std::endl;
	}

	/*
	encfile = path.DecryptionAES();
	path.printArray(encfile, 64);*/

	//// write to file
	//path.WriteFile(path.keyss, "C:/Users/Anastasia/Desktop/GPU_file_encryption/GPU_file_encryption/GPU_file_encryption/keyforcheck.bin");

	//// read file
	//std::vector<char> filestr = path.ReadFile("C:/Users/Anastasia/Desktop/GPU_file_encryption/GPU_file_encryption/GPU_file_encryption/keyforcheck.bin");

	//for (char c : filestr) {
	//	std::cout << c;
	//}
	// 
	

	return 0;
}


