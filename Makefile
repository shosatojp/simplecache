SHELL=/bin/bash

PYTHON:=python3.8
PYTARGET:=_simplecache$(shell ${PYTHON}-config --extension-suffix)
ARCH:=x86-64
TARGET:=simplecache-linux-$(ARCH)
CCOPT:=-std=c++2a -march=$(ARCH) -O2 -g -W -Wall $(shell ${PYTHON} -m pybind11 --includes)
CXX:=g++

all: $(TARGET) $(PYTARGET)
py: $(PYTARGET)
cli: $(TARGET)

%.o: %.cpp
	$(CXX) -fPIC $(CCOPT) -c -o $@ $^

$(PYTARGET): util.o httpheader.o entry.o simple.o pymain.o
	$(CXX) $(CCOPT) -fPIC -shared $^ -o $@

$(TARGET): util.o httpheader.o entry.o simple.o main.o
	mkdir -p bin
	$(CXX) $(CCOPT) $^ -o bin/$@

clean:
	rm -rfv *.o bin *.so

test:
	$(PYTHON) -c 'import simplecache'
