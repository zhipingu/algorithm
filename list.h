#ifndef CMPS12B_LIST
#define CMPS12B_LIST

#include<assert.h>


typedef struct node_type{
	void *data;
	struct node_type* next;
} Node;

typedef struct {
	Node *head;
	int size;
} List;

Node* make_node(void* data, Node* next);
List* make_list();

void free_node(Node* node);
void free_list(List* list);

void add(List* list, int index, void* data);
void* get(List* list, int index);
void set(List* list, int index, void* data);


#endif

