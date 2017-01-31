%include {
#include <stdint.h>
#include <assert.h>

struct Parse {
    // TODO(plesslie): hold result of a parse
    int dummy;
};
typedef struct Parse Parse;

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

%extra_argument {Parse* parse}
// TODO(plesslie): just to silence a warning about unused variable
%token_destructor { parse->dummy = 1; }

// TODO(plesslie)
%token_type {int}
// %token_type {Token*}
// %type expr {Expr*}

%left PLUS MINUS DIVIDE MULTIPLY.

program ::= expr.

expr ::= expr PLUS expr. { printf("Doing addition\n"); parse->dummy = 1; }
expr ::= expr MINUS expr. { printf("Doing subtraction\n"); }
expr ::= expr DIVIDE expr. { printf("Doing division\n"); }
expr ::= expr MULTIPLY expr. { printf("Doing multiplication\n"); }
expr ::= INTEGER(A). { printf("Matched integer: %d\n", A); }
