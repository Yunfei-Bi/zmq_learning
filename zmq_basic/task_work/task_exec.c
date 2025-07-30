/**
 * 任务执行器
 * 连接PULL套接字至tcp://localhost:5557端点
 * 从任务分发器处获取任务
 * 连接PUSH套接字至tcp://localhost:5558端点
 * 向结果采集器发送结果
 */

/**
 * worker上游和任务分发器相连，下游和结果收集器相连，
 * 这就意味着你可以开启任意多个worker。
 * 
 * 但若worker是绑定至端点的，而非连接至端点，
 * 那我们就需要准备更多的端点，并配置任务分发器和结果收集器。
 * 
 * 所以说，任务分发器和结果收集器是这个网络结构中较为稳定的部分，
 * 因此应该由它们绑定至端点，而非worker，因为它们较为动态。
 */

 #include "zhelpers.h"

 int main(void) {
    void *context = zmq_init(1);

    // 用于接收任务的套接字
    void *receiver = zmq_socket(context, ZMQ_PULL);
    zmq_connect(receiver, "tcp://localhost:5557");

    // 用于发送结果的套接字
    void *sender = zmq_socket(context, ZMQ_PUSH);
    zmq_connect(sender, "tcp://localhost:5558");

    while (1) {
        char *ss = s_recv(receiver);

        // 输出处理进度
        fflush(stdout);
        printf("%s.", ss);

        // 开始处理
        s_sleep(atoi(ss));
        free(ss);

        // 发送结果
        s_send(sender, "");
    }
    zmq_close(receiver);
    zmq_close(sender);
    zmq_term(context);

    return 0;
 }