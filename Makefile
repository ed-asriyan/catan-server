RM=rm -f
CXX = g++ -std=gnu++11
TARGET=server
# SOURCES=$(wildcard sources/logic/*.cpp sources/network/*.cpp sources/*.cpp)
SOURCES=$(wildcard sources/*.cpp sources/*/*.cpp)

FLAGS = -g -ggdb -static -Wall -O2 -lm

all: 
		$(CXX) $(FLAGS) $(SOURCES) -o $(TARGET)

clean:
		$(RM) $(OBJECTS) $(TARGET)
