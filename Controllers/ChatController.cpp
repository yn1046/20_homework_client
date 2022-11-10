#include "ChatController.h"
#include "../Enums/ActionTypes.h"
#include "../Helpers/strutil.h"
#include <iostream>

void cc::ChatController::initialize() {
    _connectionService->connect();
    ACTION_TYPES action = get_action();
    _connectionService->send_message<ACTION_TYPES>(action);

    switch (action) {
        case ACTION_TYPES::LOGIN:
            do_login();
            break;
        case ACTION_TYPES::SIGNUP:
            do_signup();
            break;
        case ACTION_TYPES::QUIT:
        default:
            exit(EXIT_SUCCESS);

    }
}

void cc::ChatController::do_signup() {
    string login, password;
    bool ok = false;
    while (!ok) {
        cout << "Choose login" << endl;
        cin >> login;
        _connectionService->send_message_string(login);

        ok = _connectionService->receive_message<bool>();
        if (!ok) {
            cout << "Login already in use" << endl;
        }
    }
    cout << "Choose password" << endl;
    cin >> password;
    _connectionService->send_message_string(password);

    enter_chat();
}

void cc::ChatController::do_login() {
    string login, password;
    bool ok = false;

    while (!ok) {
        cout << "Enter login" << endl;
        cin >> login;
        _connectionService->send_message_string(login);

        ok = _connectionService->receive_message<bool>();
        if (!ok) {
            cout << "User not found" << endl;
        }
    }

    ok = false;
    while (!ok) {
        cout << "Enter password" << endl;
        cin >> password;
        _connectionService->send_message_string(password);

        ok = _connectionService->receive_message<bool>();
        if (!ok) {
            cout << "Bad password" << endl;
        }
    }

    enter_chat();

}

ACTION_TYPES cc::ChatController::get_action() {
    int action = 0;
    do {
        cout << (action < 0 || action > 2 ? "Incorrect input"
                                          : "Welcome to ConsoleChat!")
             << endl;
        cout << "Please select an action:" << endl;
        cout << "1 - login" << endl;
        cout << "2 - sign up" << endl;
        cout << "0 - exit" << endl;

        cin >> action;
    } while (action < 0 || action > 2);

    return (ACTION_TYPES) action;
}

void cc::ChatController::enter_chat() {
    thread ts(&cc::ChatController::handle_send, this);
    thread tr(&cc::ChatController::handle_receive, this);

    t_send = move(ts);
    t_receive = move(tr);

    if (t_send.joinable())
        t_send.join();
    if (t_receive.joinable())
        t_receive.join();

    _connectionService->disconnect();
    exit(EXIT_SUCCESS);
}

COMMAND_TYPES cc::ChatController::parse_command(const string &command) {
    switch (command[1]) {
        case 'h':
            return COMMAND_TYPES::HELP;
        case 'q':
        case '0':
            return COMMAND_TYPES::QUIT;
        default:
            return COMMAND_TYPES::UNKNOWN;
    }
}

void cc::ChatController::handle_send() {
    while (!quitting) {
        string input = get_input();

        if (input.length() > 0) {
            if (input[0] == '/') {
                do_command(parse_command(input));
            } else {
                _connectionService->send_message_string(input);
            }
        }
    }
}

void cc::ChatController::handle_receive() {
    while (!quitting) {
        auto received = _connectionService->receive_message_string();
        cout << received << endl;
    }
}

string cc::ChatController::get_input() {
    string input;
    getline(cin, input);
    input = trim(input);

    return input;
}

void cc::ChatController::do_command(COMMAND_TYPES command) {
    switch (command) {
        case COMMAND_TYPES::HELP:
            return show_help();
        case COMMAND_TYPES::QUIT:
            return do_quit();
        case COMMAND_TYPES::UNKNOWN: {
            cout << "Unknown command. Type /h for help." << endl;
            return;
        }
    }

}

void cc::ChatController::show_help() {
    cout << "\nCOMMANDS:" << endl;
    cout << "/h — show this help" << endl;
    cout << "/q or /0 — quit chat" << endl;
    cout << "SENDING PERSONAL MESSAGE:" << endl;
    cout << "@<username> <message>" << endl;
    cout << "example: @john hi!" << endl << endl;
}

void cc::ChatController::do_quit() {
    _connectionService->send_message_string("/q");
    quitting = true;
}

