#include <zmq.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    void *context = zmq_init(1);

    printf ("正在收集气象信息...\n");
    void *subscriber = zmq_socket(context, ZMQ_SUB);
    zmq_connect(subscriber, "tcp://localhost:5556");

    char *filter = (argc > 1) ? argv[1] : "10001";
    zmq_setsockopt(subscriber, ZMQ_SUBSCRIBE, filter, strlen(filter));

    int update_nbr;
    long total_temp = 0;
    for (update_nbr = 0; update_nbr < 100; ++update_nbr) {
        char *ss = s_recv(subscriber);
        int zipcode, temperature, relhumidity;
        sscanf(ss, "%d %d %d", &zipcode, &temperature, &relhumidity);
        total_temp += temperature;
        free(ss);;
    }
    printf ("地区邮编 '%s' 的平均温度为 %dF\n",
        filter, (int) (total_temp / update_nbr));
    
    zmq_close(subscriber);
    zmq_term(context);

    return 0;
}