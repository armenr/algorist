#!/bin/sh
#see README for original credits

#Collisions

#To check for collisions, we use the following shell script. The file words is 
#created by running shuffle -f /usr/share/dict/words >words on a NetBSD system. 

#If the parameter max is specified, the output is the size of the "biggest" 
#collision (most keys giving the same hash value). With the avg parameter, the 
#average collision size is calculated. Without a parameter, the output is the 
#total number of keys involved in collsions. 

case "$1" in
	"max")
		AWKCMD='{if($1>max) max=$1} END {print max?max:0}'
		FMT=" %7s"
	;;
	"avg")
		AWKCMD='{sum+=$1} END {print sum/NR}'
		FMT=" % 7.1f"
	;;
	*)
		AWKCMD='{if($1>1) ncoll+=$1} END {print ncoll?ncoll:0}'
		FMT=" %7s"
esac
	
echo "      func:size  10      50     100     500    1000    5000   10000   50000  100000  200000  500000  1000000"
for hashfunc in add xor sax sdbm bernstein ; do
	printf "% 10s:" "$hashfunc"
	for size in 10 50 100 500 1000 5000 10000 50000 100000 200000 500000 1000000; do
		head -n $size < hash-words |
			./hash-fn-demo $hashfunc $size |
			sort -n | 
			uniq -c | 
			awk "$AWKCMD" |
			xargs printf "$FMT"
	done
	echo
done

#osman@osman-dev:~/src/algorist/1.1/ds$ sh hash-coll-cmp.sh
#      func:size  10      50     100     500    1000    5000   10000   50000  100000  200000  500000  1000000
#       add:       7      27      64     317     700    4639    9719   49799   99823  199810  234774  234774
#       xor:       7      34      84     478     980    5000   10000   50000  100000  200000  234975  234975
#       sax:       4      28      71     311     623    3175    6321   31651   63180  126568   88239   49278
#      sdbm:       4      30      56     317     627    3218    6239   31537   63242  126320   87502   48972
# bernstein:       6      31      67     309     608    3164    6312   31835   63093  126034   87888   49148
#osman@osman-dev:~/src/algorist/1.1/ds$ sh hash-coll-cmp.sh avg
#      func:size  10      50     100     500    1000    5000   10000   50000  100000  200000  500000  1000000
#       add:     2.0     1.5     1.6     1.6     1.8     4.2     7.1    27.8    51.5    95.6   110.4   110.4
#       xor:     1.7     1.8     2.4     5.3     8.8    39.1    78.1   390.6   781.2  1562.5  1835.7  1835.7
#       sax:     1.2     1.5     1.8     1.6     1.6     1.6     1.6     1.6     1.6     1.6     1.3     1.1
#      sdbm:     1.2     1.5     1.5     1.6     1.6     1.6     1.6     1.6     1.6     1.6     1.3     1.1
# bernstein:     1.4     1.6     1.6     1.6     1.6     1.6     1.6     1.6     1.6     1.6     1.3     1.1
#osman@osman-dev:~/src/algorist/1.1/ds$ sh hash-coll-cmp.sh max
#      func:size  10      50     100     500    1000    5000   10000   50000  100000  200000  500000  1000000
#       add:       4       4       5       6       8      22      34     148     277     543     623     623
#       xor:       3       4       7      16      24      89     167     768    1488    2915    3422    3422
#       sax:       2       3       4       5       5       7       8       7       8       8       7       5
#      sdbm:       2       4       3       4       6       6       6       8       7       7       6       6
# bernstein:       2       4       4       6       6       6       6       6       8      10       6       5

