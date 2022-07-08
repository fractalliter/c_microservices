//
// Created by elias on 7/8/22.
//
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "config.h"

Config parse_args(int argc, char *argv[]) {
    int i = 1;
    Config config;
    config.port = 5555;
    config.host = "*";

    while(i < argc) {
        if(!strncasecmp(argv[i], "-h", 2)) {
            config.host = argv[++i];
        }
        else if(!strncasecmp(argv[i], "-p", 2)) {
            config.port = atoi(argv[++i]);
        }
        else {
            fprintf(stderr, "Unknown argument: %s\n", argv[i]);
        }
        i++;
    }

    return config;
}

const char* get_address(Config config){
    char *address = (char *) malloc(50);
    sprintf(address, "tcp://%s:%d", config.host, config.port);
    return address;
}