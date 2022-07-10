//
// Created by elias on 7/8/22.
//

#include <stdio.h>
#include <stdlib.h>
#include <zmq.h>
#include <json-parser/json.h>
#include <string.h>
#include "libs/database.h"
#include <assert.h>
#include <ctype.h>
#include "libs/config.h"

int main(int argc, char** argv)
{
    json_value* value;
    Config config = parse_args(argc, argv);
    const char *port = getenv("TRANSACTION_SERVICE_PORT");
    if(port != NULL)
        config.port = atoi(port);
    const char *host = getenv("TRANSACTION_SERVICE_HOST");
    if (host != NULL)
        config.host = host;
    PGconn *conn = getConnection();
    const char *address = get_address(config);

    //  Socket to talk to clients
    void *context = zmq_ctx_new();
    void *responder = zmq_socket (context, ZMQ_REP);
    int rc = zmq_bind(responder, address);
    assert(rc == 0);
    printf("server is listening on port 5555\n");

    while(1) {
        int LEN = 50;
        char buffer[LEN];
        zmq_recv (responder, buffer, LEN, 0);
        int i = 0;
        while (i <= LEN+1) {
            if(buffer[i] == '}') {
                buffer[i+1] = '\0';
                LEN = i+1;
                break;
            }
            i+=1;
        }
        char json[LEN];
        int j = 0;
        while (j<=LEN) {
            json[j] = buffer[j];
            j+=1;
        }
        value = json_parse((json_char*)json, LEN);
        if (value == NULL) {
            const char *error = "{\"error\":\"Unable to parse data\"}";
            zmq_send (responder, error, strlen(error), 0);
            continue;
        }
        const char *param_values[2];
        const char *keys[] = {"user","amount"};
        for (int i = 0; i < 2; ++i) {
            if(strncasecmp(value->u.object.values[i].name, keys[i], strlen(keys[i])) == 0) {
                param_values[i] = value->u.object.values[i].value->u.string.ptr;
            }
        }

        // Begin the transaction
        PGresult *response = PQexec(conn, "BEGIN");
        command_error_handler(conn, response);
        PQclear(response);

        // Check if user exists
        char *stm = "SELECT * FROM account WHERE user_id=$1";
        response = PQexecParams(conn, stm, 1, NULL, param_values, NULL, NULL, 0);
        result_error_handler(conn, response);
        int amount = atoi(PQgetvalue(response, 0, 2));
        if (amount - atoi(param_values[1]) < 0) {
            PQclear(response);
            PQexec(conn, "ROLLBACK");
            zmq_send (responder, "{\"error\":\"Not enough money\"}", 1028, 0);
            continue;
        }
        // Update user balance and subtract the withdraw amount
        char *udt = "UPDATE account SET balance = balance - $2 WHERE user_id=$1";
        response = PQexecParams(conn, udt, 2, NULL, param_values, NULL, NULL, 0);
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
        sprintf(resp,"{\"id\":%s,\"name\": \"%s\",\"amount\":%s}", PQgetvalue(response, 0, 0),
                PQgetvalue(response, 0, 1), PQgetvalue(response, 0, 2));

        zmq_send (responder, resp, strlen(resp), 0);
        PQclear(response);
        json_value_free(value);
    }
    free((void *)address);
    zmq_close (responder);
    zmq_ctx_destroy (context);
    PQfinish(conn);
    return 0;
}
