all: secuencial

secuencial: secuencial.cpp
	g++ secuencial.cpp -o secuencial `pkg-config --cflags --libs opencv4`

clean: 
	rm -f secuencial