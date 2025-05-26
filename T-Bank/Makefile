CXX = g++
CXXFLAGS = -Wall -std=c++17 -O2 -pthread

all: init client

bank.o: bank.cpp bank.h
	$(CXX) $(CXXFLAGS) -c bank.cpp -o bank.o

init: init.o bank.o
	$(CXX) $(CXXFLAGS) -o init init.o bank.o

client: client.o bank.o
	$(CXX) $(CXXFLAGS) -o client client.o bank.o

init.o: init.cpp bank.h
	$(CXX) $(CXXFLAGS) -c init.cpp -o init.o

client.o: client.cpp bank.h
	$(CXX) $(CXXFLAGS) -c client.cpp -o client.o

clean:
	rm -f *.o init client

