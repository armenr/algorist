/*see README for original credits */

#ifndef BFSDFS_H
#define BFSDFS_H

#include"../ds/graph.h"

bool* processed;	/* which vertices have been processed */
bool* discovered;  /* which vertices have been found */
int* parent;	/* discovery relation */

int* entry_time;         /* time of vertex entry */
int* exit_time;          /* time of vertex exit */
int time;                       /* current event time */

void bfs(const graph *g, int start);
void dfs(const graph *g, int v);
void clear_search(void);
int edge_classification(int x, int y);
void find_path(int start, int end, const int parents[]);
void initialize_search(const graph *g);
void process_vertex_early(int v);
void process_vertex_late(int v);
void process_edge(int x, int y);

#endif /* BFSDFS_H */
