#include <zmq.hpp>
#include <string>
#include <iostream>
#include <unistd.h>

int main(void) {

    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_REQ);
    socket.connect("tcp://localhost:5555");
    
    for (int i = 0; i != 10; ++i) {
        zmq::message_t request(5);
        socket.send(request);

        sleep(1);

        zmq::message_t reply;
        socket.recv(&reply);
        std::cout << "收到 World" << std::endl;
    }

    return 0;
}