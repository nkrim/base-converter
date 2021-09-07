CXX = g++
CXXFLAGS = -std=c++14 -Wall

OUT = basecon
OBJS = utils.o converter.o main.o

all: $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(OUT)

converter.o: utils.o
main.o: converter.o


.PHONY: clean
clean:
	rm -rf *.o $(OUT)