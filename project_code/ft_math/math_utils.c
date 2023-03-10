/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 14:20:46 by ahsalem           #+#    #+#             */
/*   Updated: 2023/01/16 03:43:12 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

t_vec	fit_coordinate_to_screen(float x, float y, t_scene *scene)
{
	float	inv_width;
	float	inv_height;
	float	aspectratio;
	float	angle;
	t_vec	result;

	inv_width = 1 / (float)WIN_WIDTH;
	inv_height = 1 / (float)WIN_HIGHT;
	aspectratio = (float)WIN_WIDTH / (float)WIN_WIDTH;
	angle = tan(M_PI * 0.5 * scene->camera.view_field / 180.0);
	result.x = (2 * ((x + 0.5) * inv_width) - 1) * angle * aspectratio;
	result.y = (1 - 2 * ((y + 0.5) * inv_height)) * angle;
	return (result);
}

t_vec	vec_scalar_add(t_vec *vec1, float scalar)
{
	t_vec	result;

	result.x = vec1->x + scalar;
	result.y = vec1->y + scalar;
	result.z = vec1->z + scalar;
	return (result);
}

t_vec	vec_scalar_sub(t_vec *vec1, float scalar)
{
	t_vec	result;

	result.x = vec1->x + scalar;
	result.y = vec1->y + scalar;
	result.z = vec1->z + scalar;
	return (result);
}

t_pln_equ	fill_plane_equation(t_plane plane)
{
	t_pln_equ	equation;

	equation.abc.x = plane.orientation.x;
	equation.abc.y = plane.orientation.y;
	equation.abc.z = plane.orientation.z;
	equation.d = (-1 * equation.abc.x * plane.pos.x)
		- (equation.abc.y * plane.pos.y)
		- (equation.abc.z * plane.pos.z);
	return (equation);
}

void	init_rototion_angels_with_hooks(t_scene *scene)
{
	fill_single_vector(&scene->camera.sin_theta,
		sin(scene->camera.xyz_angles.x),
		sin(scene->camera.xyz_angles.y),
		sin(scene->camera.xyz_angles.z));
	fill_single_vector(&scene->camera.cos_theta,
		cos(scene->camera.xyz_angles.x),
		cos(scene->camera.xyz_angles.y),
		cos(scene->camera.xyz_angles.z));
}
