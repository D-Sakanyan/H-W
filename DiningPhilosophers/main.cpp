#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <fcntl.h>

#define N 5
sem_t* sticks[N];

void philosopher(int id) {
    int left = id;
    int right = (id + 1) % N;

    bool first_right = (id == 0);

    while (true) {
        std::cout << "Philosopher " << id << " is thinking..." << std::endl;
        sleep(2);

        if (first_right) {
            sem_wait(sticks[right]);
            sem_wait(sticks[left]);
        } else {
            sem_wait(sticks[left]);
            sem_wait(sticks[right]);
        }

        std::cout << "Philosopher " << id << " is eating..." << std::endl;
        sleep(2);

        sem_post(sticks[left]);
        sem_post(sticks[right]);
    }
}

int main() {
    for (int i = 0; i < N; i++) {
        std::string sem_name = "/stick" + std::to_string(i);
        sticks[i] = sem_open(sem_name.c_str(), O_CREAT, 0666, 1);
    }

    pid_t pids[N];
    for (int i = 0; i < N; i++) {
        pids[i] = fork();
        if (pids[i] == 0) {
            philosopher(i);
            return 0;
        }
    }

    for (int i = 0; i < N; i++) {
        wait(NULL);
    }

    for (int i = 0; i < N; i++) {
        sem_close(sticks[i]);
        sem_unlink(("/stick" + std::to_string(i)).c_str());
    }

    return 0;
}
