// task.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 128	/* maximum number characters in a line of the input file */
#define MAXNODE 26	/* maximum number of nodes in a graph */

typedef struct edge_r {
	int n_index;        	/* index of the destination node */
	struct edge_r * next;
	int length;
} edge_t;			/* An edge of a graph is represented by the index
					of the destination node, the length of the edge */

typedef struct {
	char name;
	edge_t *edge_list;
} node_t;			/* A node of a graph is represented by the name of
					of the node and edges starting from it */

node_t graph[MAXNODE];          /* A graph is a list of nodes and associated edges */
int    num_of_nodes;            /* the number of nodes in a graph */

								/* Create an edge with destination node index equal to np and length equal to weight */
edge_t *create_edge(int np,int wei) {
	edge_t *ep;
	ep = (edge_t *)malloc(sizeof(edge_t));
	ep->next = NULL;
	ep->n_index = np;
	ep->length = wei;
	return(ep);
}

void printgraph() {
	int i;
	edge_t *ep;

	printf("There are %d nodes\n", num_of_nodes);
	for (i = 0; i<num_of_nodes; i++) {
		printf("%d NODE %c", i, graph[i].name);
		ep = graph[i].edge_list;
		while (ep != NULL) {
			printf(" -->%c weight:%d ", graph[ep->n_index].name, ep->length);
			ep = ep->next;
		}
		printf("\n");
	}
}

/* Read a graph from file "filename" */
void readgraph(char *filename) {
	FILE *fp;
	char buf[MAXLEN]; 	    /* Buffer for a line from the text file */
	char *tmp[MAXNODE * 2];   /* Pointers to the names of nodes, and lengths if available */
	char sep_ch[] = " \n";    /* names and nodes are separated by space and newline */
	char nodename;          /* name of the node */
	int  ni;		/* index to the node */
	int  desti;		/* the destination index */
	edge_t *ep, *ep1;	/* pointer to the edge structure */
	int  i, j;

	fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("File %s does not exist!\n", filename);
		exit(1);
	}
	num_of_nodes = 0;
	while (fgets(buf, MAXLEN, fp) != NULL) {	/* read from the file until the end */
		j = 0;
		tmp[j] = strtok(buf, sep_ch);		/* separate line by space and new line */
		while (tmp[j] != NULL) {
			j++;
			tmp[j] = strtok(NULL, (char *)sep_ch);
		}
		if (j>0) {
			nodename = tmp[0][0];  	/* get the name of the node  */
			ni = nodename - 'A';		/* get the index of the node */
			if (num_of_nodes < ni + 1) num_of_nodes = ni + 1;  /* set the number of nodes */
			graph[ni].name = nodename;
			graph[ni].edge_list = NULL;
			ep = NULL;
			for (i = 1; i<j; i++) {		/* process each edge from the node */
				desti = tmp[i][0] - 'A';	/* get the destination node index  */
				ep1 = create_edge(desti,atoi(tmp[++i])); 		/* allocate an edge  */
				if (ep == NULL) graph[ni].edge_list = ep1;
				else ep->next = ep1;   	/* put the edge to the link list */
				ep = ep1; 		/* ep points to the end of the list */
			}
		}
	}
	fclose(fp);
}

int main(int argc, char *argv[]) {
	if(argc==2)readgraph(argv[1]);
	else printf("Usage: %s name_of_file_containing_the_graph\n", argv[0]);
	printgraph();
}

