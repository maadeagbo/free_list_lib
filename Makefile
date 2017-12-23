all:
	g++ -Wall -ggdb -std=c++11 -o freelist_test *.cpp 
	rm -rf *.o

clean:
	rm -rf *.o freelist_test