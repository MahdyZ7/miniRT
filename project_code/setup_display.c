/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_display.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 10:38:06 by ayassin           #+#    #+#             */
/*   Updated: 2023/01/17 13:31:59 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*Places a 'color' in the image 'data' in the x and y posityion
(put pixel clone)*/
void	pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	if (x >= data->width || y >= data->hight || y < 0 || x < 0)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

/*oriant planes so that the normal of planes is looking in the correct
position for light to hit it*/
static void	orint_planes(t_scene *scene)
{
	int		i;
	t_vec	tmp;
	t_plane	*plane;

	i = 0;
	plane = scene->plane;
	while (i < scene->n_planes)
	{
		tmp = vec_sub(&scene->camera.view_point, &plane[i].pos);
		if (vec_dot(&tmp, &plane[i].orientation) >= 0)
			plane[i].orientation = vec_scalar_mult(&plane[i].orientation, -1);
		++i;
	}
}

/* Destroy the imgae and then palce a new ceated image on the window.
Used to update the image on the window for any change that occures*/
void	redraw(t_win *s, t_img *img, void (*draw)(t_img *))
{
	orint_planes(img->scene);
	draw(img);
	mlx_clear_window(s->mlx_ptr, s->win_ptr);
	mlx_put_image_to_window(s->mlx_ptr, s->win_ptr, img->img_ptr, 0, 0);
}

/* setup the defulats for variables in the t_img struct and t_nums struct*/
void	setup_img(t_img *img, t_win *win, int width, int hight)
{
	img->width = width;
	img->hight = hight;
	img->img_ptr = mlx_new_image(win->mlx_ptr, img->width, img->hight);
	if (!img->img_ptr)
		exit_code(win);
	img->addr = mlx_get_data_addr(img->img_ptr, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	if (!img->addr)
		exit_code(win);
	img->x_pos = 0;
	img->y_pos = 0;
}

/* Decalre the window and image, and set up hooks  and loops of mls*/
int	window_setup(t_win *win, t_img *img, char *map_title)
{
	int		width;
	int		hight;

	width = WIN_WIDTH;
	hight = WIN_HIGHT;
	win->img = img;
	win->img->img_ptr = NULL;
	win->mlx_ptr = mlx_init();
	if (!win->mlx_ptr)
		exit_code(win);
	if (ft_strchr(map_title, '/'))
		map_title = ft_strrchr(map_title, '/') + 1;
	win->win_ptr = mlx_new_window(win->mlx_ptr, width, hight, map_title);
	if (!win->win_ptr)
		exit_code(win);
	setup_img(win->img, win, width, hight);
	return (0);
}
