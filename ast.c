#include <stdio.h>
#include <stdlib.h>

#include "ast.h"

nush_ast*
make_ast_scommand(list* tokens)
{
	nush_ast* ast = calloc(1, sizeof(nush_ast));
	ast->op = '=';
	ast->cmd = tokens->head;
	ast->args = tokens->tail;
	ast->arg0 = 0;
	ast->arg1 = 0;
	//puts("ast_scommand made");
	return ast;
}

nush_ast*
make_ast_op(char op, nush_ast* a0, nush_ast* a1)
{
	nush_ast* ast = malloc(sizeof(nush_ast));
	ast->op = op;
	ast->arg0 = a0;
	ast->arg1 = a1;
	//puts("ast_op made");
	return ast;
}

void 
free_ast(nush_ast* ast)
{
	if(ast)
	{
		if(ast->arg0) 
		{
			free_ast(ast->arg0);
		}
		if(ast->arg1)
		{
			free_ast(ast->arg1);
		}
		free(ast);
	}
	//puts("freed ast");
}
