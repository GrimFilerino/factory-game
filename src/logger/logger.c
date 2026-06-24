#include "./logger.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static char* join_path(const char* path1, const char* path2) {
    char* result = malloc(strlen(path1) + strlen(path2) + 2);
    strcpy(result, path1);
    strcat(result, "/");
    strcat(result, path2);
    return result;
}

void create_log(enum Logtype type, char *message) {
        char* errorType = "";
        switch (type) {
                case INFO: { 
                        errorType = "[info]";
                        break; 
                }
                case WARNING: {
                        errorType = "[warning]";
                        break;
                }
                case ERROR: {
                        errorType = "[error]";
                        break;
                }
        };

        FILE* file = fopen(join_path(PATH, "loggs.txt"), "a");

        if(file == NULL) {
                return;
        }

        time_t now = time(NULL);
        struct tm *t = localtime(&now); 
        char buffer[100];

        strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", t);

        fprintf(file, "%s %s %s", errorType, buffer, message);

        fclose(file);
}
