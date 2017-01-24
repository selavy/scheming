#include <stdio.h>
#include "lexer.c"

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
        printf("lexing failed!\n");
    } else {
        printf("success!\n");
    }

    if (!scanner_destroy(&scanner)) {
        fputs("Failed to destroy scanner\n", stderr);
        exit(EXIT_FAILURE);
    }
    return 0;
}
