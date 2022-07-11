//
// Created by elias on 7/11/22.
//

#ifndef TRANSACTION_SERVICE_TRANSACTION_H
#define TRANSACTION_SERVICE_TRANSACTION_H
#include "database.h"
#include <json-parser/json.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"

int receive_message(int LEN, char *buffer, char *json);

void transactional(const char *const *param_values);

void transaction();

#endif //TRANSACTION_SERVICE_TRANSACTION_H
