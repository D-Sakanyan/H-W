#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <thread>
#include <mutex>

std::mutex mtx;

void handle_client(int client_socket) {
    char buffer[1001];

    while (true) {

        int rs = recv(client_socket, buffer, 1000, 0);
        if (rs == -1) {
            perror("recv error");
            close(client_socket);
            return;
        }
        if (rs == 0) {
            break;
        }

        std::lock_guard<std::mutex> lock(mtx);
        buffer[rs] = '\0';
        std::cout << "Received message: " << buffer << std::endl;

        const char* response = "Message received";
        send(client_socket, response, strlen(response), 0);
    }

    close(client_socket);
}

int main() {
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("socket creation error");
        exit(errno);
    }

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(8888);

    if (bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
        perror("bind failed");
        exit(errno);
    }


    if (listen(server_socket, 10) < 0) {
        perror("listen failed");
        exit(errno);
    }
    std::cout << "Server is waiting for connections...\n";

    while (true) {
        int client_socket;
        struct sockaddr_in client_address;
        unsigned int client_addr_len = sizeof(client_address);

	client_socket = accept(server_socket, (struct sockaddr*)&client_address, &client_addr_len);
        if (client_socket < 0) {
            perror("accept failed");
            exit(errno);
        }

        std::cout << "Connected to client: " << inet_ntoa(client_address.sin_addr) << "\n";

        std::thread client_thread(handle_client, client_socket);
        client_thread.detach();
    }

    close(server_socket);
    return 0;
}
