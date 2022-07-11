//
// Created by elias on 7/11/22.
//

#ifndef TRANSACTION_SERVICE_GLOBAL_H
#define TRANSACTION_SERVICE_GLOBAL_H
#include <postgresql/libpq-fe.h>

extern const char *address;
extern void *context;
extern PGconn *conn;
extern void *zmq_responder;
#endif //TRANSACTION_SERVICE_GLOBAL_H
