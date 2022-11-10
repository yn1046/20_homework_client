#include <iostream>
#include <fstream>
#include <iomanip>
#include "Controllers/ChatController.h"
#include "Services/ConnectionService.h"

using namespace std;
using namespace cc;

int main() {
    new ChatController(new ConnectionService);

    return 0;
}
