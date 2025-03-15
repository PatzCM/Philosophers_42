# Makefile for the Philosophers project

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Werror -Wextra

# Directory
DIR = srcs
# Source files
SRCS = $(wildcard $(DIR)/*.c)

# Object files
OBJS = $(SRCS:.c=.o)

# Output executable
TARGET = philo

# Default target
all: $(TARGET)

# Build the target
$(TARGET): $(OBJS)
	@echo "Linking $@..."
	$(CC) $(CFLAGS) -o $@ $^

# Compile source files into object files
%.o: %.c
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@

# Clean object files
clean:
	@echo "Cleaning object files..."
	@rm -f $(OBJS)

# Full clean including the executable
fclean: clean
	@echo "Cleaning executable..."
	@rm -f $(TARGET)

# Rebuild the project
re: fclean all

# Phony targets
.PHONY: all clean fclean re
