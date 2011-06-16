/*see README for original credits */

#include<ctype.h>
#include<string.h>
#include"util.h"

int compare_keys_int(const int* key1, const int* key2) {
  if(key1 == NULL && key2 == NULL)
    return 0;
  else if(key1 == NULL)
    return -1;
  else if(key2 == NULL)
    return 1;

  return (*key1) - (*key2);
}

int compare_keys_str(const char* key1, const char* key2) {
  if(key1 == NULL && key2 == NULL)
    return 0;
  else if(key1 == NULL)
    return -1;
  else if(key2 == NULL)
    return 1;

  return strcmp(key1, key2);
}

int compare_keys_str_p(const char** key1, const char** key2) {
  if(key1 == NULL && key2 == NULL)
    return 0;
  else if(key1 == NULL)
    return -1;
  else if(key2 == NULL)
    return 1;

  return (int)(strlen(*key1) - strlen(*key1));
}

int compare_keys_str_a(const char* key1[], const char* key2[]) {
  int i, 
    lx = (int)(sizeof(*key1)/ sizeof((*key1)[0])), 
    ly = (int)(sizeof(*key2)/ sizeof((*key2)[0])),
    l = (lx > ly) ? lx : ly;
    
    for(i = 0 ; l; i++)
	    if((*key1)[i] < (*key2)[i]) 
	      return -1;
	    else if((*key1)[i] > (*key2)[i]) 
	      return 1;
    
	return 0;
}

char* reverse_string(const char* s, char* d) {
  int i, l = (int)strlen(s);

  for(i = 0; i < l; i++) 
    d[i] = s[l-i-1];
  d[l] = '\0';    
  
  return d;
}

char* toupper_string(const char* s, char* d) {
  int i, l = (int)strlen(s)+1
  ;
  for(i = 0; i < l; i++) 
    d[i] = toupper(s[i]);
    
  return d;
}

