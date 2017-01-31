#include <stdio.h>
#include "lexer.h"
#include "gram.h"
#include "gram.c"

int main(int argc, char **argv) {
    FILE *fp = fopen("tests.txt", "r");
    if (!fp) {
        fprintf(stderr, "Unable to open input file\n");
        exit(EXIT_FAILURE);
    }

    struct scanner_t scanner;
    if (!scanner_create(&scanner, fp)) {
        fprintf(stderr, "Failed to create scanner\n");
        exit(EXIT_FAILURE);
    }

    if (!scanner_lex(&scanner)) {
        printf("\nlexing failed!\n");
    } else {
        printf("\nsuccess!\n");
    }

    if (!scanner_destroy(&scanner)) {
        fputs("Failed to destroy scanner\n", stderr);
        exit(EXIT_FAILURE);
    }
    void *parser = schemeParserAlloc(malloc);
    Parse ast;

    schemeParser(parser, TK_INTEGER, 15, &ast);
    schemeParser(parser, TK_PLUS, 0, &ast);
    schemeParser(parser, TK_INTEGER, 14, &ast);
    schemeParser(parser, 0, 0, &ast);

#if 0
    schemeParser(parser, TK_INTEGER, 15);
    schemeParser(parser, TK_MINUS, 0);
    schemeParser(parser, TK_INTEGER, 14);
    schemeParser(parser, 0, 0);
#endif

    schemeParserFree(parser, free);

    return 0;
}
