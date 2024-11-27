#include <iostream>
#include <vector>
#include <thread>
#include <numeric>
#include <ctime>
#include <cstdlib>
#include <chrono>

void sum(const std::vector<long long>& array,size_t start,size_t end, long long& partialSum){
partialSum=0;
for(size_t i=start;i<end;++i){
	partialSum += array[i];
}
}

int main(int argc, char* argv[]){
if(argc != 3){
std::cerr<<"Error 1";
return 1;
}

size_t N = std::stoull(argv[1]);
size_t M = std::stoull(argv[2]);

if(N <= 1000000){
std::cerr<<"Error 2";
return 1;
}

std::vector<long long> array(N);
std::srand(std::time(nullptr));
for(size_t i=0; i<N;++i){
array[i] = std::rand();
}

auto start= std::chrono::high_resolution_clock::now();
long long singleThreadSum=0;
for(size_t i=0;i<N;++i){
singleThreadSum += array[i];
}

auto end= std::chrono::high_resolution_clock::now();
auto singleThreadDuration =std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();

size_t sizePart = N/M;
std::vector<std::thread> threads;
std::vector<long long> partialSum(M,0);


for(size_t i=0;i<M;++i){
size_t startId = i*sizePart;
size_t endId = (i==M-1) ? N:startId+sizePart;
threads.emplace_back(sum,std::cref(array),startId,endId,std::ref(partialSum[i]));

for (auto& t:threads){
t.join();
}

long long multiThreadSum =std::accumulate(partialSum.begin(),partialSum.end(),0LL);
end =std::chrono::high_resolution_clock::now();
auto multiThreadDuration =std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();

std::cout<<"Time spent without threads"<<singleThreadDuration<<"ms"<<std::endl;
std::cout<<"Time spent with "<<M<<" threads"<<multiThreadDuration<<"ms"<<std::endl;
std::cout<<"Singlee thread sum"<<singleThreadSum<<std::endl;
std::cout<<"Multi thread sum"<<multiThreadSum<<std::endl;
std::cout<<"finish"<<std::endl;
}
return 0;

}
