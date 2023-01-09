/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orientation_calculation.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 21:20:49 by ahsalem           #+#    #+#             */
/*   Updated: 2023/01/09 17:32:15 by ahsalem          ###   ########.fr       */
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
	
	result = find_rotation_matrix(&scene->camera.orientation, dir);
	return (result);
}

t_vec	find_rotation_matrix(t_vec *orientation, t_vec *dir)
{
	t_vec	result;
	float	theta_x;
	float	theta_y;
	float	theta_z;

	theta_x = orientation->x * M_PI_2;
	theta_y = orientation->y * M_PI_2;
	theta_z = orientation->z * M_PI_2;
	// rotate_around_x(&result, dir, theta_x);
	rotate_around_x(&result, dir, theta_x);
	rotate_around_y(&result, dir, theta_y); 
	rotate_around_z(&result, dir, theta_z);
// //rotate y_axis


	return (result);
}

void	rotate_around_x(t_vec *result, t_vec *dir, float theta_x)
{
	result->x = dir->x;
	result->y = dir->y * cos(theta_x) - dir->z *sin(theta_x);
	result->z = dir->y * sin(theta_x)+ dir->z * cos(theta_x);
}

void	rotate_around_y(t_vec *result, t_vec *dir, float theta_y)
{
	result->x = dir->x * cos(theta_y) + dir->z * sin(theta_y);
	result->y = dir->y;
	result->z = - 1 * dir->x * sin(theta_y) + dir->z * cos(theta_y);
}

void	rotate_around_z(t_vec *result, t_vec *dir, float theta_z)
{
	//v'  [x*cos(θ)-y*sin(θ), x*sin(θ)+y*cos(θ), z]
	result->x = dir->x * cos(theta_z) - dir->y * sin(theta_z);
	result->y = dir->x * sin(theta_z) + dir->y * cos(theta_z);
	result->z = dir->z;
}
