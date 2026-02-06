#include <QCNetwork/client/TCPClient.h>
#include <iostream>

using namespace QC;
int main(int argc, char* argv[]) {
    TCPClient client{"localhost", 8080};

    client.onMessage = [](const std::string& message) {
        std::cout << message;
    };

    client.run();

    return 0;
}