NAME		:= philo_bonus
CC			:= cc
CFLAGS		:= -Wextra -Wall -Werror -pthread -O3

SRCS		:= main_bonus.c init_bonus.c error_checks_bonus.c death_checks_bonus.c routines_bonus.c timers_bonus.c utils_bonus.c utils2_bonus.c
OBJS		:= ${SRCS:.c=.o}

COLOR_RESET			=	\033[0m
COLOR_CYAN			=	\033[36m
COLOR_GREEN			=	\033[32m
COLOR_RED			=	\033[31m

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $<

$(NAME): compile_message $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(COLOR_GREEN)Compilation for $(NAME) complete$(COLOR_RESET)"

compile_message:
	@echo "$(COLOR_CYAN)Beginning compilation for: $(NAME)$(COLOR_RESET)"

clean:
	@echo "$(COLOR_CYAN)Cleaning compiled files$(COLOR_RESET)"
	@rm -rf $(OBJS)
	@echo "$(COLOR_GREEN)Cleanup completed.$(COLOR_RESET)"

fclean: clean
	@echo "$(COLOR_CYAN)Full compiled clean initiated$(COLOR_RESET)"
	@rm -rf $(NAME)
	@echo "$(COLOR_GREEN)Full-Clean completed.$(COLOR_RESET)"

re: fclean all

.PHONY: all, clean, fclean, re
