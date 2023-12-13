all: paralelothread

paralelothread: paralelothread.cpp
	g++ paralelothread.cpp -o paralelothread `pkg-config --cflags --libs opencv4` -pthread

clean: 
	rm -f paralelothread