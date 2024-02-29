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

	// then must be function
	for (int i = 0; i < path.keyss.size(); i++) {

		unsigned char* Encrytkeyss = new unsigned char[path.keyss[i].size()];//path.EncryptionAES(path.files[3].data(), path.keyss[3].data());
		unsigned char* EncrytFiles = new unsigned char[path.files[i].size()];

		std::copy(path.keyss[i].begin(), path.keyss[i].end(), Encrytkeyss);
		std::copy(path.files[i].begin(), path.files[i].end(), EncrytFiles);


		//size_t length = sizeof(EncrytData) / sizeof(EncrytData[0]);

		size_t length1 = path.files[i].size();
		std::cout << std::endl << length1 << std::endl;

		int sum1 = path.CheckSums(EncrytFiles, length1);
		std::cout << "Sum " << sum1 << std::endl;

		unsigned char* EncrytData = path.EncryptionAES(EncrytFiles, Encrytkeyss);

		std::cout << "EncryptionAES: " << std::endl;
		for (size_t i = 0; i < length1; ++i) {
			std::cout << static_cast<int>(EncrytData[i]) << " ";
		}
		std::cout << std::endl;

		std::cout << "DecryptionAES: " << std::endl;

		unsigned char* DecryptionData = path.DecryptionAES(EncrytData);

		int sum2 = path.CheckSums(DecryptionData, length1);
		std::cout << "Sum " << sum2 << std::endl;

		for (size_t i = 0; i < length1; ++i) {
			std::cout << static_cast<int>(DecryptionData[i]) << " ";
		}
		std::cout << std::endl;
	}



	return 0;
}

