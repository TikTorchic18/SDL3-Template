SHELL := bash

CC := gcc
CFLAGS := -std=c99
CFLAGS += -Iinclude
CFLAGS += -Wall -Wextra
CFLAGS += -MMD -MP
CFLAGS += -pthread

ifdef DEBUG
	CFLAGS += -g
endif

LD := $(CC)
LDFLAGS := -pthread
LDLIBS := -lm
LDLIBS += -lSDL3 -lSDL3_ttf -lSDL3_image

ifeq ($(DEBUG),ASAN)
	CFLAGS += -fsanitize=address
	LDFLAGS += -fsanitize=address
endif
ifeq ($(DEBUG),MSAN)
	CFLAGS += -fsanitize=memory
	LDFLAGS += -fsanitize=memory
endif
ifeq ($(DEBUG),TSAN)
	CFLAGS += -fsanitize=thread
	LDFLAGS += -fsanitize=thread
endif

SRC := $(shell find src -type f -name "*.c")
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
