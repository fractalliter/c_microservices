//
// Created by elias on 7/11/22.
//

#include "queue.h"
#include "global.h"

void *context;
void *zmq_responder;
const char *address;

void start_zmq() {
    context = zmq_ctx_new();
    zmq_responder = zmq_socket (context, ZMQ_REP);
    Config config = server_env_vars();
    address = get_address(config);
    int rc = zmq_bind(zmq_responder, address);
    assert(rc == 0);
    printf("server is listening on port 5555\n");
}