/*see README for original credits */

#ifndef GRAPH_OPS
#define GRAPH_OPS

#include<stdbool.h>

void add_graph_item(graph* g, const void* item, int sz);
void clear_graph(graph* g);
void delete_edge(graph* g, int x, int y);
void delete_vertex(graph* g, int v);
const edge_node* find_edge(const graph* g, int x, int y);
const vertex* find_vertex(const graph* g, int v);
void init_graph(graph* g, bool directed);
void insert_edge(graph* g, int x, int y, int w);
int insert_vertex(graph* g);
void print_graph(const graph* g, void (*print_item)(const void* item));

#endif /* GRAPH_OPS */
