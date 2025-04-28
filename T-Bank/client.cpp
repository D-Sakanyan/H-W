#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <string>
#include "bank.h"

using namespace std;

int main(){
	const char* shm_name =  "/bank";
	size_t size = 4096;

	int fd = shm_open(shm_name, O_RDWR, 0666);
	if(fd == -1){
		perror("shm_open");
		exit(-1);
	}

	void* ptr = mmap(nullptr, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if(ptr == MAP_FAILED){
		perror("mmap");
		exit(1);
	}

	TBank* bank = reinterpret_cast<TBank*>(ptr);
	Cell* cell = reinterpret_cast<Cell*>((char*)ptr + sizeof(TBank));

	string line;
	//std::cout<<"command";
	while(getline(std::cin,line)){
		stringstream ss(line);
		string cmd;
		ss >> cmd;

	if(cmd == "get_balance"){
		int acc_num;
		ss >> acc_num;

	if(acc_num < 0 || acc_num >= bank->size){
		std::cout<<"wrong num of account";
		continue;
	}
	std::cout<<"num "<<acc_num<<" "<<bank->cells[acc_num].cur_b;
	}else{
 		std::cout<<"unknown";
	}
	}
	munmap(ptr,size);
	close(fd);
	return 0;

}
