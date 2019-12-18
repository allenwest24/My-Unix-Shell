#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#include "lists.h" // required to define the format of a linked list

//multiple ideas based off of Nat Tuck's lecture 09

//to handle input that isnt a special case
static
char*
read_input(const char* text, int ii)
{
	int nn = 0;
	while(!(isspace(text[ii + nn])) && !(text[ii+nn] == ';') && !(text[ii+nn] == '|') && !(text[ii+nn] == '&')) 
	{
		++nn;
	}

	char* input = malloc(nn + 1);
	memcpy(input, text + ii, nn);
	input[nn] = 0;
	return input;
}

//handles tokenizing, possibly sending to read_input should it need it.
list*
tokenize(const char* text)
{
	list* xs = 0;

	int nn = strlen(text);
	int ii = 0;
	while(ii < nn) 
	{
		if(isspace(text[ii]))
		{
			++ii;
			continue;
		}
		/*else if(text[ii] == '\n')
		{
			++ii;
			continue;
		}*/
		else if(text[ii] == ';')
		{
			char* input = malloc(2);
			//memcpy(input, text + ii, 1);
			xs = cons(";", xs);
			++ii;
			free(input);
			continue;
		}
		else if(text[ii] == '|')
		{
			//double instance
			if(text[ii+1] == '|')
			{
				char* input = malloc(3);
				strcpy(input, "||");
				xs = cons(input, xs);
				++ii;
				++ii;
				free(input);
			}
			//one instance
			else
			{
				char* input = malloc(2);
				//memcpy(input, text + ii, 1);
				xs = cons("|", xs);
				++ii;
				free(input);
			}
			continue;
		}
		else if(text[ii] == '&')
		{
			//double instance
			if(text[ii+1] == '&')
			{
				char* input = malloc(3);
				strcpy(input, "&&");
				xs = cons(input, xs);
				++ii;
				++ii;
				free(input);
			}
			// single instance
			else
			{
				char* input = malloc(2);
				//memcpy(input, text + ii, 1);
				xs = cons("&", xs);
				++ii;
				free(input);
			}
			continue;
		}
		else
		{
			char* input = read_input(text, ii);
			xs = cons(input, xs);
			ii += strlen(input);
			free(input);
			continue;
		}
	}
	// i only added this because in the directions for this project the say you need to have the list of items then print it backwards. Otherwise calling it double is pointless
	return rev_free(xs);
}

