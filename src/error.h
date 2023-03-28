#ifndef ERROR_H
#define ERROR_H

#include <stdint.h>
#include <stdio.h>

static bool GlobalHadError = false;

// Error handling
static void report(uint32_t line, const char *where, const char *msg) {
    printf("[line %d] Error %s: %s", line, where, msg);
    GlobalHadError = true;
};

inline void error(uint32_t line, const char *msg) {
    report(line, "", msg);
};

#endif
