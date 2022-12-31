/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 14:20:46 by ahsalem           #+#    #+#             */
/*   Updated: 2022/12/31 07:37:09 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	fill_single_vector(t_vec *vec, float x, float y, float z)
{
	vec->x = x;
	vec->y = y;
	vec->z = z;
}

float	vector_magnitude(t_vec *vec)
{
	return (sqrt((vec->x * vec->x) + (vec->y * vec->y) + (vec->z * vec->z)));
}

t_vec	fit_coordinate_to_screen(float x, float y, t_scene *scene)
{
	float	invWidth;
	float	invHeight;
	float	aspectratio;
	float	angle;
	t_vec	result;

	invWidth = 1 / (float)WIN_WIDTH;
	invHeight = 1 / (float)WIN_HIGHT;
	aspectratio = (float)WIN_WIDTH / (float)WIN_WIDTH;
	angle = tan(M_PI * 0.5 * scene->camera.view_field / 180.0);
	result.x = (2 * ((x + 0.5) * invWidth) - 1) * angle * aspectratio;
	result.y = (1 - 2 * ((y + 0.5) * invHeight)) * angle;
	return (result);
}
