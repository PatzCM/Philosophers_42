# Makefile for the Philosophers project

define HEADER
                                    ▓██▓▓                         
                                  █▓▒▓████▓▓                      
                                 ███▓██████████▓                  
                                 ▓▒░░░░▓███▓▓▓███                 
                                 ▒░░░░░▒████▓██▓▓▓                
                                ▒░░░░░░▒▓██▓█████▓                
                               ████▓░░░░▒▓▓▓░█████                
                              ░▓▓░█▓░░░░░░░▓░░██▓▓                
                              ░░░░░░░░░░░░░░░░▓█▓▓                
                              ▒▒██▒░░░░░░░░░░░░▓▓▓▓               
                              ███▒▓▓░░░░░░░░░░▓▓▓▓▓█▓▓▓▓▓         
                             ░▓████▓░░░░░░░░░▓█▓█▓█▓▓▓▓▓▓▓▒▒      
                          ▓▓░░▒█████████░░░█▓█▓█▓████▓█▓▓▓▓▓▓     
                         █░░░░░▓█     ▒░░▓█████████████▓▓▓▓▓▓     
                        ███▒▒▓███   ███████████████▓███▓█▓█▓▓     
                       ██████████ ████████████████████▓▓▓▓▓▓      
                      ▓██████▓████████████████▓█████▓▓▓▓▓▓▓       
                     ▒▓▓███▓████████████████████████▓▓▓▓▓▓▓       
                    ▒▒▓▒▒▓▓▓▓▓███████████████████████▓▓▓▓▓        
                   ░▒▒▓▓████▓████████████████▓███████▓▓▓▓         


██████╗ ██╗  ██╗██╗██╗      ██████╗ ███████╗ ██████╗ ██████╗ ██╗  ██╗███████╗██████╗ ███████╗
██╔══██╗██║  ██║██║██║     ██╔═══██╗██╔════╝██╔═══██╗██╔══██╗██║  ██║██╔════╝██╔══██╗██╔════╝
██████╔╝███████║██║██║     ██║   ██║███████╗██║   ██║██████╔╝███████║█████╗  ██████╔╝███████╗
██╔═══╝ ██╔══██║██║██║     ██║   ██║╚════██║██║   ██║██╔═══╝ ██╔══██║██╔══╝  ██╔══██╗╚════██║
██║     ██║  ██║██║███████╗╚██████╔╝███████║╚██████╔╝██║     ██║  ██║███████╗██║  ██║███████║
╚═╝     ╚═╝  ╚═╝╚═╝╚══════╝ ╚═════╝ ╚══════╝ ╚═════╝ ╚═╝     ╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝╚══════╝
                                                                                             

endef
export HEADER

# Colors
RESET = \033[0m
BOLD = \033[1m
GREEN = \033[32m
BLUE = \033[34m
CYAN = \033[36m
YELLOW = \033[33m
RED = \033[31m

# Symbols
CHECK = \033[32m✔\033[0m
CROSS = \033[31m✖\033[0m
INFO = \033[36mℹ\033[0m



# Compiler
CC = gcc

# Compiler flags
CFLAGS = -g -Wall -Werror -Wextra -fsanitize=thread

# Directory
DIR = srcs
# Source files
SRCS = $(DIR)/main.c $(DIR)/philo_utils.c $(DIR)/philo_time.c $(DIR)/data_init.c $(DIR)/philo_exit.c $(DIR)/phil_routine.c \

# Object files
OBJS = $(SRCS:.c=.o)

# Output executable
TARGET = philo

# Default target
all: $(TARGET)
	@echo "$(BOLD) $$HEADER $(RESET)"

# Compile source files into object files
%.o: %.c
	@clear
	@echo "$(INFO) $(YELLOW) Compiling $<... $(RESET)"
	@echo "$(CHECK) $(GREEN) Done! $(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

# Build the target
$(TARGET): $(OBJS)
	@echo "$(INFO) $(CYAN) Linking $(TARGET)... $(RESET)"
	@$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) -lreadline
	@echo "$(CHECK) $(GREEN) Done! $(RESET)"

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
