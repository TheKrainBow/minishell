SRCS_UTILS		=	srcs/core/main.c						\
					srcs/core/history.c						\
					srcs/core/signals.c						\
					srcs/core/next_command.c				\
					srcs/core/input1.c						\
					srcs/core/input2.c						\
					srcs/core/canno.c						\
					srcs/redirect/in.c						\
					srcs/redirect/out.c						\

SRCS_BUILTINS	=	srcs/builtins/env.c						\
					srcs/builtins/export.c					\
					srcs/builtins/export2.c					\
					srcs/builtins/unset.c					\
					srcs/builtins/cd.c						\
					srcs/builtins/cd2.c						\
					srcs/builtins/echo.c					\
					srcs/builtins/echo2.c					\
					srcs/builtins/pwd.c						\
					srcs/builtins/exit.c					\
					srcs/builtins/execve.c					\

SRCS_LEX		=	srcs/lexer_parser/lexing.c				\
					srcs/lexer_parser/lexing2.c				\
					srcs/lexer_parser/parsing.c				\
					srcs/lexer_parser/parsing2.c			\
					srcs/lexer_parser/pipe.c				\
					srcs/lexer_parser/node_to_function.c	\
					srcs/lexer_parser/free_lists.c			\
					srcs/lexer_parser/lst_minishell.c		\
					srcs/lexer_parser/get_env_var.c			\
					srcs/lexer_parser/separator.c			\

INCLUDES		=	-Iincludes								\
					-Ilibft/includes

LD_FLAGS		=	-Llibft -lft -ltermcap

NAME			=	minishell
SRCS			=	$(SRCS_UTILS) $(SRCS_LEX) $(SRCS_BUILTINS)



OBJS			=	$(SRCS:.c=.o)
CC				=	clang
RM				=	@rm -f

LIBFT			=	libft/libft.a

FLAGS			=	-Wall -Werror -Wextra $(INCLUDES) -fsanitize=address -g

.c.o:
					@$(CC) -c $< -o $(<:.c=.o) $(FLAGS)

$(NAME):			clear_screen $(LIBFT) start_message $(OBJS)
					@if [ "$?" = "clear_screen start_message" ]; then echo -n "\033[1A\033[30C\033[0;33mAlready done\033[15D\033[1B\033[1A\033[2D\033[1;32m✓\033[26D\033[1B\033[0m";else echo -n "\033[1A\033[25C\033[1;32m✓\033[26D\033[1B\033[0m"; fi
					@$(CC) $(OBJS) $(FLAGS) -o $(NAME) $(LD_FLAGS)

$(LIBFT):
					@make -s -C libft -f Makefile


all:				$(NAME)

bonus:				re

clear_screen:
					@clear

clean:
					@clear
					@make -s -C libft -f Makefile clean
					@echo "\033[0;33mCleaning \033[1;31m$(NAME)\033[0;33m's objects\033[0m"
					$(RM) $(OBJS)

fclean:				clean
					@make -s -C libft -f Makefile fclean
					@echo "\033[0;33mRemoving \033[1;31m$(NAME)\033[0;33m.\033[0m"
					$(RM) $(NAME)

start_message:
					@echo "\033[0;33mMaking \033[1;31m$(NAME)\033[0;33m\t\033[1;30m[\033[1;31mX\033[1;30m]\033[0m"

re:					fclean $(LIBFT) start_message $(OBJS)
					@if [ "$?" = "fclean start_message" ]; then echo -n "\033[1A\033[30C\033[0;33mAlready done\033[15D\033[1B\033[1A\033[2D\033[1;32m✓\033[26D\033[1B\033[0m";else echo -n "\033[1A\033[25C\033[1;32m✓\033[26D\033[1B\033[0m"; fi
					@$(CC) $(OBJS) $(FLAGS) -o $(NAME) $(LD_FLAGS)

.PHONY:				all clean fclean re