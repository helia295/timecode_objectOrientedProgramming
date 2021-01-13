all:
	g++ -Wall TimeCode.cpp TimeCodeTests.cpp -o test
	
run:
	./test
	
try: all run
