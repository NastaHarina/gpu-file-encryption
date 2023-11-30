#include "Header.h"

int main()
{
	AEScipher path("Enter your path for file key", "Enter your path for folder with data file");

	std::cout << "key: ";
	path.PrintData(path.key);

	std::cout << std::endl;


	std::cout <<"file: ";
	path.PrintData(path.file);

	std::cout<<std::endl << "check for rigth" << std::endl;
	std::cout << "key in str: "<<std::endl;


	path.ToString(path.key);

	std::cout << "file in str: ";

	path.ToString(path.file);

	return 0;
}