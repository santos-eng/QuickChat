#include <boost/asio.hpp>
#include <iostream>

using boost::asio::ip::tcp;

int main() {
    try {
        boost::asio::io_context io_context;

        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 8080));// Listen on all devices on local networrk;
        
        while (true) {
            std::cout << "Accepting on port 8080\n";
            tcp::socket socket(io_context); // closes when out of scop
            acceptor.accept(socket); // blocking until connection

            std::string test_msg = "hello client, testing\n";
            boost::system::error_code error;

            // blocking, ensure buffer written to witht he error message
            boost::asio::write(socket, boost::asio::buffer(test_msg), error); // buffer is a wrapper of the testmsg, because network doesnt understand std;:string
        } 
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}