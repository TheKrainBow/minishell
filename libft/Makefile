SRCS_CHAR	=	char/ft_isalnum.c						\
				char/ft_isalpha.c						\
				char/ft_isascii.c						\
				char/ft_isdigit.c						\
				char/ft_isprint.c						\
				char/ft_tolower.c						\
				char/ft_toupper.c

SRCS_GNL	=	get_next_line/get_next_line.c			\
				get_next_line/get_next_line_utils.c

SRCS_LST	=	lst/ft_lst_to_tab.c						\
				lst/ft_lstadd_back.c					\
				lst/ft_lstadd_front.c					\
				lst/ft_lstclear.c						\
				lst/ft_lstcpy.c							\
				lst/ft_lstdelone.c						\
				lst/ft_lstiter.c						\
				lst/ft_lstlast.c						\
				lst/ft_lstmap.c							\
				lst/ft_lstnew.c							\
				lst/ft_lstprint.c						\
				lst/ft_lstsize.c

SRCS_MATH	=	math/ft_atoi.c							\
				math/ft_itoa.c							\
				math/ft_max.c							\
				math/ft_min.c

SRCS_MEM	=	mem/ft_bzero.c							\
				mem/ft_calloc.c							\
				mem/ft_free_tab.c						\
				mem/ft_memccpy.c						\
				mem/ft_memchr.c							\
				mem/ft_memcmp.c							\
				mem/ft_memcpy.c							\
				mem/ft_memmove.c						\
				mem/ft_memset.c							\

SRCS_PRINT	=	print/ft_print_tab.c					\
				print/ft_putchar.c						\
				print/ft_putendl.c						\
				print/ft_putnbr.c						\
				print/ft_putstr.c						\

SRCS_STRS	=	strs/ft_split.c							\
				strs/ft_strchr.c						\
				strs/ft_strcmp.c						\
				strs/ft_strdup.c						\
				strs/ft_strjoin.c						\
				strs/ft_strlcat.c						\
				strs/ft_strlcpy.c						\
				strs/ft_strlen.c						\
				strs/ft_strmapi.c						\
				strs/ft_strncmp.c						\
				strs/ft_strndup.c						\
				strs/ft_strnstr.c						\
				strs/ft_strrchr.c						\
				strs/ft_strs_to_tab.c					\
				strs/ft_strtrim.c						\
				strs/ft_substr.c

SRCS		=	$(SRCS_CHAR) $(SRCS_GNL) $(SRCS_LST) $(SRCS_MATH) $(SRCS_MEM) $(SRCS_PRINT) $(SRCS_STRS)

OBJS		=	$(SRCS:.c=.o)

CC			=	clang
RM			=	rm -f
NAME		=	libft.a

FLAGS		=	-Wall -Werror -Wextra -Iincludes

.c.o:
				$(CC) $(FLAGS) -c $< -o $(<:.c=.o)

$(NAME):		$(OBJS)
				@ar rc $(NAME) $(OBJS)
				@ranlib $(NAME)

all:			$(NAME)

clean:
				$(RM) $(OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean all

.PHONY:			all clean fclean re
