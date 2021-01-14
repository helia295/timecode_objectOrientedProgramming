all:
	g++ -Wall TimeCode.cpp TimeCodeTests.cpp -o nasa
	
run:
	./nasa
	
try: all run
