CPP=g++
OBJ=seat-random.exe
OPT=

all: $(OBJ)

$(OBJ): *.cpp
	$(CPP) -o $(OBJ) $(OPT) *.cpp

clean:
	rm -f $(OBJ)

run: $(OBJ)
	./$(OBJ)

.PHONY: all clean run