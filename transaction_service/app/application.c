//
// Created by elias on 7/11/22.
//

#include "application.h"

static volatile int keepRunning = 1;

void shut_down_server() {
    keepRunning = 0;
    free((void *)address);
    zmq_close (zmq_responder);
    zmq_ctx_destroy (context);
    PQfinish(conn);
}

int start_server() {
    signal(SIGINT, shut_down_server);
    signal(SIGTERM, shut_down_server);
    start_zmq();
    getConnection();
    while(keepRunning) {
        transaction();
    }
    printf("%s", "server is shutting down\n");
    return 0;
}