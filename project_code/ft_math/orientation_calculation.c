/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orientation_calculation.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 21:20:49 by ahsalem           #+#    #+#             */
/*   Updated: 2023/01/10 02:25:08 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

float	find_rotation_angle(t_vec *a, t_vec *b)
{
	float	dot;
	float	norm_a;
	float	norm_b;
	float	theta;

	dot = vec_dot(a, b);
	norm_a = sqrt(a->x * a->x + a->y * a->y + a->z * a->z);
	norm_b = sqrt(b->x * b->x + b->y * b->y + b->z * b->z);
	theta = acos(dot / (norm_a * norm_b));
	return (theta);
}

t_vec	dir_with_camera_orientation(t_vec *dir,t_scene *scene)
{
	float	theta;
	t_vec	refrence;
	t_vec	result;
	fill_single_vector(&refrence, 0, 0, 1);
	theta = find_rotation_angle(dir, &refrence);
	theta = find_rotation_angle(&scene->camera.orientation, &refrence);
	
	result = find_rotation_matrix(dir, scene);
	return (result);
}

t_vec	find_rotation_matrix( t_vec *dir,t_scene *scene)
{
	t_vec	result;

	rotate_around_z(dir, dir, scene->camera.xyz_angles.z);
	rotate_around_x(dir, dir, scene->camera.xyz_angles.x);
	rotate_around_y(dir, dir, scene->camera.xyz_angles.y);
	result = *dir;
	return (result);
}

void	rotate_around_x(t_vec *result, t_vec *dir, float theta_x)
{
	// (void)result->x = dir->x;
	result->y = dir->y * cos(theta_x) - dir->z *sin(theta_x);
	result->z = dir->y * sin(theta_x) + dir->z * cos(theta_x);
}

void	rotate_around_y(t_vec *result, t_vec *dir, float theta_y)
{
	result->x = dir->x * cos(theta_y) + dir->z * sin(theta_y);
	// (void)result->y = dir->y;
	result->z = - 1 * dir->x * sin(theta_y) + dir->z * cos(theta_y);
}

void	rotate_around_z(t_vec *result, t_vec *dir, float theta_z)
{
	//v'  [x*cos(θ)-y*sin(θ), x*sin(θ)+y*cos(θ), z]
	result->x = dir->x * cos(theta_z) - dir->y * sin(theta_z);
	result->y = dir->x * sin(theta_z) + dir->y * cos(theta_z);
	// (void)result->z = dir->z;
}

//my brilliant soloution
// result.x = dir->x * cos(y) * cos(z) - dir->y * sin(z) * cos(y) + dir->z * sin(y);
// result.y = dir->x * sin(z) * cos(x) - dir->y * cos(z) * sin(x) 
// 	+ dir->x * sin(y) * cos(z) * sin(x) - dir->y * sin(z) * sin(y) * sin (x)
// 	- dir->z * cos(y) * sin(x);
// result.z = dir->x * sin(z) * sin(x) + dir->y * cos(z) * sin(x)
// 	- dir->x * sin(y) * cos(z) * cos(x) + y * sin(z) * sin(y) * cos(x)
// 	+ dir->z * cos(y) * cos(x);

//chat gpt loser solution
	// result.x = dir->x * cos(z) * cos(y) - dir->y * sin(z) + dir->z * cos(z) * sin(y);
    // result.y = dir->x * sin(z) * cos(y) + dir->y * cos(z) + dir->z * sin(z) * sin(y);
    // result.z = dir->x * sin(y) + dir->z * cos(y);