//
// Created by elias on 7/8/22.
//

#include <stdlib.h>
#include "database.h"
PGconn *getConnection() {
    PGconn *conn = PQconnectdb("user=postgres password=postgres dbname=test host=localhost port=5432");

    if (PQstatus(conn) == CONNECTION_BAD) {
        fprintf(stderr, "Connection to database failed: %s\n",
                PQerrorMessage(conn));
        close_connection(conn, 1);
    }
    return conn;
}

void close_connection(PGconn *connection, int code) {
    PQfinish(connection);
    exit(code);
}

void result_error_handler(PGconn *conn, PGresult *res) {
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        fprintf(stderr, "%s\n", PQresultErrorMessage(res));
        PQclear(res);
        close_connection(conn, 1);
    } else if (PQntuples(res) == 0) {
        printf("There's no such a user\n");
        PQclear(res);
        close_connection(conn, 0);
    }
}

void command_error_handler(PGconn *conn, PGresult *res) {
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        fprintf(stderr, "%s\n", PQresultErrorMessage(res));
        PQclear(res);
        close_connection(conn, 1);
    }
}