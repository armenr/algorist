/*see README for original credits */

#ifndef SORT_H
#define SORT_H

#define NELEM	8		/* size of test arrays */

int binary_search(const int s[], int key, int low, int high);
void heap_sort(int s[], int n);
void insertion_sort(int s[], int n);
void merge_sort(int s[], int low, int high);
void quick_sort(int s[], int l, int h);
void selection_sort(int s[], int n);

#endif /* SORT_H */
