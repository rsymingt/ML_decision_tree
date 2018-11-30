
all: main

main: main.cpp src/*.cpp include/*.hpp
	g++ main.cpp src/*.cpp -Iinclude -o main

clean:
	rm main
