# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/16 21:09:20 by ayassin           #+#    #+#              #
#    Updated: 2023/01/10 23:09:11 by ayassin          ###   ########.fr        #
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
		parsing/fill_vector.c parsing/checkers_utils.c\
		ft_math/vectors.c ft_math/math_utils.c ft_math/equations.c\
		ft_math/vectors_utils.c ft_math/orientation_calculation.c\
		testers/visualizers.c testers/visualizers_utils.c testers/test_math.c testers/test_equations.c\
		pre_rendering/screen_colors_init.c \
		trace_objects/plane_tracing.c trace_objects/sphere_tracing.c trace_objects/cylinder_tracing.c\
		trace_objects/lights_and_colors.c\
		trace_objects/trace_plane_utils.c\


OBJSUBDIRS = parsing error_handling testers ft_math pre_rendering trace_objects

ifeq ($(shell uname -s), Darwin)
	CFLAGS += -Werror -Imlx
	LINK_MLX = -Lminilibx_macos -lmlx -framework OpenGl -framework APPKit
	MLX_LIB = minilibx_macos
else ifeq ($(shell uname -s), Linux)
	CFLAGS += -Imlx
	LINK_MLX = -Lminilibx_linux -lmlx -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
	MLX_LIB = minilibx_linux
endif

SUBDIRS = libft $(MLX_LIB)

CC = gcc

_OBJS = $(SRC:.c=.o)
OBJS = $(addprefix $(OBJDIR)/,$(_OBJS))
# OBJS = $(patsubst %,$(OBJDIR)/%,$(_OBJS))


all: $(NAME)

# $(OBJS)/%.o:%.c
# 	mkdir -p $(OBJDIR)
# 	$(CC) $(CFLAGS) -Ilibft  -c $^ -o $@
# $(ODIR)/%.o : %.c
$(OBJDIR)/%.o : %.c
	if [ ! -d $(OBJDIR)]; then \
		mkdir -p $(OBJDIR); \
	fi;
	for dir in $(OBJSUBDIRS); do \
		if [ ! -d $(OBJDIR)/$$dir ]; then \
			mkdir -p $(OBJDIR)/$$dir; \
		fi; \
	done
	$(CC) $(CFLAGS) -Ilibft  -c $^ -o $@

$(NAME): $(SUBDIRS) $(OBJS)
	for dir in $(SUBDIRS); do \
        $(MAKE) all -C $$dir; \
    done
	$(CC) $(CFLAGS) $(OBJS) $(LINK_MLX) \
		-Llibft -lft -o $(NAME)

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