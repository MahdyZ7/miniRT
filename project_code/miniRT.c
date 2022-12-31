/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 02:13:41 by ahsalem           #+#    #+#             */
/*   Updated: 2022/12/31 09:17:31 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	main(int argc, char **argv)
{
	// t_scene	scene;
	t_win	win;
	t_img	img;

	if (not_valid_file(argc, argv))
		return (1);
	if (init_scene(argv, &scene, &win))
		return (1);
	vis_scene(&scene);
	window_setup(&win, &img, "miniRT");
	sphere_init(&(img.test), 0, 0, 30, 10, 0x00FF00);
	img.scene = &scene;
	// redraw(&win, win.img, basic_raytracing);
	redraw(&win, win.img, basic_raytracing);
	mlx_hook(win.win_ptr, 2, 1L << 0, key_hook, &win);
	mlx_hook(win.win_ptr, 17, 0, exit_code, &win);
	mlx_loop(win.mlx_ptr);
	clean_scene(scene);
	return (0);
}
