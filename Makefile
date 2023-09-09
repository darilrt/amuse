CC       := g++
C        := gcc
CCFLAGS  := -Wall -pedantic -std=c++17 -D _DEBUG
CFLAGS   := $(CCFLAGS)

LIBAMUSE := libamuse.a
SOURCES  := $(wildcard src/*.cpp) $(wildcard src/*/*.cpp)
OBJECTS  := $(subst .cpp,.o,$(SOURCES))
INCLUDES := -I./include -I/usr/include/SDL2 
AR       := ar
ARFLAGS  := -crs
RANLIB   := ranlib

./PHONY: all

all: info $(LIBAMUSE)

$(LIBAMUSE): $(OBJECTS)
	$(AR) $(ARFLAGS) $(LIBAMUSE) $(OBJECTS)
	$(RANLIB) $(LIBAMUSE)

%.o: %.cpp
	$(CC) $(CCFLAGS) -o $@ -c $^ $(INCLUDES)

info: 
	$(info $(SOURCES))
	$(info $(OBJECTS))

clean: 
	rm $(OBJECTS)

cleanall: clean
	rm $(LIBAMUSE)

