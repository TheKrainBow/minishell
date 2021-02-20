SRCS_UTILS		=	srcs/main.c

SRCS_BUILTINS	=	srcs/builtins/env.c						\
					srcs/builtins/export.c					\
					srcs/builtins/unset.c					\
					srcs/builtins/cd.c						\
					srcs/builtins/echo.c					\
					srcs/builtins/echo2.c					\
					srcs/builtins/pwd.c						\

SRCS_EXECVE		=	srcs/execve/execve.c					

SRCS_LEX		=	srcs/lexer_parser/lexing.c				\
					srcs/lexer_parser/parsing.c				\

INCLUDES		=	-Iincludes								\
					-Ilibft/includes

SRCS			=	$(SRCS_UTILS) $(SRCS_LEX) $(SRCS_BUILTINS) $(SRCS_EXECVE)
OBJS			=	$(SRCS:.c=.o)

CC				=	clang
RM				=	@rm -f
NAME			=	minishell

LIBFT			=	libft/libft.a

LD_FLAGS		=	-g -fsanitize=address -Llibft -lft
FLAGS			=	-Wall -Werror -Wextra $(INCLUDES) -D BUFFER_SIZE=4096 -g

.c.o:
					@$(CC) -c $< -o $(<:.c=.o) $(FLAGS)

$(NAME):			clear_screen start_message $(LIBFT) $(OBJS)
					@if [ "$?" = "clear_screen start_message" ]; then echo -n "\033[2A\033[30C\033[0;33mAlready done\033[15D\033[1B\033[2A\033[2D\033[1;32m✓\033[1D\033[1B✓\033[26D\033[2B\033[0m";else echo -n "\033[2A\033[25C\033[1;32m✓\033[26D\033[2B\033[0m"; fi
					@$(CC) $(OBJS) $(FLAGS) -o $(NAME) $(LD_FLAGS)
					@echo "\033[1A\033[25C\033[1;32m✓\033[3A\033[1D✓\033[3B\033[0m"

$(LIBFT):
					@make -s -C libft -f Makefile
					@echo -n "\033[3A\033[25C\033[1;32m✓\033[26D\033[3B\033[0m"


all:				$(NAME)

bonus:				re

clear_screen:
					@clear

clean:
					@clear
					@echo "\033[0;33mCleaning \033[1;31mLibft\033[0;33m.\033[0m"
					@make -s -C libft -f Makefile clean
					@echo "\033[0;33mCleaning \033[1;31mMinishell\033[0;33m's objects\033[0m"
					$(RM) $(OBJS)

fclean:				clean
					@make -s -C libft -f Makefile fclean
					@echo "\033[0;33mRemoving \033[1;31mMinishell\033[0;33m.\033[0m"
					$(RM) $(NAME)

start_message:
					@echo "\033[0;33mMaking \033[1;31mMinishell\033[0;33m\t\033[1;30m[\033[1;31mX\033[1;30m]\033[0m"
					@echo "\033[1;32mCompiling libft\t\t\033[1;30m[\033[1;31mX\033[1;30m]\t\033[0;32m\033[0m"
					@echo "\033[1;32mCompiling objects\t\033[1;30m[\033[1;31mX\033[1;30m]\t\033[0;32m\033[0m"
					@echo "\033[1;32mLinking all objects\t\033[1;30m[\033[1;31mX\033[1;30m]\033[0;32m\033[0m"

re:					fclean start_message $(LIBFT) $(OBJS)
					@if [ "$?" = "start_message" ]; then echo -n "\033[1A\033[3C\033[0;33mAlready done\033[15D\033[1B\033[2A\033[2D\033[1;32m✓\033[1C\033[2B\033[1A\033[2D\033[1;32m✓\033[1C\033[1B\033[0m";else echo -n "\033[2A\033[25C\033[1;32m✓\033[26D\033[2B\033[0m"; fi
					@$(CC) $(OBJS) $(FLAGS) -o $(NAME) $(LD_FLAGS)
					@echo "\033[1A\033[25C\033[1;32m✓\033[3A\033[1D✓\033[3B\033[0m"

.PHONY:				all clean fclean re