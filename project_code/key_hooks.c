/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 10:49:02 by ayassin           #+#    #+#             */
/*   Updated: 2022/12/17 12:13:14 by ayassin          ###   ########.fr       */
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
	if (key == ESC_KEY)
		exit_code(win);
	return (0);
}