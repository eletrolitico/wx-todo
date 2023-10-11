CC_FLAGS += -std=c++17 -g -c $(shell wx-config --cppflags)
LD_FLAGS += $(shell wx-config --libs)
CC = $(shell wx-config --cxx)

SOURCES := $(wildcard src/*.cpp)
HEADERS := $(wildcard includes/*.h)
OBJ = $(subst src,objects,$(subst .cpp,.o, $(SOURCES)))
RM = rm -rf

OBJ += objects/sqlite3.o

ifeq ($(OS), Windows_NT)
	OBJ += objects/rsrc.o
	LD_FLAGS += -Wl,--subsystem,console
	CC = x86_64-w64-mingw32-g++
else
	CC_FLAGS += -Wall -Wextra
endif

# Compilation and linking
all: objFolder app
	@ echo 'Done!'

app: $(OBJ)
	@ echo 'Building binary using GCC linker: $@'
	$(CC) $^ -o app $(LD_FLAGS)
	@ echo 'Finished building binary: $@'
	@ echo ' '

objects/rsrc.o:
	windres -IC:/msys64/mingw64/lib/wx/include/msw-unicode-3.0 -IC:/msys64/mingw64/include/wx-3.0 -J rc -O coff -i todo.rc -o objects/rsrc.o

objects/sqlite3.o:
	gcc -c -O2 -o objects/sqlite3.o src/sqlite3.c

objects/%.o: src/%.cpp
	@ echo 'Building target using GCC compiler: $<'
	$(CC) $(CC_FLAGS) -o $@ $<
	@ echo ' '

objFolder:
	@ mkdir -p objects

clean:
	@ $(RM) ./objects ./app

.PHONY: all clean
