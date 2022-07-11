//
// Created by elias on 7/8/22.
//
#include <stdio.h>
#include <stdlib.h>
#include "config.h"

const char* get_address(Config config){
    char *address = (char *) malloc(50);
    sprintf(address, "tcp://%s:%d", config.host, config.port);
    return address;
}

Config server_env_vars(){
    Config config;
    const char *port = getenv("TRANSACTION_SERVICE_PORT");
    if(port != NULL) config.port = atoi(port);
    else config.port = 5555;
    const char *host = getenv("TRANSACTION_SERVICE_HOST");
    if (host != NULL) config.host = host;
    else config.host = "*";
    return config;
}