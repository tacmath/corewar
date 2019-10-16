# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: krambono <marvin@le-101.fr>                +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/11/09 13:02:16 by krambono     #+#   ##    ##    #+#        #
#    Updated: 2019/09/29 14:34:00 by mtaquet     ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

SHELL = zsh

# EXECUTABLE
NAME =	asm

# SOURCES
SRCFILES = compile.c asm_label.c checks.c command.c encode_arg.c header.c label.c main.c op.c utils.c utils2.c valid_arg.c write_champ.c get_str.c
SRC = $(addprefix srcs/, $(SRCFILES))

# HEADERS
HEADERSFILES = asm.h op.h
HEADERS = $(addprefix includes/, $(HEADERSFILES))

# OBJETS
OBJ= $(SRC:.c=.o)

# COMPILATEUR
CC =		gcc
CFLAGS =	-Wall -Wextra -Werror

# LIBS
libft =		../libft/

# REGLES
all: libs $(NAME)

$(NAME): $(OBJ) $(libft)
	@printf "\033[2K\r\033[36m>>Linking...\033[0m\c"
	@$(CC) -o $@ $(OBJ) -I includes ../libft/libft.a
	@cp $(NAME) $(addprefix script/bin/, $(NAME))
	@echo "\t\033[32m[OK]\033[0m"
	@echo "\033[31m...ASM\033[0m"

%.o: %.c $(HEADERS)
	@printf "\033[2K\r\033[36m>>Compiling \033[37m$<\033[36m \033[0m"
	@$(CC) $(CFLAGS) -o $@ -c $< -I includes

.PHONY: clean fclean re libs

libs:
	@make -s -C $(libft)

clean:
	@make -s -C $(libft) clean
	@echo "\033[31mCleaning .o\033[0m"
	@rm -f $(OBJ)

fclean:	clean
	@make -s -C $(libft) fclean
	@echo "\033[31mCleaning $(NAME)\033[0m"
	@rm -f $(NAME)
	@rm -f $(addprefix script/bin/, $(NAME))

re:		fclean all
