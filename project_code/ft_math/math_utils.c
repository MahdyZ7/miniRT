/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 14:20:46 by ahsalem           #+#    #+#             */
/*   Updated: 2023/01/06 18:15:45 by ahsalem          ###   ########.fr       */
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

t_plane_equation	fill_plane_equation(t_plane plane)
{
	t_plane_equation	equation;

	equation.abc.x = plane.orientation.x;
	equation.abc.y = plane.orientation.y;
	equation.abc.z = plane.orientation.z;
	equation.D = (-1 * equation.abc.x * plane.pos.x) - (equation.abc.y * plane.pos.y)
		- (equation.abc.z * plane.pos.z);
	return (equation);
}
/*
Write the normal to the plane in the form (A, B, C).
Write the coordinates of the point on the plane as (x1, y1, z1).
The equation of the plane can be written in the form Ax + By + Cz + D = 0, where D is a constant. To find the value of D, substitute the values of A, B, C, and the coordinates of the point on the plane into the equation: D = -Ax1 - By1 - Cz1.
The equation of the plane is now given by Ax + By + Cz - D = 0, where A, B, C, and D are the values you have just calculated.
*/