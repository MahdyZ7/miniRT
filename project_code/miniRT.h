/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 21:09:01 by ayassin           #+#    #+#             */
/*   Updated: 2022/12/18 12:20:23 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# include "minilibx_macos/mlx.h"
# include "minilibx_linux/mlx.h"
# include "libft/libft.h"
# include "ft_printf/ft_printf.h"
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "structs.h"
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

# ifdef linux
#  define ESC_KEY 65307
// #  define W_KEY 119
// #  define A_KEY 97
// #  define S_KEY 115
// #  define D_KEY 100
// #  define LEFT_KEY 65361
// #  define RIGHT_KEY 65363
// #  define M_KEY 109
// #  define H_KEY 104
// #  define UP_KEY 65362
// #  define DOWN_KEY 65364
// #  define I_KEY 34
# endif

# ifdef __MACH__
#  define ESC_KEY 53
// #  define W_KEY 13
// #  define A_KEY 0
// #  define S_KEY 1
// #  define D_KEY 2
// #  define LEFT_KEY 123
// #  define RIGHT_KEY 124
// #  define UP_KEY 126
// #  define DOWN_KEY 125
// #  define M_KEY 46
// #  define H_KEY 4
// #  define C_KEY 8
// #  define I_KEY 34
# endif

/*------------------Parsing-------------------*/
int		init_scene(
			char **argv, t_scene *scene, t_win *win);
void	clean_scene(t_scene scene);
int		fill_scene(char **argv, t_scene *scene);
t_list	*parsing_map(int fd);
void	init_parsing_kit(
			t_parsing_kit *s, t_list **head, char *line);
/*------------------MLX_RELATED---------------*/
void	pixel_put(t_img *data, int x, int y, int color);
void	redraw(t_win *s, t_img *img, int x_pos, int y_pos);
void	setup_img(t_img *img, t_win *win, int width, int hight);
int		window_setup(t_win *win, t_img *img, char *map_title);
int		exit_code(t_win *win);
int		key_hook(int key, t_win *win);

/*----------------ERRORS-----------------------*/
int		not_valid_file(int argc, char **argv);
int		bad_file(char **argv);
int		parse_error_message(void);

/*------------------DUMMY---------------------*/
void	put_ellipse(t_img *img, int width, int hight);
void	put_serpenski(t_img *img, int width, int hight);
void	put_ellipse2(t_img *img, int x, int y);
void	put_border(t_img *img);

#endif