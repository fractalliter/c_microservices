//
// Created by elias on 7/11/22.
//

#include "queue.h"
#include "global.h"

void *context;
void *zmq_responder;
const char *address;

int receive_message(int LEN, char *buffer, char *json) {
    int size = zmq_recv (zmq_responder, buffer, LEN, 0);
    if (size == -1){
        return 0;
    }
    int i = 0;
    while (i <= LEN+1) {
        if(buffer[i] == '}') {
            buffer[i+1] = '\0';
            LEN = i+1;
            break;
        }
        i+=1;
    }
    int j = 0;
    while (j<=LEN) {
        json[j] = buffer[j];
        j+=1;
    }
    return LEN;
}

void start_zmq() {
    context = zmq_ctx_new();
    zmq_responder = zmq_socket (context, ZMQ_REP);
    Config config = server_env_vars();
    address = get_address(config);
    int rc = zmq_bind(zmq_responder, address);
    assert(rc == 0);
    printf("server is listening on port 5555\n");
}