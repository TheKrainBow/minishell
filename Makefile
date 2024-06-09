SRCS_UTILS		=	main.c									\
					signal.c								\
					pipe.c									\
					redirections.c							\

SRCS_PARSING	=	parsing.c								\
					memory.c								\
					lst.c									\
					env_expand.c							\
					lexer/lexer.c							\
					lexer/quote.c							\
					lexer/token.c							\

SRCS_BULTINS	=	cd.c									\
					echo.c									\
					env.c									\
					exit.c									\
					export.c								\
					pwd.c									\
					unset.c									\
					execve.c								\
					bul_utils.c 							\
					export_utils.c							\

ALL_SRCS		=	$(addprefix parsing/, $(SRCS_PARSING)) $(addprefix utils/, $(SRCS_UTILS)) $(addprefix builtins/, $(SRCS_BULTINS))

INCLUDES		=	-Iincludes								\
					-Ilibft/includes

LD_FLAGS		=	-Llibft -lft -ltermcap -lreadline

NAME			=	minishell
OBJS			=	$(addprefix srcs/, $(ALL_SRCS:.c=.o))

NB_OF_FILES	=	0
FIRST_CALL	=	0
I			=	0
TMP			=	0
TMP2		=	20

CC				=	cc
RM				=	@rm -f

LIBFT			=	libft/libft.a

FLAGS			=	-Wall -Werror -Wextra $(INCLUDES) -g -fsanitize=address

.c.o:
				$(eval I=$(shell echo $$(($(I)+1))))
				@if [ "$(FIRST_CALL)" -eq "1" ]; then\
					printf "\033[1A\033[2K";\
					printf "\033[1A\033[2K";\
					printf "\033[1A\033[2K";\
				fi
				@$(eval FIRST_CALL=$(shell echo 1))
				@if [ "$(I)" -eq "$(NB_OF_FILES)" ]; then\
					printf "╭─ %s ────────╮\n" $(NAME);\
					printf "│\033[0;32m████████████████████\033[0m│ %2d/%d compiled!\n" $(I) $(NB_OF_FILES);\
					printf "╰────────────────────╯\n";\
				else\
					printf "╭─ %s ────────╮\n" $(NAME);\
					printf "│\033[0;32m%.*s%*c\033[0m│ %2d/%d %s\n" $(TMP) "████████████████████" $(TMP2) ' ' $(I) $(NB_OF_FILES) $<;\
					printf "╰────────────────────╯\n";\
				fi
				@$(CC) -c $< -o $(<:.c=.o) $(FLAGS)
				$(eval TMP=$(shell echo $$(($(I) * 20 / $(NB_OF_FILES) * 3))))
				$(eval TMP2=$(shell echo $$((20 - $(TMP) / 3))))

$(NAME):			$(LIBFT) init $(OBJS)
					@$(CC) $(OBJS) $(FLAGS) -o $(NAME) $(LD_FLAGS)

init:
				$(eval I=$(shell echo $$(find -name "*.o" | grep srcs | wc -l)))
				$(eval NB_OF_FILES=$(shell echo $$(find -name "*.c" | grep srcs | wc -l)))

all:				$(NAME) norme

$(LIBFT):
					@make -s -C libft -f Makefile


bonus:				re

clean:
					@make -s -C libft -f Makefile clean
					$(RM) $(OBJS)

fclean:				clean
					@make -s -C libft -f Makefile fclean
					$(RM) $(NAME)

re:					fclean all
					@$(CC) $(OBJS) $(FLAGS) -o $(NAME) $(LD_FLAGS)

norme:
					@echo "\033[0;33mChecking \033[1;31mnorminette\033[0;33m\t\033[1;30m[\033[1;31mX\033[1;30m]\033[0m"
					@if norminette > norm.tmp; then\
						echo -n "\033[1A\033[25C\033[1;32m✓\033[26D\033[1B\033[0m";\
					else\
						cat norm.tmp | grep Error;\
					fi;
					@rm norm.tmp

.PHONY:				all clean fclean re