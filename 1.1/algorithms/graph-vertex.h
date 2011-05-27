/*see README for original credits */

#ifndef GRAPH_VERTEX_H
#define GRAPH_VERTEX_H

#include"graph-search.h"

void bi_conn_early(graph_search* gs, int v);
void bi_conn_late(graph_search* gs, int v);
void bi_conn_edge(graph_search* gs, int x, int y);
void bi_part_edge(graph_search* gs, int x, int y);
void bfs_early(graph_search* gs, int v);
void bfs_edge(graph_search* gs, int x, int y);
/*void cycle_edge(graph_search* gs, int x, int y);*/
void dfs_early(graph_search* gs, int v);
void dfs_late(graph_search* gs, int v);
void dfs_edge(graph_search* gs, int x, int y);
void strong_early(graph_search* gs, int v);
void strong_late(graph_search* gs, int v);
void strong_edge(graph_search* gs, int x, int y);
void top_sort_late(graph_search* gs, int v);
void top_sort_edge(graph_search* gs, int x, int y);

#endif /* GRAPH_VERTEX_H */
