CXX = g++

# -Iinclude if needed

CPPFLAGS += -Isrc -I$(CURDIR)/vcpkg_installed/x64-windows/include/

CXXFLAGS = -Wall -Wextra -std=c++17 $(CPPFLAGS)

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