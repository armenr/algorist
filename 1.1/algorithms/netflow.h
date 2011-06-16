/*see README for original credits */

#ifndef NETFLOW_H
#define NETFLOW_H

#include<stdbool.h>
#include"../ds/graph1.h"

#define MAXDEGREE	50		/* maximum outdegree of a vertex */
#define min(A, B)		((A) < (B) ? (A) : (B))

typedef struct flow_node {
	int flow;			/* flow through edge */
	int residual;			/* residual capacity of edge */
} flow_node;

void netflow(graph* g, int source, int sink);
void print_flow_graph(const graph* g, int source);

#endif /* NETFLOW_H */

