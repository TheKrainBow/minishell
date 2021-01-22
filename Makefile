SRCS_GNL	=	srcs/get_next_line.c					\
				srcs/get_next_line_utils.c				

SRCS_UTILS	=	srcs/main.c

SRCS_PARS	=	srcs/parsing.c							\
				srcs/lexing.c

INCLUDES	=	-Iincludes								\
				-Ilibft

SRCS		=	$(SRCS_GNL) $(SRCS_UTILS) $(SRCS_PARS)
OBJS		=	$(SRCS:.c=.o)

CC			=	clang
RM			=	@rm -f
NAME		=	minishell

LIBFT		=	libft/libft.a

LD_FLAGS	=	-g -Llibft -lft
FLAGS		=	-Wall -Werror -Wextra $(INCLUDES) -D BUFFER_SIZE=4096 -g

.c.o:
				$(CC) -c $< -o $(<:.c=.o) $(FLAGS)
				@echo -n "\033[1A\033[30C\033[0K"

$(NAME):		start_message $(LIBFT) $(OBJS)
				@if [ "$?" = "start_message" ]; then echo "\033[0;33mAlready done\033[17D\033[1;32m✓\033[1A\033[1D✓\033[1B";else echo "\033[5D\033[1;32m✓"; fi
				@echo -n "\033[33C"
				@$(CC) $(OBJS) $(FLAGS) -o $(NAME) $(LD_FLAGS)
				@echo "\033[27C\033[0K\033[35D\033[1;32m✓\033[3A\033[1D✓\033[3B"

$(LIBFT):		
				@make -s -C libft -f Makefile
				@echo -n "\033[1A\033[5D\033[1;32m✓\033[4C\033[1B"


all:			$(NAME)

bonus:			re

clean:
				@clear
				@echo "\033[0;33mCleaning \033[1;31mLibft\033[0;33m.\033[0m"
				@make -s -C libft -f Makefile clean
				@echo "\033[0;33mCleaning \033[1;31mMinishell\033[0;33m's objects\033[0m"
				$(RM) $(OBJS)

fclean:			clean
				@make -s -C libft -f Makefile fclean
				@echo "\033[0;33mRemoving \033[1;31mMinishell\033[0;33m.\033[0m"
				$(RM) $(NAME)

start_message:
				@echo "\033[0;33mMaking \033[1;31mMinishell\033[0;33m\t\033[1;30m[\033[1;31mX\033[1;30m]"
				@echo "\033[1;32mCompiling libft\t\t\033[1;30m[\033[1;31mX\033[1;30m]\t\033[0;32m"
				@echo "\033[1;32mCompiling objects\t\033[1;30m[\033[1;31mX\033[1;30m]\t\033[0;32m"
				@echo "\033[1;32mLinking all objects\t\033[1;30m[\033[1;31mX\033[1;30m]\033[0;32m"
				@echo -n "\033[2A\033[30C"

re:				fclean all

.PHONY:			all clean fclean re