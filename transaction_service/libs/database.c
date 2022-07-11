//
// Created by elias on 7/8/22.
//

#include <stdlib.h>
#include "database.h"
#include <stdio.h>

typedef struct {
    int port;
    const char *host;
    const char *user;
    const char *password;
    const char *dbname;
} Config;

PGconn *getConnection() {
    Config config;
    config.port = 5432;
    config.host = "localhost";
    config.user = "postgres";
    config.password = "postgres";
    config.dbname = "test";
    const char *port = getenv("DB_PORT");
    if(port != NULL)
        config.port = atoi(port);
    const char *host = getenv("DB_HOST");
    if (host != NULL)
        config.host = host;
    const char *user = getenv("DB_USER");
    if (user != NULL)
        config.user = user;
    const char *password = getenv("DB_PASSWORD");
    if (password != NULL)
        config.password = password;
    const char *dbname = getenv("DB_NAME");
    if (dbname != NULL)
        config.dbname = dbname;
    char *conn_str = malloc(sizeof(char) * 200);
    sprintf(conn_str, "host=%s port=%d user=%s password=%s dbname=%s", config.host, config.port, config.user, config.password, config.dbname);
    PGconn *conn = PQconnectdb(conn_str);

    if (PQstatus(conn) == CONNECTION_BAD) {
        fprintf(stderr, "Connection to database failed: %s\n",
                PQerrorMessage(conn));
        close_connection(conn, 1);
    }
    free(conn_str);
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