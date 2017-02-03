%include {

#include <stdint.h>
#include <assert.h>

typedef void SchemeParser;

enum NodeType {
    AST_BOOLEAN,
    AST_NUMBER,
    AST_UNKNOWN
};

struct ParseTree {
    enum NodeType type;
    int dummy; // TODO(plesslie): remove
};
typedef struct ParseTree ParseTree;

int g_parse_accepted = 0;

struct Token {
    int value;
};
typedef struct Token Token;

} // ~include

%parse_accept {
    //printf("parsing succeeded!\n");
    g_parse_accepted = 1;
}

%parse_failure {
    //printf("parsing failed!\n");
    g_parse_accepted = 0;
    assert(0);
}

%stack_overflow {
    //printf("stack overflow\n");
    g_parse_accepted = 0;
    assert(0);
}

%syntax_error {
    //printf("syntax error\n");
    g_parse_accepted = 0;
    assert(0);
}

%token_prefix TK_

%name schemeParser

%extra_argument {struct ParseTree* parse}
// TODO(plesslie): just to silence a warning about unused variable
%token_destructor { parse->dummy = 1; }

//%token_type {int}
%token_type {struct Token*}
// %type expr {Expr*}

constant ::= BOOLEAN. { parse->type = AST_BOOLEAN; }
constant ::= NUMBER. { parse->type = AST_NUMBER; }
