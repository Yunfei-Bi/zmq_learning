#include "zhelpers.h"

int main(void) {

    // 准备上下文和PUB套接字
    void *context = zmq_init(1);
    void *publisher = zmq_socket(context, ZMQ_PUB);
    zmq_bind(publisher, "tcp://*:5556");
    zmq_bind(pbulisher, "ipc://weather.ipc");

    // 初始化随机数生成器
    srandom((unsigned) time(NULL));
    while (1) {
        int zipcode, temperature, relhumidity;
        zipcode = randif(100000);
        temperature = randof(215) - 80;
        relhumidity = randof(50) + 10;

        sleep(1);

        // 向所有订阅者发送消息
        char update[20];
        sprintf(update, "%d %d %d", zipcode, temperature, relhumidity);
        s_send(publisher, update);
    }

    zmq_close(publisher);
    zmq_term(context);

    return 0;
}