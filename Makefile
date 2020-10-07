SHELL=/bin/bash

PYTHON:=python3.8
PYTARGET:=simplecache$(shell ${PYTHON}-config --extension-suffix)
TARGET:=simplecache-linux-x86_64
CCOPT:=-std=c++2a -g -W -Wall $(shell ${PYTHON} -m pybind11 --includes)
CXX:=g++

all: $(TARGET) $(PYTARGET)

%.o: %.cpp
	$(CXX) -fPIC $(CCOPT) -c -o $@ $^

$(PYTARGET): util.o httpheader.o entry.o simple.o pymain.o
	$(CXX) $(CCOPT) -O3 -fPIC -shared $^ -lstdc++fs -lz -o $@

$(TARGET): util.o httpheader.o entry.o simple.o main.o
	$(CXX) -static $(CCOPT) $^ -lstdc++fs -lz -o $@

clean:
	rm -f *.o $(TARGET) *.so

# test:
# 	$(PYTHON) -c 'import simplecache'

# install:
# 	cp -i $(TARGET) ~/local/bin/simplecache