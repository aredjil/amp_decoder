CC=g++
LFLAGS= -O3 -march=native 
CFLAGS= -I./include 

all: main_ser.x main_mse.x 

main_ser.x: src/main.cpp src/amp.cpp 
	$(CC) $(CFLAGS) $^ -o $@ $(LFLAGS)
main_mse.x: src/main.cpp src/amp.cpp
	$(CC) $(CFLAGS) $^ -o $@ $(LFLAGS) -DMSE

clean:
	rm *.x 
