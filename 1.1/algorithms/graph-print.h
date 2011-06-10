/*see README for original credits */

#ifndef GRAPH_PRINT_H
#define GRAPH_PRINT_H

#include"../ds/graph1.h"
#include"graph-search.h"

void print_colors(const graph* g, const graph_search* gs);
void print_components(const graph* g, const graph_search* gs);
void print_fs(const graph* g, graph_search* gs);
void print_item(const char* item);
void print_top_sort(const graph_search* gs);

#endif /* GRAPH_PRINT_H */
