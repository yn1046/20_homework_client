#pragma once

#include <iostream>
#include <string>
#include <vector>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <arpa/inet.h>
#include <unistd.h>

#include <signal.h>
#include <string.h>

using namespace std;

#define MESSAGE_LEN 1024
#define PORT 10011

namespace cc {
    class ConnectionService {
        const int client_socket;
    public:
        ConnectionService() : client_socket{socket(AF_INET, SOCK_STREAM, 0)} {}

        void connect();

        template<typename T>
        void send_message(T value) {
            send(client_socket, &value, sizeof(value), 0);
        }

        void send_message_string(const string &str);

        template<typename T>
        T receive_message() {
            T value;
            recv(client_socket, &value, sizeof(value), 0);
            return value;
        }

        string receive_message_string();

        void disconnect();
    };
}