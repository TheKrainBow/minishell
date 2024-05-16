SRCS_ALGO	=	srcs/main.c								\

INCLUDES	=	-Iincludes								\


SRCS		=	$(SRCS_ALGO)
OBJS		=	$(SRCS:.c=.o)

CC			=	@cc
RM			=	@rm -f
NAME		=	minishell

LD_FLAGS	=	
FLAGS		=	-Wall -Werror -Wextra $(INCLUDES) -fsanitize=address -g

.c.o:
				@$(CC) -c $< -o $(<:.c=.o) $(FLAGS)

$(NAME):		start_message $(OBJS)
				@if [ "$?" = "start_message" ]; then echo -n "\033[1A\033[30C\033[0;33mAlready done\033[15D\033[1B\033[1A\033[2D\033[1;32m✓\033[26D\033[1B\033[0m";else echo -n "\033[1A\033[25C\033[1;32m✓\033[26D\033[1B\033[0m"; fi
				$(CC) $(LD_FLAGS) $(FLAGS) $(OBJS) -o $(NAME)

all:			$(NAME)

bonus:			re

clean:
				@echo "\033[0;33mCleaning \033[1;31m$(NAME)\033[0;33m's objects\033[0m"
				$(RM) $(OBJS)

fclean:			clean
				@echo "\033[0;33mRemoving \033[1;31m$(NAME)\033[0;33m.\033[0m"
				$(RM) $(NAME)

start_message:
				@echo "\033[0;33mMaking \033[1;31m$(NAME)\033[0;33m\t\033[1;30m[\033[1;31mX\033[1;30m]\033[0m"

re:				fclean $(NAME)
				$(CC) $(LD_FLAGS) $(FLAGS) $(OBJS) -o $(NAME)

.PHONY:			all clean fclean re
