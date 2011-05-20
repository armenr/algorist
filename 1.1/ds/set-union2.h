/*see README for original credits */

#ifndef SET_UNION2_H
#define SET_UNION2_H

/*
In a disjoint set forest, we represent each partition using a tree (not 
necessarily a binary tree). The nodes of the tree have no child pointers, but 
do have parent pointers. We use void pointers for the values to allow any value 
to be placed in the data structure (in other languages one would use generics 
here):

Although simple, the algorithm described so far has the problem that the tree 
can, over many merge operations, develop a large height. Since the find 
operation takes time proportional to tree height, this can lead to linear 
worst-case time. Recalling that we can attach either root to the other during a 
merge, we would ideally always attach the tree of smaller height to the root of 
the tree of larger height. Unfortunately, height is expensive to calculate, 
especially without child pointers. Instead, we'll use a rough estimate of height 
called the rank, stored in the tree's root node: 
*/
typedef struct forest_node {
  void* item;
  struct forest_node* parent;
  int rank;
} forest_node;

/*
A disjoint set data structure, also known as a union-find set, is a data 
structure that keeps track of a partitioning of a set of elements over time as 
certain operations are done. The three main operations are:

    * MakeSet: Create a new partition containing a single given element.
    * Find: Figure out which partition a given element is in.
    * Merge/Union: Merge two partitions into a single partition. 

There are several solutions to this problem. The most efficient known and most 
commonly used is disjoint set forests with path compression and the union rank 
heuristic, which has a performance of O(α(n)) amortized time per operation, 
where α(n) [inverse ackermann?] is a very slowly growing function that for all 
practical purposes never exceeds 5
*/
void init_set_union2(forest_node** node, const void* item, int sz);
void merge_set_union2(forest_node* node1, forest_node* node2);
const forest_node* find_set_union2(forest_node* node);

#endif /*SET_UNION2_H */

