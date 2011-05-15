#!/bin/sh
#see README for original credits./tim

#Speed

#The following script compares the time usage for the different hash functions. 

for hashfunc in add xor sax sdbm bernstein ; do
	printf "% 10s: " "$hashfunc"
	time ./hash-fn-demo $hashfunc < hash-words-100 > /dev/null
done

#osman@osman-dev:~/src/algorist/1.1/ds$ sh hash-time-cmp.sh
#       add: 0.00user 0.00system 0:00.02elapsed 18%CPU (0avgtext+0avgdata 1568maxresident)k
#0inputs+0outputs (0major+137minor)pagefaults 0swaps
#       xor: 0.00user 0.00system 0:00.01elapsed 61%CPU (0avgtext+0avgdata 1568maxresident)k
#0inputs+0outputs (0major+137minor)pagefaults 0swaps
#       sax: 0.00user 0.00system 0:00.00elapsed 44%CPU (0avgtext+0avgdata 1568maxresident)k
#0inputs+0outputs (0major+137minor)pagefaults 0swaps
#      sdbm: 0.00user 0.00system 0:00.01elapsed 36%CPU (0avgtext+0avgdata 1568maxresident)k
#0inputs+0outputs (0major+137minor)pagefaults 0swaps
# bernstein: 0.00user 0.00system 0:00.01elapsed 40%CPU (0avgtext+0avgdata 1552maxresident)k
#0inputs+0outputs (0major+136minor)pagefaults 0swaps


