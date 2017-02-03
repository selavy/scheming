#include <stdio.h>
//#include "lexer.h"
#include "gram.h"
#include "gram.c"
#include <cgreen/cgreen.h>

Describe(Parser);
BeforeEach(Parser) {}
AfterEach(Parser) {}

Ensure(Parser, parse_boolean_true_lowercase) {
    const char *restrict const data = "#t";
    const size_t len = strlen(data);

    ParseTree ast;
    Token token = { .begin=data, .end=data+len };
    SchemeParser *parser = schemeParserAlloc(malloc);

    ast.kind = AST_UNKNOWN;
    g_parse_accepted = 0;

    schemeParser(parser, TK_BOOLEAN, &token, &ast);
    schemeParser(parser, 0, 0, &ast);

    schemeParserFree(parser, free);

    assert_that(g_parse_accepted, is_equal_to(1));
    assert_that(ast.kind, is_equal_to(AST_BOOLEAN));
    assert_that_double(ast.u.nval, is_equal_to_double(1.0));
}

Ensure(Parser, parse_boolean_true_uppercase) {
    const char *restrict const data = "#T";
    const size_t len = strlen(data);

    ParseTree ast;
    Token token = { .begin=data, .end=data+len };
    SchemeParser *parser = schemeParserAlloc(malloc);

    ast.kind = AST_UNKNOWN;
    g_parse_accepted = 0;

    schemeParser(parser, TK_BOOLEAN, &token, &ast);
    schemeParser(parser, 0, 0, &ast);

    schemeParserFree(parser, free);

    assert_that(g_parse_accepted, is_equal_to(1));
    assert_that(ast.kind, is_equal_to(AST_BOOLEAN));
    assert_that_double(ast.u.nval, is_equal_to_double(1.0));
}

Ensure(Parser, parse_boolean_false_lowercase) {
    const char *restrict const data = "#f";
    const size_t len = strlen(data);

    ParseTree ast;
    Token token = { .begin=data, .end=data+len };
    SchemeParser *parser = schemeParserAlloc(malloc);

    ast.kind = AST_UNKNOWN;
    g_parse_accepted = 0;

    schemeParser(parser, TK_BOOLEAN, &token, &ast);
    schemeParser(parser, 0, 0, &ast);

    schemeParserFree(parser, free);

    assert_that(g_parse_accepted, is_equal_to(1));
    assert_that(ast.kind, is_equal_to(AST_BOOLEAN));
    assert_that_double(ast.u.nval, is_equal_to_double(0.0));
}

Ensure(Parser, parse_boolean_false_uppercase) {
    const char *restrict const data = "#F";
    const size_t len = strlen(data);

    ParseTree ast;
    Token token = { .begin=data, .end=data+len };
    SchemeParser *parser = schemeParserAlloc(malloc);

    ast.kind = AST_UNKNOWN;
    g_parse_accepted = 0;

    schemeParser(parser, TK_BOOLEAN, &token, &ast);
    schemeParser(parser, 0, 0, &ast);

    schemeParserFree(parser, free);

    assert_that(g_parse_accepted, is_equal_to(1));
    assert_that(ast.kind, is_equal_to(AST_BOOLEAN));
    assert_that_double(ast.u.nval, is_equal_to_double(0.0));
}

Ensure(Parser, parse_number) {
    const char *restrict const data = "1234";
    const size_t len = strlen(data);

    ParseTree ast;
    Token token = { .begin=data, .end=data+len };
    SchemeParser *parser = schemeParserAlloc(malloc);

    ast.kind = AST_UNKNOWN;
    g_parse_accepted = 0;

    schemeParser(parser, TK_NUMBER, &token, &ast);
    schemeParser(parser, 0, 0, &ast);

    schemeParserFree(parser, free);

    assert_that(g_parse_accepted, is_equal_to(1));
    assert_that(ast.kind, is_equal_to(AST_NUMBER));
    assert_that_double(ast.u.nval, is_equal_to_double(1234.0));
}

Ensure(Parser, parse_fraction) {
    const char *restrict const data = "0.1111";
    const size_t len = strlen(data);

    ParseTree ast;
    Token token = { .begin=data, .end=data+len };
    SchemeParser *parser = schemeParserAlloc(malloc);

    ast.kind = AST_UNKNOWN;
    g_parse_accepted = 0;

    schemeParser(parser, TK_NUMBER, &token, &ast);
    schemeParser(parser, 0, 0, &ast);

    schemeParserFree(parser, free);

    assert_that(g_parse_accepted, is_equal_to(1));
    assert_that(ast.kind, is_equal_to(AST_NUMBER));
    assert_that_double(ast.u.nval, is_equal_to_double(0.1111));
}

Ensure(Parser, parse_character) {
    const char *restrict const data = "#\\A";
    const size_t len = strlen(data);

    ParseTree ast;
    Token token = { .begin=data, .end=data+len };
    SchemeParser *parser = schemeParserAlloc(malloc);

    ast.kind = AST_UNKNOWN;
    g_parse_accepted = 0;

    schemeParser(parser, TK_CHARACTER, &token, &ast);
    schemeParser(parser, 0, 0, &ast);

    schemeParserFree(parser, free);

    assert_that(g_parse_accepted, is_equal_to(1));
    assert_that(ast.kind, is_equal_to(AST_CHARACTER));
    assert_that(ast.u.s.info, is_equal_to('A'));
}

int main(int argc, char **argv) {
    TestSuite *suite = create_test_suite();
    add_test_with_context(suite, Parser, parse_boolean_true_lowercase);
    add_test_with_context(suite, Parser, parse_boolean_true_uppercase);
    add_test_with_context(suite, Parser, parse_boolean_false_lowercase);
    add_test_with_context(suite, Parser, parse_boolean_false_uppercase);
    add_test_with_context(suite, Parser, parse_number);
    add_test_with_context(suite, Parser, parse_fraction);
    add_test_with_context(suite, Parser, parse_character);
    return run_test_suite(suite, create_text_reporter());
}

//int main(int argc, char **argv) {
//    FILE *fp = fopen("tests.txt", "r");
//    if (!fp) {
//        fprintf(stderr, "Unable to open input file\n");
//        exit(EXIT_FAILURE);
//    }
//
//    struct scanner_t scanner;
//    if (!scanner_create(&scanner, fp)) {
//        fprintf(stderr, "Failed to create scanner\n");
//        exit(EXIT_FAILURE);
//    }
//
//    if (!scanner_lex(&scanner)) {
//        printf("\nlexing failed!\n");
//    } else {
//        printf("\nsuccess!\n");
//    }
//
//    if (!scanner_destroy(&scanner)) {
//        fputs("Failed to destroy scanner\n", stderr);
//        exit(EXIT_FAILURE);
//    }
//
//    return 0;
//}
