# This file demonstrates how to compile the hello-world project
# on Linux. Just run "make" to compile it.

GPP=g++
GCC=gcc
OUTFILE="pythonplugin.so"

# sources
AMX_FILES=getch.o
SDK_FILES=amxplugin.o
PROJ_SOURCE=$(wildcard *.cpp)
PROJ_FILES=$(PROJ_SOURCE:.cpp=.o)


COMPILE_FLAGS=-c -O3 -w -DLINUX -I./SDK/amx/ $(shell python-config --includes)

all: $(PROJ_SOURCE) $(OUTFILE)

$(OUTFILE): $(PROJ_FILES)
	$(GPP) -O3 -fshort-wchar -shared $(shell python-config --ldflags) -o $@ *.o

$(PROJ_FILES): $(PROJ_SOURCE) $(SDK_FILES)
	$(GPP) $(COMPILE_FLAGS) *.cpp

$(SDK_FILES): $(AMX_FILES)
	$(GPP) $(COMPILE_FLAGS) ./SDK/*.cpp

$(AMX_FILES):
	$(GCC) $(COMPILE_FLAGS) ./SDK/amx/*.c

clean:
	rm *.o $(OUTFILE)
