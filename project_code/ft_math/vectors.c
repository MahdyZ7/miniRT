/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 01:52:45 by ahsalem           #+#    #+#             */
/*   Updated: 2022/12/25 14:20:43 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

float	vec_dot(t_vec *vec1, t_vec *vec2)
{
	return (vec1->x * vec2->x + vec1->y * vec2->y + vec1->z * vec2->z);
}

t_vec	vec_cross(t_vec vec1, t_vec vec2)
{
	t_vec	result;

	result.x = vec1.y * vec2.z - vec1.z * vec2.y;
	result.y = vec1.x * vec2.z - vec1.z * vec2.x;
	result.z = vec1.x * vec2.y - vec1.y * vec2.x;
	return (result);
}

t_vec	vec_add(t_vec vec1, t_vec vec2)
{
	t_vec	result;

	result.x = vec1.x + vec2.x;
	result.y = vec1.y + vec2.y;
	result.z = vec1.z + vec2.z;
	return (result);
}

t_vec	vec_sub(t_vec vec1, t_vec vec2)
{
	t_vec	result;

	result.x = vec1.x - vec2.x;
	result.y = vec1.y - vec2.y;
	result.z = vec1.z - vec2.z;
	return (result);
}

t_vec	vec_scalar_mult(t_vec vec1, float scalar)
{
	t_vec	result;

	result.x = vec1.x * scalar;
	result.y = vec1.y * scalar;
	result.z = vec1.z * scalar;
	return (result);
}
