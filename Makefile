TARGET = $(BIN_DIR)/lawn
INCLUDE_DIR = ./include
BIN_DIR = ./bin
SRC_DIR = ./src
TEST_DIR = ./test

CC = gcc
WARNFLAGS	 = -Wall -Wextra -g
CFLAGS = $(WARNFLAGS) -I$(INCLUDE_DIR)
ARGS = "a.in" "a.out"

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(subst $(SRC_DIR), $(BIN_DIR), $(SRCS:.c=.o))

.PHONY: all clean run valgrind

all: $(TARGET)

run: $(TARGET)
	@$(TARGET) $(ARGS)

$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

valgrind: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes $(TARGET) $(ARGS)
