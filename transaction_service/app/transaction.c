//
// Created by elias on 7/11/22.
//

#include "transaction.h"
#include <zmq.h>

enum direction {in,out};

void transaction() {
    json_value* value;
    int LEN = 1028;
    char *buffer = (char *) malloc(LEN);
    char *json = (char *) malloc(LEN);
    LEN = receive_message(LEN, buffer, json);
    value = json_parse((json_char*)json, LEN);
    if (value == NULL) {
        json_value_free(value);
        free(buffer);
        free(json);
        const char *error = "{\"error\":\"Unable to parse data\"}";
        zmq_send (zmq_responder, error, strlen(error), 0);
    }else {
        int param_len = 3;
        const char *param_values[param_len];
        const char *keys[] = {"user", "amount", "direction"};
        for (int i = 0; i < param_len; ++i) {
            if (strncasecmp(value->u.object.values[i].name, keys[i], strlen(keys[i])) == 0) {
                param_values[i] = value->u.object.values[i].value->u.string.ptr;
                if(i==2 && strncasecmp(value->u.object.values[i].value->u.string.ptr, "in", strlen("in")) == 0) {
                    param_values[i] = "1";
                }else if(i==2 && strncasecmp(value->u.object.values[i].value->u.string.ptr, "out", strlen("out")) == 0)
                    param_values[i]= "0";
            }
        }
        transactional(param_values);

        json_value_free(value);
        free(buffer);
        free(json);
    }
}

void transactional(const char *const *param_values) {
    int rollback = 0;
    // Begin the transaction
    PGresult *response = PQexec(conn, "BEGIN");
    command_error_handler(conn, response);
    PQclear(response);

    // Check if user exists
    char *stm = "SELECT * FROM account WHERE user_id=$1";
    response = PQexecParams(conn, stm, 1, NULL, param_values, NULL, NULL, 0);
    result_error_handler(conn, response);
    char *ptr;
    long amount = strtol(PQgetvalue(response, 0, 2), &ptr, 10);
    if (amount - strtol(param_values[1], &ptr, 10) < 0) {
        PQclear(response);
        PQexec(conn, "ROLLBACK");
        rollback = 1;
        zmq_send(zmq_responder, "{\"error\":\"Not enough money\"}", 1028, 0);

    }
    if (rollback == 0) {
        char *udt[] = {"UPDATE account SET balance=balance-$2 WHERE user_id=$1",
                       "UPDATE account SET balance=balance+$2 WHERE user_id=$1"};
        if(strncasecmp(param_values[2], "0", 1)==0)
            response = PQexecParams(conn, udt[0], 2, NULL, param_values, NULL, NULL, 0);
        if(strncasecmp(param_values[2], "1", 1)==0)
            response = PQexecParams(conn, udt[1], 2, NULL, param_values, NULL, NULL, 0);
        command_error_handler(conn, response);
        PQclear(response);

        // Commit the transaction
        response = PQexec(conn, "COMMIT");
        command_error_handler(conn, response);
        PQclear(response);

        // retrieve updated user
        response = PQexecParams(conn, stm, 1, NULL, param_values, NULL, NULL, 0);
        result_error_handler(conn, response);
        char resp[50];
        sprintf(resp, "{\"id\":%s,\"name\": \"%s\",\"amount\":%s}", PQgetvalue(response, 0, 0),
                PQgetvalue(response, 0, 1), PQgetvalue(response, 0, 2));

        zmq_send(zmq_responder, resp, strlen(resp), 0);
    }

    PQclear(response);
}