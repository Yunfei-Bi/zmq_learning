#include "zhelpers.h"

int main(void ) {
    int major, minor, patch;
    zmq_version(&major, &minor, &patch);
    printf("当前 ZeroMQ 版本: %d.%d.%d\n", major, minor, patch);
    return 
}