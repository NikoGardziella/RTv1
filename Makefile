# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ngardzie <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/24 12:09:35 by ngardzie          #+#    #+#              #
#    Updated: 2022/01/24 12:09:40 by ngardzie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RTv1
N_LFT = libft.a
SDL_TAR = SDL2-2.0.22.tar.gz

D_LFT = ./libft/

SRC_DIR = ./src/
INC_DIR = ./includes/
LFTINC_DIR = ./libft/

SDL_DIR = ./SDL2-2.0.22/
D_SDLINC = $(SDL_DIR)include
SDLLIB_DIR = $(SDL_DIR)lib
OBJ_DIR = ./obj/

L_SDL = `$(SDL_DIR)sdl2-config --cflags --libs`

LFT = $(D_LFT)$(N_LFT)

HEADER_FILES = $(INC_DIR)rtv1.h 
LIBHEAD = $(LFTINC_DIR)libft.h $(LFTINC_DIR)get_next_line.h

C_FILES =	main.c misc.c parser.c libft_vectors.c normals.c intersections.c \
			parse_line.c libft_vectors1.c pixel.c get_t.c

LIBFT_FILES = ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c \
			ft_isdigit.c ft_isprint.c ft_itoa.c ft_lstadd.c ft_lstdel.c \
			ft_lstdelone.c ft_lstiter.c ft_lstnew.c ft_memalloc.c \
			ft_memccpy.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memdel.c \
			ft_memmove.c ft_memset.c ft_putchar.c ft_putchar_fd.c ft_putendl.c \
			ft_putendl_fd.c ft_putnbr.c ft_putnbr_fd.c ft_putstr.c \
			ft_putstr_fd.c ft_strcat.c ft_strchr.c ft_strclr.c ft_strcmp.c \
			ft_strcpy.c ft_strdel.c ft_strdup.c ft_strequ.c ft_striter.c \
			ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlen.c ft_strmap.c \
			ft_strmapi.c ft_strncat.c ft_strncmp.c ft_strncpy.c ft_strnequ.c \
			ft_strnew.c ft_strnstr.c ft_strrchr.c ft_strsplit.c ft_strstr.c \
			ft_strsub.c ft_strtrim.c ft_tolower.c ft_toupper.c \
			 get_next_line.c ft_isascii.c \

SRC = $(addprefix $(SRC_DIR), $(C_FILES))
LFTSRC = $(addprefix $(D_LFT), $(LIBFT_FILES))
OBJ = $(addprefix $(OBJ_DIR), $(C_FILES:.c=.o))

CC = gcc
CFLAGS = -Wall -Werror -Wextra
INC = -I $(INC_DIR) -I $(LFTINC_DIR) -I $(D_SDLINC)

C_RED = \033[31m
C_GREEN = \033[32m
C_NONE = \033[0m

all: $(NAME)

$(NAME): $(SDL_DIR) $(SDLLIB_DIR) $(OBJ_DIR) $(OBJ) $(LFTSRC) $(LIBHEAD)
	@make -C $(D_LFT)
	@printf "RTv1:  %-25s$(C_GREEN)[done]$(C_NONE)\n" "libft.a"
	@$(CC) $(CFLAGS) $(OBJ) $(LFT) $(L_SDL) -o $(NAME)
	@printf "RTv1:  %-25s$(C_GREEN)[done]$(C_NONE)\n" $@

$(N_LFT):
	@make -C $(D_LFT)
	@printf "RTv1:  %-25s$(C_GREEN)[done]$(C_NONE)\n" $@

$(SDL_DIR):
	@tar -xf $(SDL_TAR)
	@printf "RTv1:  %-25s$(C_GREEN)[extracted]$(C_NONE)\n" $@

$(SDLLIB_DIR):
	@mkdir $(SDLLIB_DIR)
	@printf "\n$(C_GREEN)[configuring SDL]$(C_NONE)\n"
	@cd $(SDL_DIR); ./configure --prefix=`pwd`/lib
	@printf "$(C_GREEN)[compiling SDL]$(C_NONE)\n"
	@make -C $(SDL_DIR)
	@make -C $(SDL_DIR) install >/dev/null
	@printf "RTv1:  %-25s$(C_GREEN)[done]$(C_NONE)\n" $@

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)
	@printf "RTv1:  %-25s$(C_GREEN)[done]$(C_NONE)\n" $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER_FILES)
	@$(CC) $(CFLAGS) -c $(INC) $< -o $@
	@printf "RTv1:  %-25s$(C_GREEN)[done]$(C_NONE)\n" $@

clean:
	@rm -rf $(OBJ_DIR)
	@make -C $(D_LFT) clean
	@printf "RTv1:  %-25s$(C_RED)[done]$(C_NONE)\n" $@

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(SDL_DIR)
	@make -C $(D_LFT) fclean
	@printf "RTv1:  %-25s$(C_RED)[done]$(C_NONE)\n" $@

re: fclean all
