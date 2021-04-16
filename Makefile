TARGET=main

all: main play

main: $(TARGET).cc utils.cc
	g++ -o $@ $^

play:
	./main CDEF GHIJ GHIJ CDEF

clean:
	rm -f main utils.o
