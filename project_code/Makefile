# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/16 21:09:20 by ayassin           #+#    #+#              #
#    Updated: 2022/12/21 16:31:20 by ayassin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minirt

HEADER = miniRT.h

CFLAGS =  -Wall -Wextra

OBJDIR=obj

SRC = miniRT.c setup_display.c key_hooks.c dummy_functions.c basic_raytracing.c\
		error_handling/file_error.c\
		parsing/read_file.c parsing/mem_clean.c \
		parsing/cmd_smasher.c parsing/classify_cmd.c parsing/smash_newline.c


OBJSUBDIRS = parsing error_handling

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