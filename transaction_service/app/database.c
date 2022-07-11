//
// Created by elias on 7/8/22.
//

#include <stdlib.h>
#include "database.h"
#include <stdio.h>
#include "global.h"

PGconn *conn;
PGconn *getConnection() {
    DBConfig config = db_env_vars();
    char *conn_str = malloc(sizeof(char) * 200);
    sprintf(conn_str, "host=%s port=%d user=%s password=%s dbname=%s", config.host, config.port, config.user, config.password, config.dbname);
    conn = PQconnectdb(conn_str);

    if (PQstatus(conn) == CONNECTION_BAD) {
        fprintf(stderr, "Connection to database failed: %s\n",
                PQerrorMessage(conn));
        close_connection(conn, 1);
    }
    free(conn_str);
    return conn;
}

DBConfig db_env_vars() {
    DBConfig config;
    const char *port = getenv("DB_PORT");
    if(port != NULL) config.port = atoi(port);
    else config.port = 5432;
    const char *host = getenv("DB_HOST");
    if (host != NULL) config.host = host;
    else config.host = "localhost";
    const char *user = getenv("DB_USER");
    if (user != NULL) config.user = user;
    else config.user = "postgres";
    const char *password = getenv("DB_PASSWORD");
    if (password != NULL) config.password = password;
    else config.password = "postgres";
    const char *dbname = getenv("DB_NAME");
    if (dbname != NULL) config.dbname = dbname;
    else config.dbname = "test";
    return config;
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