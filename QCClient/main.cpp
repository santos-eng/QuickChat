#include <QCNetwork/client/TCPClient.h>
#include <iostream>
#include <thread>

using namespace QC;
int main(int argc, char* argv[]) {
    TCPClient client{"localhost", 8080};

    client.onMessage = [](const std::string& message) {
        std::cout << message;
    };

    // Running input processes on seperate threads, otherwise block everything
    std::thread t{[&client]() {client.run();}};

    while (true) {
        std::string message;
        std::getline(std::cin, message);

        if (message == "\\q") break;
        message += "\n";

        client.post(message);
    }

    // Must kill the client loop and kill the thread 
    client.stop(); 
    t.join();
    return 0;
}