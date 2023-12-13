all: paraleloomp

paraleloomp: paraleloomp.cpp
	g++ paraleloomp.cpp -o paraleloomp `pkg-config --cflags --libs opencv4` -fopenmp

clean: 
	rm -f paraleloomp