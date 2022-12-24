/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 01:52:45 by ahsalem           #+#    #+#             */
/*   Updated: 2022/12/25 02:13:08 by ahsalem          ###   ########.fr       */
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

void	fill_single_vector(t_vec *vec, float x, float y, float z)
{
	vec->x = x;
	vec->y = y;
	vec->z = z;
}
