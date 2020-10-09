SHELL=/bin/bash

PYTHON?=python3
PYTARGET:=_simplecache$(shell ${PYTHON}-config --extension-suffix)
TARGET:=simplecache
CCOPT:=-std=c++11 -O2 -g -W -Wall $(shell ${PYTHON} -m pybind11 --includes)
CXX?=g++

all: $(TARGET) $(PYTARGET)
py: $(PYTARGET)
cli: $(TARGET)

%.o: %.cpp
	$(CXX) -fPIC $(CCOPT) -c -o $@ $^

$(PYTARGET): util.o httpheader.o entry.o simple.o pymain.o
	$(CXX) $(CCOPT) -fPIC -shared $^ -lstdc++fs -o $@

$(TARGET): util.o httpheader.o entry.o simple.o main.o
	mkdir -p bin
	$(CXX) $(CCOPT) $^ -lstdc++fs -o bin/$@

clean:
	rm -rfv *.o bin *.so

test:
	$(PYTHON) -c 'import simplecache'
