%include {

#include <stdint.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

typedef void SchemeParser;

enum OperatorType {
    OP_PLUS,
    OP_UNKNOWN
};
typedef enum OperatorType OperatorType;

enum NodeType {
    // Literal Types
    AST_BOOLEAN,
    AST_NUMBER,
    AST_CHARACTER,
    AST_STRING,
    AST_OPERATOR,
    AST_UNKNOWN
};
typedef enum NodeType NodeType;

// TODO(plesslie):
struct String {
    char *begin;
    char *end;
};
typedef struct String String;

int String_create(const char *restrict const begin,
                   const char *restrict const end,
                   String *str) {
    assert(str);
    assert(end - begin > 0);
    const size_t size = end - begin;
    str->begin = malloc(size);
    // TODO(plesslie): handle malloc fail
    assert(str->begin);
    str->end = str->begin + size;
    memcpy(str->begin, begin, size);
    return 0;
}

struct ParseTree {
    NodeType kind;
    union {
        struct {
            uint32_t info;
            uint32_t aux;
        } s;
        double nval;
        String sval;
    } u;

    struct ParseTree *l;
    struct ParseTree *r;

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

%token_type {const Token*}

program ::= expression.

expression ::= literal.

expression ::= LPAREN operator literal literal RPAREN. {
    printf("WOOT\n");
}

operator ::= PLUS. {
    parse->kind = AST_OPERATOR;
    parse->u.s.info = OP_PLUS;
}

//------------------------------------------------------------------------------
// Datum
//------------------------------------------------------------------------------
//datum ::= literal.

//------------------------------------------------------------------------------
// Literal (constant) Values
//------------------------------------------------------------------------------

literal ::= STRING(C). {
    const char *restrict const begin = C->begin;
    const char *restrict const end = C->end;
    parse->kind = AST_STRING;
    // TODO(plesslie): support unicode
    assert(end - begin >= 2);
    // REVISIT(plesslie): lexer strip double-quotes
    const int rval = String_create(begin + 1, end - 1, &parse->u.sval);
    assert(rval == 0);
}

literal ::= CHARACTER(C). {
    const char *restrict const begin = C->begin;
    const char *restrict const end = C->end;
    parse->kind = AST_CHARACTER;
    // TODO(plesslie): extremely naive, need to support unicode
    // assuming form "#\A", where A is any ASCII character
    assert(end - begin == 3);
    // REVISIT(plesslie): lexer strip prefix?
    parse->u.s.info = begin[2];
}

literal ::= BOOLEAN(B). {
    parse->kind = AST_BOOLEAN;
    assert(B->end - B->begin == 2);
    parse->u.nval = (B->begin[1] == 't' || B->begin[1] == 'T') ? 1.0 : 0.0;
}

literal ::= NUMBER(N). {
    const char *restrict begin = N->begin;
    const char *restrict end = N->end;
    parse->kind = AST_NUMBER;

    // TODO(plesslie): other numerical reprs
    assert(begin != 0);
    assert(end > begin);
    //parse->u.nval = sm_strtod(begin, end);

    char *buf = strndup(begin, end - begin);
    parse->u.nval = atof(buf);
    free(buf);
}
