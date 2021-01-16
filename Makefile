all:
	g++ -std=c++11 -Wall -Wc++11-extensions TimeCode.cpp TimeCodeTests.cpp -o time-code
	g++ -std=c++11 -Wall -Wc++11-extensions TimeCode.cpp NASALaunchAnalysis.cpp -o nasa
	g++ -std=c++11 -Wall -Wc++11-extensions TimeCode.cpp PaintDryTimer.cpp -o pdt
	
run:
	./pdt
	
try: all run
