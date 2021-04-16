TARGET=main
OBJ=utils
CC=g++

all: main play

main: $(TARGET).cc $(OBJ).cc
	$(CC) -o $@ $^ -g

play:
	./$(TARGET) CDEF GHIJ GHIJ CDEF

gdb:
	gdb --args $(TARGET) --CDEF --GHIJ --GHIJ --CDEF

clean:
	rm -f $(TARGET) $(OBJ).o
