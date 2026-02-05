#include <boost/asio.hpp>
#include <array>
#include <iostream>

using boost::asio::ip::tcp;

int main(int argc, char* argv[]) {
    try {
        boost::asio::io_context io_context;

        tcp::resolver resolver{io_context}; // Convert domain to IP addr

        // Endpoint is a combo of IP and port #, think of as hotel street # and room # in the hotel 
        auto endpoints = resolver.resolve("127.0.0.1", "8080");

        tcp::socket socket{io_context};
        boost::asio::connect(socket, endpoints);

        while (true) {
            //Listening
            std::array<char, 128> buf;

            boost::system::error_code error;

            size_t len = socket.read_some(boost::asio::buffer(buf), error); // Bytes successfull read;
            
            if (error == boost::asio::error::eof) {
                // connection cleanly cut
                break;
            } else if (error) {
                throw boost::system::system_error(error);
            }

            std::cout.write(buf.data(), len); // (mem address, length of msg)
        }
         
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}