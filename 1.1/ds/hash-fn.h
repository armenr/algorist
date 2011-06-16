/*see README for original credits */

#ifndef HASH_FN_H
#define HASH_FN_H

typedef unsigned long hash_t;

typedef struct hashfunc_s {
	const char* name;
	hash_t (*func)(const void* key);
} hashfunc_s;

/*
Additive
This function simply sums up the values of each character in the string. 
*/
hash_t add_hash(const void* key);

/*
XOR

This function applies bitwise exclusive-or on all the characters. Note that the 
generated hash value will never be larger than UCHAR_MAX (normally 255) with 
this method. If key only consists of ASCII values, it will be maximum 127. So 
this function is a bad choice for large hash tables. 
*/
hash_t xor_hash(const void* key);

/*
Shift-add-XOR

This function combines the first two functions (add and XOR) with a shift 
operation. 
*/
hash_t sax_hash(const void* key);

/*
SDBM

This is an implementation of the [sdbm hash function]. 
*/
hash_t sdbm_hash(const void* key);

/*
Bernstein

This is an efficient hash function created by Daniel J. Bernstein. 
*/
hash_t bernstein_hash(const void* key);

#endif /* HASH_FN_H */
