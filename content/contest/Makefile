CXX = g++
CXXFLAGS = -Wall -Wextra -Wshadow -g -std=c++20 -fsanitize=undefined,address

%: %.cpp
    $(CXX) $(CXXFLAGS) -o $@ $<
