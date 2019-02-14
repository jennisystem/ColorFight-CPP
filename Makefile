all: exampleAI

exampleAI: exampleAI.cpp colorfight.o
	g++ --std=c++11 -lcurl exampleAI.cpp colorfight.o -o exampleAI

colorfight.o: colorfight.cpp
	g++ --std=c++11 -c -lcurl colorfight.cpp

clean:
	rm *.o exampleAI