all:
	g++ -std=c++11 -Wall -Wc++11-extensions TimeCode.cpp TimeCodeTests.cpp -o test
	
run:
	./test
	
try: all run
