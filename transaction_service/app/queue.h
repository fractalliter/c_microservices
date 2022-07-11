//
// Created by elias on 7/11/22.
//

#ifndef TRANSACTION_SERVICE_QUEUE_H
#define TRANSACTION_SERVICE_QUEUE_H
#include "config.h"
#include <zmq.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int receive_message(int, char *, char *);
void start_zmq();

#endif //TRANSACTION_SERVICE_QUEUE_H
