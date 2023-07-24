CC = g++
CFLAGS = -std=c++17
SRC = main.cpp gap/gap_instance.cpp heuristicas/greedy_local.cpp gap/gap_solution.cpp gap/gap_cost.cpp auxiliares/auxiliares.cpp heuristicas/worst_fit.cpp busq_locales/relocate_ls.cpp busq_locales/swap_ls.cpp metaheuristicas/grasp.cpp
OBJ = $(SRC:.cpp=.o)
EXEC = gap_simulator 
all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)