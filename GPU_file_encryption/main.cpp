#include "Header.h"
using namespace std;

int main()
{
	AEScipher path("C:/Users/Anastasia/Desktop/GPU_file_encryption/GPU_file_encryption/GPU_file_encryption/key.txt", "C:/Users/Anastasia/Desktop/GPU_file_encryption/GPU_file_encryption/GPU_file_encryption/data");

	cout <<"key "<< path.key << endl;
	cout <<"file " << path.file << endl;

	return 0;
}