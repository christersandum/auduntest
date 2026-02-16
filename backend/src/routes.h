#ifndef ROUTES_H
#define ROUTES_H

#include "mongoose.h"

void handle_health(struct mg_connection *c, struct mg_http_message *hm);
void handle_items(struct mg_connection *c, struct mg_http_message *hm);

#endif
