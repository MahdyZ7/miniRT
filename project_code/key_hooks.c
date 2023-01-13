/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 10:49:02 by ayassin           #+#    #+#             */
/*   Updated: 2023/01/11 19:45:01 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* free any malloced data and exit the program*/
int	exit_code(t_win *win)
{
	if (!win)
		exit(0);
	if (win->img)
	{
		if (win->img->scene)
			clean_scene(*(win->img->scene));
		if (win->img->img_ptr)
			mlx_destroy_image(win->mlx_ptr, win->img->img_ptr);
	}
	if (win->mlx_ptr && win->win_ptr)
		mlx_destroy_window(win->mlx_ptr, win->win_ptr);
	exit(0);
	return (0);
}

/*switch function for keys*/
int	key_hook(int key, t_win *win)
{
if (key == DOWN_KEY)
		win->img->scene->camera.orientation.y += 0.05;
	if (key == UP_KEY)
		win->img->scene->camera.orientation.y -= 0.05;
	if (key == RIGHT_KEY)
		win->img->scene->camera.orientation.x += 0.05;
	if (key == LEFT_KEY)
		win->img->scene->camera.orientation.x  -= 0.05;

	if (key == M_KEY)
		win->img->scene->camera.orientation.z += 0.05;
	if (key == H_KEY)
		win->img->scene->camera.orientation.z -= 0.05;
	
	if (key == Q_KEY)
		win->img->scene->camera.view_point.z += 5;	
	if (key == E_KEY)
		win->img->scene->camera.view_point.z -= 5;

	if (key == W_KEY)
		win->img->scene->camera.view_point.y += 5;
	if (key == S_KEY)
		win->img->scene->camera.view_point.y -= 5;

	if (key == A_KEY)
		win->img->scene->camera.view_point.x -= 5;
	if (key == D_KEY)
		win->img->scene->camera.view_point.x += 5;
	if (key == ESC_KEY)
		exit_code(win);
	printf("Key = %d\n", key);
	vis_scene(win->img->scene);
	redraw(win, win->img, basic_raytracing);
	return (0);
}
