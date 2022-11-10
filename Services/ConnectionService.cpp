#include "ConnectionService.h"

void cc::ConnectionService::connect() {
    if (client_socket == -1) {
        perror("socket: ");
        exit(-1);
    }

    struct sockaddr_in client;
    client.sin_family = AF_INET;
    client.sin_port = htons(PORT); // Port no. of server
    client.sin_addr.s_addr = INADDR_ANY;
    //client.sin_addr.s_addr=inet_addr("127.0.0.1"); // Provide IP address of server
    bzero(&client.sin_zero, 0);

    if ((::connect(client_socket, (struct sockaddr *) &client, sizeof(struct sockaddr_in))) == -1) {
        perror("connect: ");
        exit(-1);
    }


}

void cc::ConnectionService::send_message_string(const string &str) {
    const char *cstr = str.c_str();
    send(client_socket, cstr, sizeof(cstr), 0);
}

string cc::ConnectionService::receive_message_string() {
    char str[MESSAGE_LEN];
    recv(client_socket, str, sizeof(str), 0);
    return string() + str;
}


void cc::ConnectionService::disconnect() {
    close(client_socket);
}
