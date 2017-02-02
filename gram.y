%include {
#include <stdint.h>
#include <assert.h>

struct ParseTree {
    // TODO(plesslie): hold result of a parse
    int dummy;
};
//typedef struct ParseTree ParseTree;

struct Token {
    int value;
};

}

%parse_accept {
    printf("parsing succeeded!\n");
}

%parse_failure {
    printf("parsing failed!\n");
}

%stack_overflow {
    printf("stack overflow\n");
}

%syntax_error {
    printf("syntax error\n");
}

%token_prefix TK_

%name schemeParser

%extra_argument {struct ParseTree* parse}
// TODO(plesslie): just to silence a warning about unused variable
%token_destructor { parse->dummy = 1; }

//%token_type {int}
%token_type {struct Token*}
// %type expr {Expr*}

%left PLUS MINUS DIVIDE MULTIPLY.

program ::= expr.

expr ::= expr PLUS expr. { printf("Doing addition\n"); parse->dummy = 1; }
expr ::= expr MINUS expr. { printf("Doing subtraction\n"); }
expr ::= expr DIVIDE expr. { printf("Doing division\n"); }
expr ::= expr MULTIPLY expr. { printf("Doing multiplication\n"); }
expr ::= INTEGER(A). { printf("Matched integer: %d\n", A->value); }
