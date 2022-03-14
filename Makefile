TARGET=main
OBJ=utils
CC=g++
STR=CDEF IJKL IJKL CDEF

all: main play anime

main: $(TARGET).cc $(OBJ).cc
	$(CC) -o $@ $^ -g -O3

play:
	./$(TARGET) $(STR)
	# ./$(TARGET) CDEF IJKL ABEG HIKM

anime:
	./animeroutemaker.sh
	python coinMoveAnime.py

gdb:
	gdb --args $(TARGET) --CDEF --IJKL --IJKL --CDEF

clean:
	rm -f $(TARGET) $(OBJ).o route.txt
