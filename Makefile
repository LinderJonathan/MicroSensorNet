CXX = g++

# -Iinclude if needed

CXXFLAGS = -Wall -Wextra -std=c++17

TARGET = main

SRCS = src/main.cpp

OBJS = $(SRCS:.cpp=.o)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm -f $(TARGET) $(OBJS)