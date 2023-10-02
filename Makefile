CC_FLAGS += -O2 -std=c++17 -Wall -Wextra -c $(shell wx-config --cppflags)
LD_FLAGS += $(shell wx-config --libs)
CC = $(shell wx-config --cxx)

SOURCES := $(wildcard src/*.cpp)
HEADERS := $(wildcard includes/*.h)
OBJ = $(subst src,objects,$(subst .cpp,.o, $(SOURCES)))
RM = rm -rf

# Compilation and linking
all: objFolder app
	@ echo 'Done!'

app: $(OBJ) objects/sqlite3.o
	@ echo 'Building binary using GCC linker: $@'
	$(CC) $^ -o app $(LD_FLAGS)
	@ echo 'Finished building binary: $@'
	@ echo ' '

objects/sqlite3.o:
	gcc -c -o objects/sqlite3.o src/sqlite3.c

objects/%.o: src/%.cpp
	@ echo 'Building target using GCC compiler: $<'
	$(CC) $< $(CC_FLAGS) -o $@
	@ echo ' '

objFolder:
	@ mkdir -p objects

clean:
	@ $(RM) ./objects ./app

.PHONY: all clean
