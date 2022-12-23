# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/16 21:09:20 by ayassin           #+#    #+#              #
#    Updated: 2022/12/21 23:21:06 by ahsalem          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minirt

HEADER = miniRT.h

CFLAGS = -Werror -Wall -Wextra

SRC = miniRT.c setup_display.c key_hooks.c dummy_functions.c\
		error_handling/file_error.c\
		error_handling/elements_error.c\
		parsing/read_file.c parsing/mem_clean.c parsing/check_element_items.c\
		parsing/line_smasher.c parsing/classify_line.c\
		 parsing/cam_light_check.c parsing/classify_elements.c parsing/element_checking_utils.c\
		testers/visualizers.c\

OBJDIR=obj

ifeq ($(shell uname -s), Darwin)
	CFLAGS += -Imlx
	LINK_MLX = -Lminilibx_macos -lmlx -framework OpenGl -framework APPKit
	MLX_LIB = minilibx_macos
else ifeq ($(shell uname -s), Linux)
	CFLAGS += -Imlx
	LINK_MLX = -Lminilibx_linux -lmlx -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
	MLX_LIB = minilibx_linux
endif

SUBDIRS = libft ft_printf $(MLX_LIB)

CC = gcc

OBJS = $(SRC:.c=.o)
# OBJS = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))

all: $(NAME)

.c.o:
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -Ilibft -Ift_printf -c $^ -o $@

$(NAME): $(SUBDIRS) $(OBJS)
	for dir in $(SUBDIRS); do \
        $(MAKE) all -C $$dir; \
    done
	$(CC) $(CFALGS) $(SRC) $(LINK_MLX) \
		-Lft_printf -lftprintf -Llibft -lft -o $(NAME)

$(SUBDIRS):
	for dir in $(SUBDIRS); do \
        $(MAKE) all -C $$dir; \
    done

clean:
	rm -f $(OBJS)
	for dir in $(SUBDIRS); do \
        $(MAKE) clean -C $$dir; \
    done

fclean: clean
	rm -f $(NAME)
	for dir in $(SUBDIRS); do \
        $(MAKE) fclean -C $$dir; \
    done

re : fclean all

.PHONY: clean fclean all re