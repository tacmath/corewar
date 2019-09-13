# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2019/05/09 12:30:59 by lperron      #+#   ##    ##    #+#        #
#    Updated: 2019/09/12 16:28:37 by lperron     ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

all: libft asm corewar

libft:
	make -C ./libft/

asm:
	make -C ./asm/

corewar:
	make -C ./corewar/

clean: 
	make -C ./libft/ clean
	make -C ./asm/ clean
	make -C ./corewar/ clean

fclean:
	make -C ./libft/ fclean
	make -C ./asm/ fclean
	make -C ./corewar/ fclean

re: fclean all

.PHONY: libft asm corewar
