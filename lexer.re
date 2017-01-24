#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

/*!max:re2c*/
#define SIZE (64 * 1024)

struct scanner_t {
    uint8_t buffer[SIZE + YYMAXFILL];
    uint8_t *limit;
    uint8_t *cur;
    uint8_t *marker;
    uint8_t *token;
    FILE *fp;
    bool eof;
};

bool scanner_create(struct scanner_t *scanner, FILE *fp) {
    assert(scanner);
    assert(fp);

    scanner->fp = fp;
    memset(&scanner->buffer[0], 0, sizeof(scanner->buffer));
    scanner->limit = &scanner->buffer[SIZE];
    scanner->cur = scanner->limit;
    scanner->marker = scanner->limit;
    scanner->token = scanner->limit;
    scanner->eof = false;

    return true;
}

bool scanner_destroy(struct scanner_t *scanner) {
    return true;
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

/*!re2c re2c:define:YYCTYPE = "unsigned char"; */

static bool lex_integer(const uint8_t *const begin, const uint8_t *const end, int *val) {
    char c;
    int result = 0;
    for (const uint8_t *cur = begin; cur < end; ++cur) {
        c = *cur;
        result *= 10;
        if (c < '0' || c > '9') {
            return false;
        }
        result += *cur - '0';
    }
    *val = result;
    return true;
}

static bool scanner_lex(struct scanner_t *scanner) {
    for (;;) {
        scanner->token = scanner->cur;
        /*!re2c
            re2c:define:YYCURSOR = scanner->cur;
            re2c:define:YYMARKER = scanner->marker;
            re2c:define:YYLIMIT = scanner->limit;
            re2c:yyfill:enable = 1;
            re2c:define:YYFILL = "if (!scanner_fill(scanner, @@)) return false;";
            re2c:define:YYFILL:naked = 1;

			end = "\x00";

            *   { return false; }
            end { return scanner->limit - scanner->token == YYMAXFILL; }

            integer = [0-9][0-9]+;
            integer {
                int result;
                if (!lex_integer(scanner->token, scanner->cur, &result)) {
                    return false;
                }
                printf("Parsed integer: %d\n", result);
                //return true;
                continue;
            }

            // whitespaces
            mcm = "#|" ([^#] | ("|" [^#]))* "|""#";
            scm = ";" [^\n]* "\n";
            wsp = ([ \t\v\n\r] | scm | mcm)+;
            wsp { continue; }

        */
    }
}
