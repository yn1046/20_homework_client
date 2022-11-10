#pragma once

#include <string>
#include <utility>

using namespace std;

namespace cc {
    struct Message {
        string sender;
        string text;
        bool is_personal = false;
        pair <User, User> between;
    }
}