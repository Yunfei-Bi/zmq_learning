#include <zmq.h>

int main(void) {
    void *context = zmq_init(1);
    void *mousetrap;

    mousetrap = zmq_socket(context, ZMQ_PULL);

    int64_t jawsize = 10000;

    /**
     * ZMQ_HWM = 高水位标记，控制消息队列的最大长度
     * 对于 ZMQ_PULL 套接字，当缓存的消息超过 10000 条时，
     * 上游的 ZMQ_PUSH 套接字会被阻塞，直到有空间为止。
     */
    zmq_setsockopt(mousetrap, ZMQ_HWM, &jawsize, sizeof jawsize);

    zmq_connect(mousetrap, "tcp://192.168.55.221:5501");

    zmq_msg_t mouse;
    zmq_msg_init(&mouse);
    zmq_msg_recv(&mouse, mousetrap, 0);

    zmq_msg_close(&mouse);

    zmq_close(mousetrap);
    return 0;
}
