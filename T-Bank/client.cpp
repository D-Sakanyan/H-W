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

        int fd = shm_open(shm_name, O_RDWR, 0666);
        if(fd == -1){
                perror("shm_open");
                exit(-1);
        }

        struct stat statbuf;
        fstat(fd, &statbuf);

        size_t size = statbuf.st_size;

        void* ptr = mmap(nullptr, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
        if(ptr == MAP_FAILED){
                perror("mmap");
                exit(1);
        }

        TBank* bank = static_cast<TBank*>(ptr);

	std::cout<<"Commands:"<<std::endl;
        std::cout<<"get_balance_curr/min/max"<<std::endl;
	std::cout<<"froze/unfroze"<<std::endl;
	std::cout<<"transfer"<<std::endl;
	std::cout<<"add"<<std::endl;
	std::cout<<"withdraw"<<std::endl;

	string line;
        while(getline(std::cin,line)){
                stringstream ss(line);
                string cmd;
                ss >> cmd;

	if(cmd == "get_balance_curr"){
		int acc_num;
		
		if(!(ss>>acc_num)){
			std::cout<<"Missing number of account"<<std::endl;
			continue;
		}
		
		int result = get_balance_curr(bank, acc_num);
		
		if(result >= 0){
			std::cout<<"Num: "<<acc_num<<" , "<<"curr balance: "<<bank->cells[acc_num].cur_b<<std::endl;
			continue;
		}
		else if(result == -1){
			std::cout<<"Wrong number of account"<<std::endl;
			continue;
		}
	}

	if(cmd == "get_balance_min"){
		int acc_num;

		if(!(ss>>acc_num)){
			std::cout<<"Missing number of account"<<std::endl;
                	continue;
		}

		int result = get_balance_min(bank, acc_num);

		if(result >= 0){
			std::cout<<"Num: "<<acc_num<<" , "<<"min balance: "<<bank->cells[acc_num].min<<std::endl;
			continue;
		}
		else if(result == -1){
			std::cout<<"Wrong number of account"<<std::endl;
			continue;
		}
	}

	if(cmd == "get_balance_max"){
		int acc_num;
		
		if(!(ss>>acc_num)){
			std::cout<<"Missing number of account"<<std::endl;
			continue;
		}

		int result = get_balance_max(bank, acc_num);

		if(result >= 0){
			std::cout<<"Num: "<<acc_num<<" , "<<"max balance: "<<bank->cells[acc_num].max<<std::endl;
			continue;
		}
		else if(result == -1){
			std::cout<<"Wrong number of account"<<std::endl; 
			continue;
		}
	}

	if(cmd == "froze"){
		int acc_num;
		
		if(!(ss>>acc_num)){
                        std::cout<<"Missing number of account"<<std::endl;
                        continue;
                }

		int result = froze(bank, acc_num);

		if(result == 0){
			std::cout<<"The account is frozen"<<std::endl;
			bank->cells[acc_num].is_frozen = 1;
			continue;
		}
		else if(result == 1){
			std::cout<<"The account is already frozen"<<std::endl;
			continue;
		}
		else if(result == -1){
			std::cout<<"Wrong number of account"<<std::endl;
			continue;
		}
	}

	if(cmd == "unfroze"){
                int acc_num;

                if(!(ss>>acc_num)){
                        std::cout<<"Missing number of account"<<std::endl;
                        continue;
                }

		int result = unfroze(bank, acc_num);
		
		if(result == 1){
                        std::cout<<"The account is unfrozen"<<std::endl;
                        bank->cells[acc_num].is_frozen = 0;
                	continue;
		}
		else if(result == 0){
                        std::cout<<"The account is already unfrozen"<<std::endl;
			continue;
		}
		else if(result == -1){
                        std::cout<<"Wrong number of account"<<std::endl;
			continue;
		}
        }

	if(cmd == "transfer"){
	int from, to, amount;
	

		if(!(ss>>from>>to>>amount)){
			std::cout<<"Wrong format"<<std::endl;
                        continue;
		}

		int result = transfer(bank, from, to, amount);

		switch(result){
			case 0:
			      std::cout<<"Transfer "<<"from "<<from<<" to "<<to<<" is successful"<<std::endl;
			      continue;
			case -1:
			      std::cout<<"Wrong number of account"<<std::endl;
			      continue;
			case -2:
			      std::cout<<"Cannot transfer to the same account"<<std::endl;
			      continue;
			case -3:
			      std::cout<<"Account "<<from<<" is frozen"<<std::endl;
			      continue;
			case -4:
			      std::cout<<"Account "<<to<<" is frozen"<<std::endl;
			      continue;
			case -5:
		      	      std::cout<<"Insufficient funds"<<std::endl;
			      continue;
		}

	}

	if(cmd == "add"){
		int amount;

		if(!(ss>>amount)){
			std::cout<<"Wrong format";
			continue;
		}

		int result = add(bank, amount);

		switch(result){
			case 0:
				for(int i = 0; i < static_cast<int>(bank->size); i++){
                                        if(bank->cells[i].is_frozen == 1){
                                                std::cout<<"Account "<<i<<" is frozen"<<std::endl;
                                                continue;
                                        }
                                        else if(bank->cells[i].is_frozen == 0){
                                               	bank->cells[i].cur_b += amount;
                        	        	std::cout<<amount<<" was deposited into "<<i<<std::endl;
			        	    	continue;
                                        }
                                }
                                continue;
			case -1:
				std::cout<<"Amount must be less than 20000"<<std::endl;
				continue;
			case -2:
				std::cout<<"Amount must be greater than 0"<<std::endl;
				continue;
		}
	}

	if(cmd == "withdraw"){
		int amount;

		if(!(ss>>amount)){
			std::cout<<"Wrong format"<<std::endl;
			continue;
		}

		int result = withdraw(bank, amount);

		switch(result){
			case 0:
				for(int i = 0; i < static_cast<int>(bank->size); i++){
					if(bank->cells[i].is_frozen == 1){
                                                std::cout<<"Account "<<i<<" is frozen"<<std::endl;
                                                continue;
                                        }
					else if(amount > bank->cells[i].cur_b){
						std::cout<<"There is not enough balance in "<<i<<std::endl;
						continue;
					}
					else if(bank->cells[i].is_frozen == 0){
						std::cout<<amount<<" was withdrawn from "<<i<<std::endl;
						bank->cells[i].cur_b -= amount;
						continue;
					}
				}
				continue;
			case -1:
                                std::cout<<"Amount must be less than 20000"<<std::endl;
                                continue;
                        case -2:
                                std::cout<<"Amount must be greater than 0"<<std::endl;
                                continue;		
		}
	
	
	}

	else{
                std::cout<<"unknown"<<std::endl;
        }
}

        munmap(ptr,size);	
        close(fd);
        return 0;

}
