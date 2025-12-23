CXX = g++
CXXFLAGS = -std=c++11 -w

TARGET = lab7

SRCS = lab7.cpp
HEADERS = lab7.h

all: $(TARGET)

$(TARGET): $(SRCS) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET)
