//
// Created by elias on 7/8/22.
//
#ifndef C_MICROSERVICES_DATABASE_H
#define C_MICROSERVICES_DATABASE_H
#include <postgresql/libpq-fe.h>

typedef struct {
    int port;
    const char *host;
    const char *user;
    const char *password;
    const char *dbname;
} DBConfig;

DBConfig db_env_vars();

PGconn *getConnection();

void close_connection(PGconn *, int);

// If the retrieved data is not a tuble
void result_error_handler(PGconn *, PGresult *);

// If command not performed
void command_error_handler(PGconn *, PGresult *);

#endif //C_MICROSERVICES_DATABASE_H
