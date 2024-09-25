CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11
SRCS = main.cpp complex.cpp sorter.cpp

OBJS = $(SRCS:.cpp=.o)

TARGET = complex_numbers

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean

