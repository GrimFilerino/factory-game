
#ifndef LOGGER_H
#define LOGGER_H

#define PATH "./logs"
typedef enum log_statuses {
        INFO,
        WARNING,
        ERROR,
} log_statuses_t;

typedef struct log {
        char* type;
        char* message;
        char* timestamp;
} log_t;


void create_log(log_statuses_t type, char* message);

#endif

