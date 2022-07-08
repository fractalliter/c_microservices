//
// Created by elias on 7/8/22.
//

#ifndef C_MICROSERVICES_CONFIG_H
#define C_MICROSERVICES_CONFIG_H
typedef struct {
    int port;
    const char *host;
} Config;

Config parse_args(int, char **);

const char* get_address(Config);

#endif //C_MICROSERVICES_CONFIG_H
