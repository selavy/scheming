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

Ensure(Parser, parse_string) {
    const char *restrict const data = "\"Hello World\"";
    const size_t len = strlen(data);

    ParseTree ast;
    Token token = { .begin=data, .end=data+len };
    SchemeParser *parser = schemeParserAlloc(malloc);

    ast.kind = AST_UNKNOWN;
    g_parse_accepted = 0;

    schemeParser(parser, TK_STRING, &token, &ast);
    schemeParser(parser, 0, 0, &ast);

    schemeParserFree(parser, free);

    assert_that(g_parse_accepted, is_equal_to(1));
    assert_that(ast.kind, is_equal_to(AST_STRING));
    const char *expected = "Hello World";
    assert_that(ast.u.sval.begin, is_equal_to_contents_of(expected, strlen(expected)));
}

Ensure(Parser, parse_plus_expr) {
    const char *data[5] = {
        "(",
        "+",
        "1234",
        "4444",
        ")"
    };
    const size_t lens[5] = {
        strlen(data[0]),
        strlen(data[1]),
        strlen(data[2]),
        strlen(data[3]),
        strlen(data[4]),
    };
    const Token tokens[5] = {
        { .begin=&data[0][0], .end=&data[0][0]+lens[0] },
        { .begin=&data[1][0], .end=&data[1][0]+lens[1] },
        { .begin=&data[2][0], .end=&data[2][0]+lens[2] },
        { .begin=&data[3][0], .end=&data[3][0]+lens[3] },
        { .begin=&data[4][0], .end=&data[4][0]+lens[4] },
    };
    const int types[5] = {
        TK_LPAREN,
        TK_PLUS,
        TK_NUMBER,
        TK_NUMBER,
        TK_RPAREN,
    };

    ParseTree ast;
    SchemeParser *parser = schemeParserAlloc(malloc);

    ast.kind = AST_UNKNOWN;
    g_parse_accepted = 0;

    for (int i = 0; i < 5; ++i) {
        schemeParser(parser, types[i], &tokens[i], &ast);
    }
    schemeParser(parser, 0, 0, &ast);

    schemeParserFree(parser, free);

    assert_that(g_parse_accepted, is_equal_to(1));
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
    add_test_with_context(suite, Parser, parse_string);
    add_test_with_context(suite, Parser, parse_plus_expr);
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
