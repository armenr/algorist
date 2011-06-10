/*see README for original credits */

#include"hash-fn.h"

/*
Additive
This function simply sums up the values of each character in the string. 
*/
hash_t add_hash(const void* key) {
	hash_t h = 0;
  const unsigned char* c = (const unsigned char*)key;
  
	while(*c) 
	  h += *c++;
	  
	return h;
}

/*
XOR

This function applies bitwise exclusive-or on all the characters. Note that the 
generated hash value will never be larger than UCHAR_MAX (normally 255) with 
this method. If key only consists of ASCII values, it will be maximum 127. So 
this function is a bad choice for large hash tables. 
*/
hash_t xor_hash(const void* key) {
	hash_t h = 0;
  const unsigned char* c = (const unsigned char*)key;
  
	while(*c) 
	  h ^= *c++;
	  
	return h;
}

/*
Shift-add-XOR

This function combines the first two functions (add and XOR) with a shift 
operation. 
*/
hash_t sax_hash(const void* key) {
	hash_t h = 0;
  const unsigned char* c = (const unsigned char*)key;
  
	while(*c) 
	  h ^= (h << 5) + (h >> 2) + (*c++);
	  
	return h;
}

/*
SDBM

This is an implementation of the [sdbm hash function]. 
*/
hash_t sdbm_hash(const void* key) {
	hash_t h = 0;
  const unsigned char* c = (const unsigned char*)key;
  
	while(*c) 
	  h = (*c++) + (h << 6) + (h << 16) - h;
	
	return h;
}

/*
Bernstein

This is an efficient hash function created by Daniel J. Bernstein. 
*/
hash_t bernstein_hash(const void* key) {
	hash_t h = 0;
  const unsigned char* c = (const unsigned char*)key;
  
	while(*c) 
	  h = 33 * h + (*c++);
	  
	return h;
}
