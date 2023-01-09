/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orientation_calculation.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 21:20:49 by ahsalem           #+#    #+#             */
/*   Updated: 2023/01/08 19:35:34 by ahsalem          ###   ########.fr       */
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
	result.x = dir->x;
	result.y = dir->y * cos(theta_x) - dir->z *sin(theta_x);
	result.z = dir->y * sin(theta_x)+ dir->z * cos(theta_x);
	// result.x = ://do the matrix rotation here
	// result.x = :
	// result.x = :
	return (result);
}
//make the rotation matrix to multiply each theta as follows
//theta x = x * 180
//theta y = y * 180
//theta z = y * 180

/*
function find_angle(A, B):
    dot_product = A.x * B.x + A.y * B.y + A.z * B.z
    norm_A = sqrt(A.x^2 + A.y^2 + A.z^2)
    norm_B = sqrt(B.x^2 + B.y^2 + B.z^2)
    theta = acos(dot_product / (norm_A * norm_B))
    return theta
*/