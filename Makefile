CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf
NAME = pipex
NAME1 = pipex_bonus
SOURCES = \
		libft_utils.c \
		check_path.c \
		exit_error.c \
		pipex_process.c \
		pipex.c

BSOURCES = \
		libft_utils.c \
		check_path.c \
		exit_error.c \
		pipex_process.c \
		pipex_process_bonus.c \
		pipex_bonus.c

OBJS = $(SOURCES:.c=.o)
BOBJS = $(BSOURCES:.c=.o)

all: $(NAME)

bonus: $(NAME1)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(lib):
	@make all -C $(LIB_DIR) > /dev/null 2>&1
	@echo "\033[32m	Libft Compiled Successfully! ✅\033[0m"

$(NAME): $(OBJS) $(lib)
	@$(CC) $(CFLAGS) $(OBJS) ./LIBFT/libft.a -o $(NAME)
	@echo "\033[32m	Pipex Compiled Successfully! ✅\033[0m"

$(NAME1): $(BOBJS) $(lib)
	@$(CC) $(CFLAGS) $(BOBJS) ./LIBFT/libft.a -o $(NAME1)
	@echo "\033[32m	Pipex_bonus Compiled Successfully! ✅\033[0m"

clean:
	@$(RM) $(OBJS) $(BOBJS)
	@echo "\033[33m	Object Files Removed! 🗑️\033[0m"

fclean: clean
	@$(RM) $(NAME) $(NAME1)
	@echo "\033[31m	Executable removed! ❌\033[0m"

re: fclean all

.PHONY: all clean fclean re
.SECONDARY: $(OBJS) $(BOBJS)
