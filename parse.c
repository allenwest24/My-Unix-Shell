#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "ast.h"
#include "parse.h"

//just a helper method to see if two strings are the same
int
streq(const char* aa, const char* bb)
{
	return strcmp(aa, bb) == 0;
}


// helper for contains that finds first instance of something
int
find_first_index(list* tokens, const char* tt)
{
	int ii = 0;
	for(list* it = tokens; it; it = it->tail) {
		if (streq(it->head, tt)) {
			return ii;
		}
		ii++;
	}
	return -1;
}

// is something in a list of tokens?
int contains(list* tokens, const char* tt)
{
	return find_first_index(tokens, tt) != -1;
}

//creates a slice from i0 to i1-1
list*
slice(list* xs, int i0, int i1)
{
	list* ys = 0;
	for(int ii = 0; ii < i1; ++ii) {
		if(ii >= i0) {
			ys = cons(xs->head, ys);
		}
		xs = xs->tail;
	}
	return rev_free(ys);
}


nush_ast*
parse(list* tokens)
{
	//add more as needed
	const char* ops[] = {";", "|"};

	int has_op = 0;
	for(int ii = 0; ii < 2; ++ii) {
		const char* op = ops[ii];

		if (contains(tokens, op)) {
			//puts("contains works");
			int jj = find_first_index(tokens, op);
			list* xs = slice(tokens, 0, jj);
			list* ys = slice(tokens, jj+1, length(tokens));
			// arg0 and arg1 are ast but can be scommand like below
			nush_ast* ast = make_ast_op(op[0], parse(xs), parse(ys));
			free_list(xs);
			free_list(ys);
			++has_op;
			return ast;
		}
	}
	//this should be the case if all we have left is a command with some or no arguments
	if(has_op == 0)
	{
		/*list* tester_list = tokens->tail;
		const char* cmds[] = {"echo", "random"};
		int has_cmd = 0;
		for(int ii = 0; ii < 2; ++ii) {
			const char* cmd = cmds[ii];
			if(contains(tester_list, cmd)) {
				int jj = find_first_index(tester_list, cmd);
				list* xs = slice(tokens, 0, ii);
				list* ys = slice(tokens, ii, length(tester_list));
				nush_ast* ast = make_ast_op('+', parse(xs), parse(ys));
				free_list(xs);
				free_list(ys);
				++has_cmd;
				return ast;
			}
		
		if(has_cmd == 0)
		{*/
		nush_ast* ast = make_ast_scommand(tokens);
		return ast;
		//}
	}
}
