# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/16 21:09:20 by ayassin           #+#    #+#              #
#    Updated: 2022/12/25 14:21:10 by ahsalem          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minirt

HEADER = miniRT.h

CFLAGS =  -Wall -Wextra -Werror -g

OBJDIR=obj

SRC = miniRT.c setup_display.c key_hooks.c dummy_functions.c basic_raytracing.c\
		error_handling/file_error.c\
		error_handling/elements_error.c  error_handling/shapes_check.c\
		parsing/read_file.c parsing/mem_clean.c parsing/check_element_items.c\
		parsing/line_smasher.c parsing/classify_line.c\
		parsing/check_sphere_cylind_plane.c parsing/coordinate_checking.c\
		parsing/cam_light_check.c parsing/classify_elements.c parsing/element_checking_utils.c\
		parsing/fill_shapes.c parsing/fill_scene.c parsing/fill_elements.c \
		parsing/fill_vector.c\
		testers/visualizers.c testers/visualizers_utils.c testers/test_math.c\
		ft_math/vectors.c ft_math/math_utils.c\


OBJSUBDIRS = parsing error_handling testers ft_math

ifeq ($(shell uname -s), Darwin)
	CFLAGS += -Werror -Imlx
	LINK_MLX = -Lminilibx_macos -lmlx -framework OpenGl -framework APPKit
	MLX_LIB = minilibx_macos
else ifeq ($(shell uname -s), Linux)
	CFLAGS += -Imlx
	LINK_MLX = -Lminilibx_linux -lmlx -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
	MLX_LIB = minilibx_linux
endif

SUBDIRS = libft ft_printf $(MLX_LIB)

CC = gcc

_OBJS = $(SRC:.c=.o)
OBJS = $(addprefix $(OBJDIR)/,$(_OBJS))
# OBJS = $(patsubst %,$(OBJDIR)/%,$(_OBJS))


all: $(NAME)

# $(OBJS)/%.o:%.c
# 	mkdir -p $(OBJDIR)
# 	$(CC) $(CFLAGS) -Ilibft -Ift_printf -c $^ -o $@
# $(ODIR)/%.o : %.c
$(OBJDIR)/%.o : %.c
	mkdir -p $(OBJDIR)
	for dir in $(OBJSUBDIRS); do \
		mkdir -p $(OBJDIR)/$$dir; \
	done
	$(CC) $(CFLAGS) -Ilibft -Ift_printf -c $^ -o $@

$(NAME): $(SUBDIRS) $(OBJS)
	for dir in $(SUBDIRS); do \
        $(MAKE) all -C $$dir; \
    done
	$(CC) $(CFLAGS) $(OBJS) $(LINK_MLX) \
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