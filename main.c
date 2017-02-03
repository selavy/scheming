#include <stdio.h>
//#include "lexer.h"
#include "gram.h"
#include "gram.c"
#include <cgreen/cgreen.h>

Describe(Parser);
BeforeEach(Parser) {}
AfterEach(Parser) {}

Ensure(Parser, boolean_is_constant) {
    ParseTree ast;
    Token token;
    SchemeParser *parser = schemeParserAlloc(malloc);

    ast.type = AST_UNKNOWN;
    g_parse_accepted = 0;
    token.value = 0;

    schemeParser(parser, TK_BOOLEAN, &token, &ast);
    schemeParser(parser, 0, 0, &ast);

    schemeParserFree(parser, free);
    assert_that(g_parse_accepted == 1);
    assert_that(ast.type == AST_BOOLEAN);
}

Ensure(Parser, number_is_constant) {
    ParseTree ast;
    Token token;
    SchemeParser *parser = schemeParserAlloc(malloc);

    ast.type = AST_UNKNOWN;
    g_parse_accepted = 0;
    token.value = 0;

    schemeParser(parser, TK_NUMBER, &token, &ast);
    schemeParser(parser, 0, 0, &ast);

    schemeParserFree(parser, free);
    assert_that(g_parse_accepted == 1);
    assert_that(ast.type == AST_NUMBER);
}

int main(int argc, char **argv) {
    TestSuite *suite = create_test_suite();
    add_test_with_context(suite, Parser, boolean_is_constant);
    return run_test_suite(suite, create_text_reporter());
}

//int main(int argc, char **argv) {
////    FILE *fp = fopen("tests.txt", "r");
////    if (!fp) {
////        fprintf(stderr, "Unable to open input file\n");
////        exit(EXIT_FAILURE);
////    }
////
////    struct scanner_t scanner;
////    if (!scanner_create(&scanner, fp)) {
////        fprintf(stderr, "Failed to create scanner\n");
////        exit(EXIT_FAILURE);
////    }
////
////    if (!scanner_lex(&scanner)) {
////        printf("\nlexing failed!\n");
////    } else {
////        printf("\nsuccess!\n");
////    }
////
////    if (!scanner_destroy(&scanner)) {
////        fputs("Failed to destroy scanner\n", stderr);
////        exit(EXIT_FAILURE);
////    }
//
//    printf("Running unit tests...\n");
//    test_constant_boolean();
//    test_constant_number();
//    printf("Success!\n");
//
//#if 0
//    void *parser = schemeParserAlloc(malloc);
//    struct ParseTree ast;
//    struct Token token;
//    token.value = 15;
//    schemeParser(parser, TK_INTEGER, &token, &ast);
//    schemeParser(parser, TK_PLUS, &token, &ast);
//    schemeParser(parser, TK_INTEGER, &token, &ast);
//    schemeParser(parser, 0, 0, &ast);
//    schemeParserFree(parser, free);
//#endif
//
//    return 0;
//}
