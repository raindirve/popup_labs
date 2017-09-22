
default:
	g++ -Wall -g -O2 -static -std=gnu++11 lab1.h lab1.cpp lab1typing.cpp intervaltest.cpp

knapsack:
	g++ -Wall -g -O2 -static -std=gnu++11 -o kstest.bin lab1.h lab1.cpp knapsack_test.cpp

auf:
	g++ -Wall -g -O2 -static -std=gnu++11 -o uftest.bin almost_unionfind2.cpp
	
fenwick:
	g++ -Wall -g -O2 -static -std=gnu++11 -o fenwick.bin fenwick.cpp
	
polymult:
	g++ -Wall -g -O2 -static -std=gnu++11 -o polymult.bin polymult.cpp

r: default
	./a.out
