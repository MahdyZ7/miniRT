/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 21:09:01 by ayassin           #+#    #+#             */
/*   Updated: 2022/12/17 12:13:35 by ayassin          ###   ########.fr       */
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

struct	s_img;
struct	s_win;

// hold image related information
typedef struct s_img
{
	void			*img_ptr;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				width;
	int				hight;
	int				zoom;
	int				x_pos;
	int				y_pos;
	struct s_win	*win;	
}				t_img;

// hold window info and key information
typedef struct s_win
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	*img;
}				t_win;

//miniRT.c

// key_hooks.c
int		exit_code(t_win *win);
int		key_hook(int key, t_win *win);

// display_setup.c
void	pixel_put(t_img *data, int x, int y, int color);
void	redraw(t_win *s, t_img *img, int x_pos, int y_pos);
void	img_setup(t_img *img, t_win *win, int width, int hight);
int		window_setup(t_win *win, t_img *img, char *map_title);

// dummy_functions.c
void	put_ellipse(t_img *img, int width, int hight);
void	put_serpenski(t_img *img, int width, int hight);
void	put_ellipse2(t_img *img, int x, int y);
void	put_border(t_img *img);


#endif