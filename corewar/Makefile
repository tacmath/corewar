# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: krambono <marvin@le-101.fr>                +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/11/09 13:02:16 by krambono     #+#   ##    ##    #+#        #
#    Updated: 2019/09/17 13:26:22 by mtaquet     ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

# EXECUTABLE
NAME =	corewar

# SOURCES
VISUFILES = end.c event.c print_log.c info.c init.c music.c pause.c print.c resize.c utils.c intro.c init_cycle.c init_text.c load_image.c resize_image.c utils2.c print_info.c print_instr.c print_process1.c print_process2.c highlight.c print_jauge.c info_instr.c info_process.c print_memory.c
SRCFILES = error.c explorer.c get_instr_info.c globals.c instr_addsub.c instr_aff.c instr_args.c instr_fork.c instr_ld.c instr_ldi.c instr_live.c instr_logical.c instr_st.c instr_sti.c instr_utils.c instr_utils2.c instr_verbose.c instr_zjmp.c main.c op.c options.c options2.c parser.c process_list.c ret_instr.c utils.c utils2.c verbose.c vm.c vm2.c vm3.c check_cor.c $(addprefix visu/, $(VISUFILES))
SRC = $(addprefix srcs/, $(SRCFILES))

# HEADERS
HEADERSFILES = corewar.h op.h errors.h
HEADERS = $(addprefix includes/, $(HEADERSFILES))

# OBJETS
OBJ= $(SRC:.c=.o)

# COMPILATEUR
CC =		gcc
CFLAGS =	-Wall -Wextra -Werror
SDLFLAGS = $(shell sdl2-config --libs) -lSDL2_ttf -lSDL2_image -lSDL2_mixer -O3

# LIBS
libft =		../libft/

# REGLES
all: libs $(NAME)

$(NAME): $(OBJ) $(libft)
	@printf "\033[2K\r\033[36m>>Linking...\033[0m"
	@$(CC) -o $@ $(OBJ) -I /usr/includes/SDL2 -I includes -I ../libft/includes $(SDLFLAGS) -L ../libft/ -lft

	@echo "\t\033[32m[OK]\033[0m"
	@echo "\033[31m...COREWAR\033[0m"

%.o: %.c $(HEADERS)
	@printf "\033[2K\r\033[36m>>Compiling \033[37m$<\033[36m \033[0m"
	@$(CC) $(CFLAGS) -o $@ -c $< -I includes/SDL_include -I includes -I ../libft/includes

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

re:		fclean all
