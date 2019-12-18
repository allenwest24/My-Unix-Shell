#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "lists.h"

//these are where all the list functions are.
// based off of nats notes lecture 9 list.c

//this makes a linked list
list*
cons(char* xx, list* xs)
{
	list* ys = malloc(sizeof(list));
	ys->head = strdup(xx); 
	ys->tail = xs;
	return ys;
}

//goes through the list by recurring over the tail and freeing the head
void
free_list(list* xs)
{
	if (xs) 
	{
		free_list(xs-> tail);
		free(xs->head);
		free(xs);
	}
}

//prints out the linked list
void
print_list(list* xs)
{
	for(; xs; xs = xs->tail)
	{
		printf("%s\n", xs->head);
	}
}

int
length(list* xs)
{
	int yy = 0;
		for(; xs; xs = xs->tail) {
			yy++;
		}
	return yy;
}

//reverse the list
list*
reverse(list* xs)
{
	list* ys = 0;
	for(; xs; xs = xs->tail) 
	{
		ys = cons(xs->head, ys);
	}
	return ys;
}

//makes a new list that is the reverse of the given list and handles freeing the old list
list*
rev_free(list* xs)
{
	list* ys = reverse(xs);
	free_list(xs);
	return ys;
}






