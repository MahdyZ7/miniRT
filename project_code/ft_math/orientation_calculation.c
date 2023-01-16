/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orientation_calculation.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 21:20:49 by ahsalem           #+#    #+#             */
/*   Updated: 2023/01/16 04:22:50 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	init_rototion_angels(t_scene *scene)
{
	scene->camera.xyz_angles.x = acosf(scene->camera.orientation.y) - M_PI_2;
	scene->camera.xyz_angles.y = atan2f(scene->camera.orientation.x,
			scene->camera.orientation.z);
	scene->camera.xyz_angles.z = 0;
	fill_single_vector(&scene->camera.sin_theta,
		sin(scene->camera.xyz_angles.x),
		sin(scene->camera.xyz_angles.y),
		sin(scene->camera.xyz_angles.z));
	fill_single_vector(&scene->camera.cos_theta,
		cos(scene->camera.xyz_angles.x),
		cos(scene->camera.xyz_angles.y),
		cos(scene->camera.xyz_angles.z));
}

t_vec	dir_with_camera_orientation(t_vec *dir, t_scene *scene)
{
	t_vec	result;

	normalize(dir);
	rotate_around_z(dir, dir, scene);
	rotate_around_x(dir, dir, scene);
	rotate_around_y(dir, dir, scene);
	normalize(dir);
	result = *dir;
	return (result);
}

void	rotate_around_x(t_vec *result, t_vec *dir, t_scene *scene)
{
	t_vec	tmp;

	vec_init(&tmp, dir->x, dir->y, dir->z);
	result->y = tmp.y * scene->camera.cos_theta.x
		- tmp.z * scene->camera.sin_theta.x;
	result->z = tmp.y * scene->camera.sin_theta.x
		+ tmp.z * scene->camera.cos_theta.x;
}

void	rotate_around_y(t_vec *result, t_vec *dir, t_scene *scene)
{
	t_vec	tmp;

	vec_init(&tmp, dir->x, dir->y, dir->z);
	result->x = tmp.x * scene->camera.cos_theta.y
		+ tmp.z * scene->camera.sin_theta.y;
	result->z = -1 * tmp.x * scene->camera.sin_theta.y
		+ tmp.z * scene->camera.cos_theta.y;
}

void	rotate_around_z(t_vec *result, t_vec *dir, t_scene *scene)
{
	t_vec	tmp;

	vec_init(&tmp, dir->x, dir->y, dir->z);
	result->x = tmp.x * scene->camera.cos_theta.z
		- tmp.y * scene->camera.sin_theta.z;
	result->y = tmp.x * scene->camera.sin_theta.z
		+ tmp.y * scene->camera.cos_theta.z;
}

// void init_rototion_angels(t_scene *scene)
// {
// 	t_vec	ref;

// 	fill_single_vector(&ref, 1, 0, 0);
// 	normalize(&scene->camera.orientation);
// 	scene->camera.xyz_angles.x = 
//find_rotation_angle(scene->camera.orientation, ref) - 1.57;
// 	fill_single_vector(&ref, 0, 1, 0);
// 	scene->camera.xyz_angles.y 
//= find_rotation_angle(scene->camera.orientation, ref) - 1.57;
// 	fill_single_vector(&ref, 0, 0, 1);
// 	scene->camera.xyz_angles.z 
//= find_rotation_angle(scene->camera.orientation, ref) * 0;
// }
