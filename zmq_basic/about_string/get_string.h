#include <zmq.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>

static char *
s_recv (void *socket) {
    zmq_msg_t message;
    zmq_msg_init(&message);
    zmq_msg_recv(&message, socket, 0);
    int size = zmq_msg_size(&message);
    char *ss = malloc(size + 1);
    memcpy(ss, zmq_msg_data(&message), size);
    zmq_msg_close(&message);
    ss[size] = 0;
    return ss;
}