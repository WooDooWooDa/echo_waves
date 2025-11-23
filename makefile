CXX=emcc
CXXFLAGS=-std=c++20 -I C:/SDL/include -s USE_SDL=3 USE_SDL_TTF=3
SRCS=$(wildcard *.cpp)
OBJS=$(SRCS:.cpp=.o)
TARGET=index.html

all: $(TARGET)

%.o: %.cpp
    $(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
    $(CXX) $(OBJS) $(CXXFLAGS) -o $(TARGET)

clean:
    rm -f *.o $(TARGET)