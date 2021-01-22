SRCS_GNL	=	srcs/get_next_line.c					\
				srcs/get_next_line_utils.c				

SRCS_UTILS	=	srcs/main.c

SRCS_PARS	=	srcs/parsing.c

INCLUDES	=	-Iincludes								\

SRCS		=	$(SRCS_GNL) $(SRCS_UTILS) $(SRCS_PARS)
OBJS		=	$(SRCS:.c=.o)

CC			=	clang
RM			=	@rm -f
NAME		=	minishell

LD_FLAGS	=	-g -fsanitize=address
FLAGS		=	-Wall -Werror -Wextra $(INCLUDES) -D BUFFER_SIZE=4096 -g

.c.o:
				$(CC) -c $< -o $(<:.c=.o) $(FLAGS)

$(NAME):		start_message $(OBJS)
				@if [ "$?" = "start_message" ]; then echo "\033[0;33mObjects already up to date\033[0;32m"; fi
				@echo "\033[1;32mLinking all objects\033[0;32m"
				$(CC) $(OBJS) $(FLAGS) -o $(NAME) $(LD_FLAGS)
				@echo "\033[1;31mMinishell\033[0m is ready to use!"

all:			$(NAME)

bonus:			re

clean:
				@echo "\033[0;33mCleaning \033[1;31mMinishell\033[0;33m's objects\033[0m"
				$(RM) $(OBJS)

fclean:			clean
				@echo "\033[0;33mRemoving \033[1;31mMinishell\033[0;33m.\033[0m"
				$(RM) $(NAME)

start_message:
				@clear
				@echo "\033[0;31mMaking \033[1;31mMinishell"
				@echo "\033[1;32mCompiling objects\033[0;32m"

re:				fclean all

.PHONY:			all clean fclean re