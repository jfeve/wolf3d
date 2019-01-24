# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: jfeve <marvin@le-101.fr>                   +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/01/18 21:26:38 by jfeve        #+#   ##    ##    #+#        #
#    Updated: 2018/12/18 18:54:10 by jfeve       ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

#******************************************************************************#
#-----------------------------------GCC----------------------------------------#
#******************************************************************************#

CC = gcc
CC_FLAGS = -Wall -Wextra -Werror -O2
SDL_FLAGS = -framework SDL2

#******************************************************************************#
#----------------------------------LIBFT---------------------------------------#
#******************************************************************************#

NAME_LIB = libft.a
PATH_LIB = ./libft/

#******************************************************************************#
#-----------------------------------WOLF----------------------------------------#
#******************************************************************************#

NAME = wolf3d
PATH_SRC_WOLF = ./src/
PATH_OBJ_WOLF = ./obj/
PATH_INC_WOLF = ./incs/
FILES_WOLF = $(shell ls src | cut -d "." -f 1)
OBJ_WOLF = $(addprefix $(PATH_OBJ_WOLF), $(addsuffix .o, $(FILES_WOLF)))
SRC_WOLF = $(addprefix $(PATH_SRC_WOLF), $(addsuffix .c, $(FILES_WOLF)))
INC_WOLF = $(addprefix $(PATH_INC_WOLF), wolf3d.h)

#******************************************************************************#
#----------------------------------RULES---------------------------------------#
#******************************************************************************#

#.PHONY = all re

all: $(NAME)

$(NAME): $(PATH_LIB)$(NAME_LIB) $(PATH_OBJ_WOLF) $(OBJ_WOLF)
	@$(CC) $(CC_FLAGS) $(SDL_FLAGS) $(OBJ_WOLF) $(PATH_LIB)$(NAME_LIB)\
		-o $(NAME)
	@echo "*******\nexecutable wolf3d cree.\n*******\n"

$(PATH_OBJ_WOLF):
	@mkdir $(PATH_OBJ_WOLF)
	@echo "*******\ndossier objet cree\n*******\n"

$(PATH_OBJ_WOLF)%.o: $(PATH_SRC_WOLF)%.c $(INC_WOLF)
	@$(CC) $(CC_FLAGS) -o $@ -c $< -I $(PATH_INC_WOLF)

$(PATH_LIB)$(NAME_LIB):
	@make -C $(PATH_LIB)
	@echo "*******\nlibft.a cree\n*******\n"

re: fclean all

re_wolf3d: fclean_wolf3d all

#******************************************************************************#
#----------------------------------CLEAN---------------------------------------#
#******************************************************************************#

#.PHONY = clean clean_lib clean_wolf3d clean_mlx

clean_wolf3d:
	@rm -f $(OBJ_WOLF)
	@rm -rf obj
	@echo "*******\nfichiers objet de wolf3d supprimes\n*******\n"

clean_lib :
	@make -C $(PATH_LIB) clean
	@echo "*******\nfichiers objet de la lib supprimes\n*******\n"

clean: clean_lib clean_wolf3d
	@echo "******\ntous les fichiers objets supprimes\n*******\n"

#******************************************************************************#
#---------------------------------FCLEAN---------------------------------------#
#******************************************************************************#


fclean_wolf3d: clean_wolf3d
	@rm -f $(NAME)
	@echo "*******\nexecutable wolf3d supprime\n*******\n"

fclean_lib: clean_lib
	@make -C $(PATH_LIB) fclean
	@echo "*******\nexecutable lib supprime\n*******\n"

fclean : fclean_lib fclean_wolf3d clean
	@echo "*******\ntout executable supprime\n*******\n"
