CC = g++
CFLAGS = -std=c++17
SRC = main.cpp gap_instance.cpp gap_solution.cpp greedy_local.cpp
OBJ = $(SRC:.cpp=.o)
EXEC = gap_simulator 
all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)