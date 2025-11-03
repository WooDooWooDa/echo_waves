CXX=emcc
CXXFLAGS=-I C:/SDL/include -s USE_SDL=3
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