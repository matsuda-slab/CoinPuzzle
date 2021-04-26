TARGET=main
OBJ=utils
CC=g++
STR=CDEF IJKL IJKL CDEF

all: main play

main: $(TARGET).cc $(OBJ).cc
	$(CC) -o $@ $^ -g -O3

play:
	./$(TARGET) $(STR)
	# ./$(TARGET) CDEF IJKL ABEG HIKM

gdb:
	gdb --args $(TARGET) --CDEF --IJKL --IJKL --CDEF

clean:
	rm -f $(TARGET) $(OBJ).o
