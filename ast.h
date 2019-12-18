#ifndef NUSH_AST_H
#define NUSH_AST_H

#include<stdlib.h>

#include "lists.h"

typedef struct nush_ast {
	char op;
	// Op is either:
	// one of: ;, &, |
	//     or: '=' for simplecommand
	struct nush_ast* arg0;
	struct nush_ast* arg1;
	char* cmd;
	list* args;
} nush_ast;

typedef struct nush_op_ast {
	char op;
	struct nush_ast* arg0;
	struct nush_ast* agr1;
} nush_op_ast;

typedef struct nush_scommand_ast {
	char op;
	char* cmd;
	list* args;
} nush_scommand_ast;

nush_ast* make_ast_scommand(list* tokens);
nush_ast* make_ast_op(char op, nush_ast* a0, nush_ast* a1);
void free_ast(nush_ast* ast);
//added as a check
void print_ast(nush_ast* ast);

//should be all the functions we need because we do the evaluation in fork.


#endif
