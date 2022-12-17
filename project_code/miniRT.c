/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 21:08:55 by ayassin           #+#    #+#             */
/*   Updated: 2022/12/17 18:13:09 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	main(int argc, char **argv)
{
	t_win	win;
	t_img	img;

	// read map
	if (not_valid_file(argc, argv))
		return (1);
	window_setup(&win, &img, "miniRT");
	// put prossing comand inside redraw;
	redraw(&win, win.img, win.img->x_pos, win.img->y_pos);
	mlx_hook(win.win_ptr, 2, 1L << 0, key_hook, &win);
	mlx_hook(win.win_ptr, 17, 0, exit_code, &win);
	mlx_loop(win.mlx_ptr);
	return (0);
}