#include "Header.h"

int main()
{
	AEScipher path("key.txt", "data");
	

	//Delete empty string
	//path.keyss.erase(std::remove_if(path.keyss.begin(), path.keyss.end(), [](unsigned char c) { return c == '\0'; }), path.keyss.end());

	std::cout << "key: ";
	path.PrintDataFiles(path.keyss);


	// Delete empty string in files
	//for (auto& vec : path.files) {
	//	vec.erase(std::remove(vec.begin(), vec.end(), '\0'), vec.end());
	//}
	
	path.PrintDataFiles(path.files);

	//path.files.erase(std::remove_if(path.files.begin(), path.files.end(), [](const auto& vec) {
	//	return vec.empty();
	//}), path.files.end());


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

	//let the keys and files have the same data size
	//for (size_t i = 0; i < path.files.size(); ++i) {

		//std::cout << "len path.keyss " << path.keyss.size() << std::endl;

		unsigned char* EncrytData = path.EncryptionAES(path.files[3].data(), path.keyss[3].data());
		size_t length = sizeof(EncrytData) / sizeof(EncrytData[0]);

		size_t length1 = sizeof(path.files[0]);
		std::cout << length << std::endl << length1 << std::endl;



		std::cout << "EncryptionAES: " << std::endl;
		for (size_t i = 0; i < length; ++i) {
			std::cout << static_cast<int>(EncrytData[i]) << " ";
		}
		std::cout << std::endl;

		std::cout << "DecryptionAES: " << std::endl;

		unsigned char* DecryptionData = path.DecryptionAES(EncrytData);

		for (size_t i = 0; i < length; ++i) {
			std::cout << static_cast<int>(EncrytData[i]) << " ";
		}
		std::cout << std::endl;


		//std::cout << std::endl;
	//}
	//std::cout<<EncrytData<<std::endl;
	

	//}

	//path.WriteFile(path.keyss, "C:/Users/Anastasia/Desktop/GPU_file_encryption/GPU_file_encryption/GPU_file_encryption/keyforcheck.bin");

	// read file 
	//std::vector<unsigned char> filestr = path.ReadFile("C:/Users/Anastasia/Desktop/GPU_file_encryption/GPU_file_encryption/GPU_file_encryption/keyforcheck.bin");
	//std::vector<unsigned char> filestr1 = path.ReadFile("C:/Users/Anastasia/Desktop/GPU_file_encryption/GPU_file_encryption/GPU_file_encryption/dataEncode/fileEncript0.bin");
	//std::cout << " filestr1: " << std::endl;
	//path.PrintKey(filestr1);

	return 0;
}

