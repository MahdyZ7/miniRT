/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 02:13:41 by ahsalem           #+#    #+#             */
/*   Updated: 2022/12/27 20:02:15 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	main(int argc, char **argv)
{
	t_scene	scene;
	t_win	win;
	t_img	img;

	if (not_valid_file(argc, argv))
		return (1);
	if (init_scene(argv, &scene, &win))
		return (1);
	vis_scene(&scene);
	clean_scene(scene);
	window_setup(&win, &img, "miniRT");
	sphere_init(&(img.test), 0, 0, 30, 10, 0x00FF00);
	// redraw(&win, win.img, basic_raytracing);
	redraw(&win, win.img, unknown_raytracing);
	// clean_scene(scene);
	mlx_hook(win.win_ptr, 2, 1L << 0, key_hook, &win);
	mlx_hook(win.win_ptr, 17, 0, exit_code, &win);
	mlx_loop(win.mlx_ptr);
	return (0);
}
