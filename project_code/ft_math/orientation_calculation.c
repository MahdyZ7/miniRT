/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orientation_calculation.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 21:20:49 by ahsalem           #+#    #+#             */
/*   Updated: 2023/01/14 18:03:12 by ayassin          ###   ########.fr       */
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

t_vec	dir_with_camera_orientation(t_vec *dir, t_scene *scene)
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
	t_vec 	tmp;
	
	vec_init(&tmp, dir->x, dir->y, dir->z);
	result->y = tmp.y * cos(theta_x) - tmp.z * sin(theta_x);
	result->z = tmp.y * sin(theta_x) + tmp.z * cos(theta_x);
}

void	rotate_around_y(t_vec *result, t_vec *dir, float theta_y)
{
	t_vec 	tmp;
	
	vec_init(&tmp, dir->x, dir->y, dir->z);
	result->x = tmp.x * cos(theta_y) + tmp.z * sin(theta_y);
	result->z = -1 * tmp.x * sin(theta_y) + tmp.z * cos(theta_y);
}

void	rotate_around_z(t_vec *result, t_vec *dir, float theta_z)
{
	t_vec 	tmp;
	
	vec_init(&tmp, dir->x, dir->y, dir->z);
	result->x = tmp.x * cos(theta_z) - tmp.y * sin(theta_z);
	result->y = tmp.x * sin(theta_z) + tmp.y * cos(theta_z);
}

//my brilliant soloution that doesn't work
// result.x = dir->x * cos(y) * cos(z) - dir->y 
//* sin(z) * cos(y) + dir->z * sin(y);
// result.y = dir->x * sin(z) * cos(x) - dir->y * cos(z) * sin(x) 
// 	+ dir->x * sin(y) * cos(z) * sin(x) - dir->y * sin(z) * sin(y) * sin (x)
// 	- dir->z * cos(y) * sin(x);
// result.z = dir->x * sin(z) * sin(x) + dir->y * cos(z) * sin(x)
// 	- dir->x * sin(y) * cos(z) * cos(x) + y * sin(z) * sin(y) * cos(x)
// 	+ dir->z * cos(y) * cos(x);

//chat gpt solution has only y and z axis working
	// result.x = dir->x * cos(z) * cos(y) 
	//- dir->y * sin(z) + dir->z * cos(z) * sin(y);
	// result.y = dir->x * sin(z)
	//* cos(y) + dir->y * cos(z) + dir->z * sin(z) * sin(y);
	// result.z = dir->x * sin(y) + dir->z * cos(y);