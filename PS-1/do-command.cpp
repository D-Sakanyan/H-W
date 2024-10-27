#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <vector>
#include <cstring>
#include <chrono>

int do_command(char** argv){
	if(argv==nullptr || argv[0]==nullptr){
		std::cerr<<"Err1";
		return -1;
	}

	auto start = std::chrono::high_resolution_clock::now();
	pid_t pid = fork();

	if(pid<0){
		std::perror("fork");
		return -1;
	}
	if(pid==0){
		execvp(argv[0],argv);
		std::perror("exec");
		return -1;
	}if(pid>0){
                int status;

                waitpid(pid,&status,0);

                auto end = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
		if(WIFEXITED(status)){
	                std::cout<<WEXITSTATUS(status)<<duration.count()<<std::endl;
		}else{
			std::cout<<"Err3";
		}
	return WEXITSTATUS(status);
      }
return 0;
}

int main(int argc, char** argv){
	char** args= new char*[argc];

	for(int i=0;i<argc;++i){
		args[i-1] = argv[i];
	}
	args[argc-1] = nullptr;

	for(int i=0;i<argc-1;++i){
		std::cout<<"argv["<<i<<"] "<<argv[i]<<std::endl;
	}

	int status = do_command(args);

	delete[] args;

	return status;
return 0;
}
