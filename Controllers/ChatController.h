#pragma once

#include <string>
#include <utility>
#include <thread>

#include "../Services/ConnectionService.h"
#include "../Enums/ActionTypes.h"
#include "../Enums/CommandTypes.h"

using namespace std;

namespace cc {
    class ChatController {
    private:
        ConnectionService *_connectionService;
        thread t_send;
        thread t_receive;
        bool quitting = false;

    public:
        explicit ChatController(ConnectionService *connectionService)
                : _connectionService(connectionService) {
            initialize();
        };
        void initialize();
        void do_signup();
        void do_login();
        void do_quit();
        void enter_chat();
        void handle_send();
        void handle_receive();
        void show_messages();
        string get_input();
        COMMAND_TYPES parse_command(const string &command);
        void do_command(COMMAND_TYPES command);
        static void show_help();
        static ACTION_TYPES get_action();
        static string gen_password(const string &password);
    };
} // namespace cc