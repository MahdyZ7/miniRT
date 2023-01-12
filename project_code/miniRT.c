/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 02:13:41 by ahsalem           #+#    #+#             */
/*   Updated: 2023/01/12 12:15:12 by ahsalem          ###   ########.fr       */
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
	{
		clean_scene(scene);
		return (1);
	}
	window_setup(&win, &img, "miniRT");
	img.scene = &scene;
	redraw(&win, win.img, basic_raytracing);
	mlx_hook(win.win_ptr, 2, 1L << 0, key_hook, &win);
	mlx_hook(win.win_ptr, 17, 0, exit_code, &win);
	mlx_loop(win.mlx_ptr);
	clean_scene(scene);
	return (0);
}

/*
	refrence:
	For spheres, camera orientation, light, and shadows:
	https://gabrielgambetta.com/computer-graphics-from-scratch/
	For Cylinder:
	https://iquilezles.org/articles/intersectors/
	// http://www.illusioncatalyst.com/notes_files/mathematics/line_cylinder_intersection.php
*/