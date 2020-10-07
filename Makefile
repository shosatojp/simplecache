SHELL=/bin/bash

PYTHON:=python3.8
PYTARGET:=simplecache$(shell ${PYTHON}-config --extension-suffix)
ARCH:=x86-64
TARGET:=simplecache-linux-$(ARCH)
CCOPT:=-std=c++2a -march=$(ARCH) -O2 -g -W -Wall $(shell ${PYTHON} -m pybind11 --includes)
CXX:=g++

all: $(TARGET) $(PYTARGET)

%.o: %.cpp
	$(CXX) -fPIC $(CCOPT) -c -o $@ $^

$(PYTARGET): util.o httpheader.o entry.o simple.o pymain.o
	$(CXX) $(CCOPT) -fPIC -shared $^ -o $@

$(TARGET): util.o httpheader.o entry.o simple.o main.o
	$(CXX) -static $(CCOPT) $^ -o $@

clean:
	rm -f *.o $(TARGET) *.so

# test:
# 	$(PYTHON) -c 'import simplecache'

# install:
# 	cp -i $(TARGET) ~/local/bin/simplecache