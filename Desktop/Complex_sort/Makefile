CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11
OBJ = Main.o Complex.o Sorting.o

all: complex_sort

complex_sort: $(OBJ)
	$(CXX) -o complex_sort $(OBJ)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f $(OBJ) complex_sort
