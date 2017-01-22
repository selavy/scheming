#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

/*!max:re2c*/
static const size_t SIZE = 64 * 1024;

struct scanner_t {
    uint8_t buffer[SIZE + YYMAXFILL];
    uint8_t *limit;
    uint8_t *cur;
    uint8_t *marker;
    uint8_t *token;
    FILE *fp;
    bool eof;
};

int scanner_create(struct scanner_t *scanner, FILE *fp) {
    assert(scanner);
    assert(fp);

    scanner->fp = fp;
    memset(&scanner->buffer[0], 0, sizeof(scanner->buffer));
    scanner->limit = &buffer[SIZE];
    scanner->cur = scanner->limit;
    scanner->marker = scanner->limit;
    scanner->token = scanner->limit;
    scanner->eof = false;

    return 0;
}

int scanner_destroy(struct scanner_t *scanner) {
    return 0;
}

bool scanner_fill(struct scanner_t *scanner, size_t need) {
    assert(scanner);
    if (scanner->eof) {
        return false;
    }

    assert(scanner->token >= &scanner->buffer[0]);
    const size_t free = scanner->token - &scanner->buffer[0];
    if (free < need) {
        return false;
    }
    memmove(&scanner->buffer[0],
            scanner->token,
            scanner->limit - scanner->token
           );
    scanner->limit -= free;
    scanner->cur -= free;
    scanner->marker -= free;
    scanner->token -= free;
    scanner->limit += fread(scanner->limit, 1, free, scanner->fp);
    if (scanner->limit < &scanner->buffer[SIZE]) {
        scanner->eof = true;
        memset(scanner->limit, 0, YYMAXFILL);
        scanner->limit += YYMAXFILL;
    }
    return true;
}
