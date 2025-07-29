#include <zmq.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main (void) {
    
    /**
     * zmq_init(1) - 初始化ZeroMQ库，参数 1 表示使用1个I/O线程
     * void *context - 声明一个指针变量来存储上下文对象的地址
     * context - 这个上下文对象管理所有的套接字和连接
     */
    void *context = zmq_init(1);

    // 与客户端通信的套接字
    void *responder = zmq_socket(context, ZMQ_REP);
    zmq_bind(responder, "tcp://*:5555");

    while (1) {
        // 等待客户端请求
        zmq_msg_t request; //  声明了一个ZeroMQ消息对象。
        zmq_msg_init(&request); // 初始化消息对象
        zmq_msg_recv(&request, responder, 0); // 从客户端接收消息
        printf("收到 Hello\n"); // 从客户端接收消息
        zmq_msg_close(&request); // 释放消息对象资源

        sleep(1);

        // 返回应答
        zmq_msg_t reply; // 声明回复消息对象
        zmq_msg_init_size(&reply, 5); // 初始化消息，分配5字节空间
        memcpy(zmq_msg_data(&reply), "World", 5); // 将"World"复制到消息数据中
        zmq_msg_send(&reply, responder, 0); // 发送回复消息给客户端
        zmq_msg_close(&reply); // 释放回复消息资源
    }

    zmq_close(responder);
    zmq_term(context);

    return 0;
}