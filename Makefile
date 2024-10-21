CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11

TARGET = read-file
OBJECT = main.o

all: $(TARGET)

$(TARGET): $(OBJECT)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECT)

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

clean:
	rm -f *.o $(TARGET)

