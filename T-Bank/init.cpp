#include <iostream>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include "bank.h"

using namespace std;

int main(int argc, char* argv[]) {
    const int N = atoi(argv[1]);
    int fd = shm_open("/bank", O_CREAT | O_RDWR, 0666);
    if (fd == -1) {
        perror("shm_open");
        return 1;
    }

    size_t total_size = sizeof(TBank) + N * sizeof(Cell);
    if (ftruncate(fd, total_size) == -1) {
        perror("ftruncate");
        return 1;
    }

    void* ptr = mmap(nullptr, total_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (ptr == MAP_FAILED) {
        perror("mmap");
        return 1;
    }

    close(fd);

    TBank* bank = new(ptr) TBank;
    Cell* cells = reinterpret_cast<Cell*>(reinterpret_cast<char*>(bank) + sizeof(TBank));
    bank->size = N;

for(int i = 0; i<N; i++){
    cells[i].cur_b = 0;
    cells[i].min = 0;
    cells[i].max = 500;
    cells[i].frozen = false;
}
    munmap(ptr, total_size);


// shm_unlink("/bank"); // удалить разделяемую память, если больше не нужна
    return 0;
}

