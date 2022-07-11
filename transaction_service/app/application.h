//
// Created by elias on 7/11/22.
//

#ifndef TRANSACTION_SERVICE_APPLICATION_H
#define TRANSACTION_SERVICE_APPLICATION_H
#include <stdio.h>
#include <stdlib.h>
#include <zmq.h>
#include "database.h"
#include <signal.h>
#include "transaction.h"
#include "global.h"
#include "queue.h"

void shut_down_server();
int start_server();
#endif //TRANSACTION_SERVICE_APPLICATION_H
