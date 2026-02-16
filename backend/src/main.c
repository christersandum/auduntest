#include "mongoose.h"
#include "routes.h"
#include <signal.h>
#include <stdio.h>

static int s_signo = 0;

static void signal_handler(int signo) {
    s_signo = signo;
}

// Main event handler — dispatches to route handlers
static void event_handler(struct mg_connection *c, int ev, void *ev_data) {
    if (ev == MG_EV_HTTP_MSG) {
        struct mg_http_message *hm = (struct mg_http_message *) ev_data;

        // --- API Routes ---
        if (mg_match(hm->uri, mg_str("/api/health"), NULL)) {
            handle_health(c, hm);
        } else if (mg_match(hm->uri, mg_str("/api/items"), NULL)) {
            handle_items(c, hm);
        } else {
            // Fallback: 404
            mg_http_reply(c, 404, "Content-Type: application/json\r\n",
                          "{\"error\": \"Not found\"}\n");
        }
    }
}

int main(void) {
    struct mg_mgr mgr;
    const char *listen_addr = "http://0.0.0.0:8080";

    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    mg_mgr_init(&mgr);
    printf("Starting server on %s\n", listen_addr);

    if (mg_http_listen(&mgr, listen_addr, event_handler, NULL) == NULL) {
        fprintf(stderr, "Failed to bind to %s\n", listen_addr);
        return 1;
    }

    // Event loop
    while (s_signo == 0) {
        mg_mgr_poll(&mgr, 1000);
    }

    printf("Caught signal %d, shutting down...\n", s_signo);
    mg_mgr_free(&mgr);
    return 0;
}