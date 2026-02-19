SHELL := bash

CC := gcc
CFLAGS := -std=c99 -g -Iinclude -Wall -Wextra -MMD -MP -pthread

LD := $(CC)
LDLIBS := -lm -lSDL3 -pthread

SRC := $(shell fd -e c . src)
OBJ := $(SRC:src/%.c=build/%.o)
DEP := $(OBJ:.o=.d)
EXE := main

-include $(DEP)

.PHONY: all clean

all: $(EXE)

$(EXE): $(OBJ)
	$(LD) $(LDFLAGS) $(LDLIBS) $^ -o $@

build/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) -R $(EXE) build
