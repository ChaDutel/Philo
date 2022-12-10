NAME	:= philo


CC	:= gcc
CFLAGS	:=	-Wall -Wextra -Werror
CSAN	:=	-fsanitize=address -g3

DIR_SRCS	:=	sources
DIR_INCS	:=	includes
DIR_OBJS	:=	.objs

LST_SRCS	:=	main.c parsing.c init.c exec.c state.c
LST_INCS	:=	philo.h
LST_OBJS	:=	$(LST_SRCS:.c=.o)

SRCS	:=	$(addprefix $(DIR_SRCS)/,$(LST_SRCS))
INCS	:=	$(addprefix $(DIR_INCS)/,$(LST_INCS))
OBJS	:=	$(addprefix $(DIR_OBJS)/,$(LST_OBJS))

all	:	$(NAME)

$(NAME)	:	$(OBJS) $(INCS) Makefile
			$(CC) $(CFLAGS) $(INCS) $(OBJS) -o $@

$(DIR_OBJS)/%.o	:	$(DIR_SRCS)/%.c $(INCS) Makefile | $(DIR_OBJS)
					$(CC) $(CFLAGS) $(INCS) -c $< -o $@

$(DIR_OBJS)	:
				mkdir -p $(DIR_OBJS)

clean	:
			rm -rf $(DIR_OBJS)
			$(MAKE) clean -C

fclean	:
			rm -rf $(NAME)
			$(MAKE) fclean -C

re	:
		$(MAKE) fclean
		$(MAKE) all

.PHONY	:	all clean fclean re