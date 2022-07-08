//
// Created by elias on 7/8/22.
//
#include <postgresql/libpq-fe.h>
#ifndef C_MICROSERVICES_DATABASE_H
#define C_MICROSERVICES_DATABASE_H

PGconn *getConnection();

void close_connection(PGconn *, int);

// If the retrieved data is not a tuble
void result_error_handler(PGconn *, PGresult *);

// If command not performed
void command_error_handler(PGconn *, PGresult *);

#endif //C_MICROSERVICES_DATABASE_H
