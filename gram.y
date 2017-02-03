%include {

#include <stdint.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

typedef void SchemeParser;

enum NodeType {
    AST_BOOLEAN,
    AST_NUMBER,
    AST_UNKNOWN
};
typedef enum NodeType NodeType;

struct ParseTree {
    NodeType kind;
    double   nval;

    int dummy; // TODO(plesslie): remove
};
typedef struct ParseTree ParseTree;

int g_parse_accepted = 0;

struct Token {
    const char *restrict const begin;
    const char *restrict const end;
};
typedef struct Token Token;

} // end %include

%parse_accept {
    g_parse_accepted = 1;
}

%parse_failure {
    // TODO(plesslie): add error message
    g_parse_accepted = 0;
    assert(0);
}

%stack_overflow {
    // TODO(plesslie): add error message
    g_parse_accepted = 0;
    assert(0);
}

%syntax_error {
    // TODO(plesslie): add error message
    g_parse_accepted = 0;
    assert(0);
}

%token_prefix TK_

%name schemeParser

%extra_argument {struct ParseTree* parse}

%token_type {struct Token*}

constant ::= BOOLEAN(B). {
    parse->kind = AST_BOOLEAN;
    assert(B->end - B->begin == 2);
    parse->nval = (B->begin[1] == 't' || B->begin[1] == 'T') ? 1.0 : 0.0;
}

constant ::= NUMBER(N). {
    const char *restrict begin = N->begin;
    const char *restrict end = N->end;
    parse->kind = AST_NUMBER;

    // TODO(plesslie): other numerical reprs
    assert(begin != 0);
    assert(end > begin);
    //parse->nval = sm_strtod(begin, end);

    char *buf = strndup(begin, end - begin);
    parse->nval = atof(buf);
    free(buf);
}
