#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char *argv[]){
	if(argc < 2){
	   std::cerr<<"~/Desktop/FS-1/input.txt"<<std::endl;
	   return 1;
	}

	std::string filePath = argv[1];
	std::ifstream inputFile(filePath);

	if(!inputFile){
	   std::cerr<< "Error" <<filePath<< std::endl;
	   return 1;
	}

	std::string line;
	while(std::getline(inputFile,line)){
	   std::cout<<line<<std::endl;
	}

	inputFile.close();
	return 0;
}
