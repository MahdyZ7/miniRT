/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orientation_calculation.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 21:20:49 by ahsalem           #+#    #+#             */
/*   Updated: 2023/01/14 16:51:46 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

float	find_rotation_angle(t_vec a, t_vec b)
{
	float	dot;
	float	norm_a;
	float	norm_b;
	float	theta;

	dot = vec_dot(&a, &b);
	norm_a = sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
	norm_b = sqrt(b.x * b.x + b.y * b.y + b.z * b.z);
	theta = acos(dot / (norm_a * norm_b));
	return (theta);
}

t_vec	dir_with_camera_orientation(t_vec *dir, t_scene *scene)
{
	t_vec	result;

	normalize(dir);
	rotate_around_z(dir, dir, scene->camera.xyz_angles.z);
	rotate_around_x(dir, dir, scene->camera.xyz_angles.x);
	rotate_around_y(dir, dir, scene->camera.xyz_angles.y);
	normalize(dir);
	result = *dir;
	return (result);
}

void	rotate_around_x(t_vec *result, t_vec *dir, float theta_x)
{
	result->y = dir->y * cos(theta_x) - dir->z * sin(theta_x);
	result->z = dir->y * sin(theta_x) + dir->z * cos(theta_x);
}

void	rotate_around_y(t_vec *result, t_vec *dir, float theta_y)
{
	result->x = dir->x * cos(theta_y) + dir->z * sin(theta_y);
	result->z = -1 * dir->x * sin(theta_y) + dir->z * cos(theta_y);
}

void	rotate_around_z(t_vec *result, t_vec *dir, float theta_z)
{
	result->x = dir->x * cos(theta_z) - dir->y * sin(theta_z);
	result->y = dir->x * sin(theta_z) + dir->y * cos(theta_z);
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
