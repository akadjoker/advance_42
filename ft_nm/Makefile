NAME = ft_nm

# Diretórios
SRC_DIR = src
OBJDIR = obj
INCLUDE_DIR = include



# Headers
HEADERS = $(wildcard $(INCLUDE_DIR)/*.h)
INCLUDES = -I$(INCLUDE_DIR) 

# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
SANITIZE = -fsanitize=address -fsanitize=leak -fsanitize=undefined -fno-omit-frame-pointer

# Arquivos fonte e objeto
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJDIR)/%.o)

# Debug info
$(info == Debug Information ==)
$(info Sources: $(SRC))
$(info Objects: $(OBJ))
$(info Headers: $(HEADERS))
$(info =====================)

# Regras
all: mk_objdir  $(NAME)

mk_objdir:
	@mkdir -p $(OBJDIR)
	@echo "Created object directory: $(OBJDIR)"

simple:
	gcc -o simple simple.c
	gcc -c simple.c -o simple.o
	gcc -m32 -c simple.c -o simple_32.o 2>/dev/null


$(NAME): $(OBJ)
	@echo "Linking $(NAME)..."
	@$(CC) $(CFLAGS) $(SANITIZE) $(OBJ)  -o $(NAME)
	@echo "\033[1;32m$(NAME) built successfully!\033[0m"

$(OBJDIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	@echo "\033[1;34m  Compiling [$< to $@]\033[0m"
	@$(CC) $(CFLAGS) $(SANITIZE) $(INCLUDES) -c $< -o $@

clean:
	@echo "Cleaning objects..."
	@rm -rf $(OBJDIR)

fclean: clean
	@echo "Cleaning everything..."
	@rm -f $(NAME)
	@echo "\033[1;33mAll cleaned!\033[0m"

re: fclean all

check:
	@echo "\n\033[1;32m Checking project structure..."
	@echo "Current directory: $$(pwd)"
	@echo "\nChecking source directory ($(SRC_DIR)):"
	@ls -la $(SRC_DIR) || echo "$(SRC_DIR) not found!"
	@echo "\nChecking include directory:"
	@ls -la $(INCLUDE_DIR) || echo "$(INCLUDE_DIR) not found!"
	@echo "\nChecking headers:"
	@for header in $(HEADERS); do \
		if [ -f $$header ]; then \
			echo "$$header exists\033[0m"; \
		else \
			echo "$$header does not exist\033[0m"; \
		fi \
	done

.PHONY: all clean fclean re mk_objdir  check
