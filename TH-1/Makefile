CXX = g++
CXXFLAGS = -Wextra -Wall -pthread -std=c++17
LDFLAGS=-pthread

TARGET=main
SRC=main.cpp
OBJ=$(SRC:.cpp=.o)

all: $(TARGET)
$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
.PHONY: all clean

