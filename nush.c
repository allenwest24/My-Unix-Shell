#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "tokenizer.h"
#include "ast.h"
#include "parse.h"

//-----------------------------------------------------------------------------------------------------

void
execute(char* cmd, nush_ast* ast)
{
    	int cpid;
    	if ((cpid = fork())) {
		// parent process

		//printf("Parent pid: %d\n", getpid());
		//cpid is child processid
		//printf("Parent knows child pid: %d\n", cpid);

	  	// Child may still be running until we wait.

		int status;
		waitpid(cpid, &status, 0);

		//printf("== executed program complete ==\n");

		//printf("child returned with wait code %d\n", status);
		if (WIFEXITED(status)) {
	     		//printf("child exited with exit code (or main returned) %d\n", WEXITSTATUS(status));
		}
    	}
    	else {
	 	// child process
	        //printf("Child pid: %d\n", getpid());
 	        //printf("Child knows parent pid: %d\n", getppid());

	        for (int ii = 0; ii < strlen(cmd); ++ii) {
    			if (cmd[ii] == ' ') {
				cmd[ii] = 0;
				break;
	    		}
       		 }
		if(ast->op == '=')
		{
			// The argv array for the child.
			// // Terminated by a null pointer.
			list* formerargs = ast->args;
			char* thisone = formerargs->head;
			char* args[] = {cmd, thisone, 0};
			//printf("== executed program's output: ==\n");
			////was execvp(cmd, args);	
			execvp(ast->cmd, args);
			//printf("Can't get here, exec only returns on error.");
		}
		else if(ast->op == '+')
		{
			nush_ast* left = ast->arg0;
			nush_ast* right = ast->arg1;
			execute(cmd, left);
			execute(cmd, right);
		}
    	}
}

//-----------------------------------------------------------------------------------------------------

int
main(int argc, char* argv[])
{
	char cmd[256];
	if (argc == 1) {
		while(1)
		{
			printf("nush$ ");
			fflush(stdout);
			char* rv = fgets(cmd, 256, stdin);
			if(!rv)
			{
				break;
			}
			list* tokens = tokenize(cmd);
			print_list(tokens);
			nush_ast* ast = parse(tokens);
			execute(cmd, ast);
			free_ast(ast);
			free_list(tokens);
		}
    	}
    	else {
		//memcpy(cmd, "echo", 5);
		char* fileName = argv[1];
		FILE* file = fopen(fileName, "r");
		char line[256];
		char line2[256];
		fgets(line, 256, file);
		fgets(line2, 256, file);
		//strcat(line, line2);
		char* rv = line;
		char* rv2 = line2;
		//printf("this is what is in line: %s\n", line);
		if(!rv)
		{
			exit(0);
		}
		fclose(file);
		list* tokens = tokenize(line);
		//printf("This is tokenizer output:\n");
		//print_list(tokens);
		nush_ast* ast = parse(tokens);
		//printf("This is the output:\n");
		execute(line, ast);

		int length = strlen(line2);
		//printf("%d\n", length);
		
		if(length > 1)
		{
			if(!rv2)
			{
				exit(0);
			}
			list* tokens2 = tokenize(line2);
			//printf("This is tokenizer output:\n");
			//print_list(tokens2);
			nush_ast* ast2 = parse(tokens2);
			//printf("This is the output:\n");
			execute(line2, ast2);
			free_ast(ast2);
			free_list(tokens2);
		}

		free_ast(ast);
		free_list(tokens);
   	}	
    	return 0;
}
