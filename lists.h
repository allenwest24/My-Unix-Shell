#ifndef LISTS_H
#define LISTS_H

typedef struct list
{
	char* head;
	struct list* tail;
} list;

list* cons(char* xx, list* xs);
void free_list(list* xs);
void print_list(list* xs);
int length(list* xs);
list* reverse(list* xs);
list* rev_free(list* xs);

#endif
