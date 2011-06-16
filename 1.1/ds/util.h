/*see README for original credits */

#ifndef UTIL_H
#define UTIL_H

#define	max(A, B)		((A) > (B) ? (A) : (B))
#define min(A, B)		((A) < (B) ? (A) : (B))
#define STRCMP(a,R,b) (strcmp(a,b) R 0)

int compare_keys_int(const int* key1, const int* key2);
int compare_keys_str(const char* key1, const char* key2);
int compare_keys_str_p(const char** key1, const char** key2);
int compare_keys_str_a(const char* key1[], const char* key2[]);

char* reverse_string(const char* s, char* d);
char* toupper_string(const char* s, char* d);
 
#endif /* UTIL_H */
