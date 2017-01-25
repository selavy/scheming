%include {
#include <stdint.h>
#include <assert.h>
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

// TODO(plesslie)
%token_type {int}
// %token_type {Token*}
// %type expr {Expr*}

%left PLUS.

program ::= expr.

expr ::= expr PLUS expr. { printf("Doing addition\n"); }
expr ::= INTEGER(A). { printf("Matched integer: %d\n", A); }
