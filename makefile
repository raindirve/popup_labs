
default:
	g++ -Wall -g -O2 -static -std=gnu++11 lab1.h lab1.cpp lab1typing.cpp intervaltest.cpp

knapsack:
	g++ -Wall -g -O2 -static -std=gnu++11 lab1.h lab1.cpp lab1typing.cpp knapsacktest.cpp

r: default
	./a.out
