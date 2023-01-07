/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 17:16:26 by ahsalem           #+#    #+#             */
/*   Updated: 2023/01/07 22:35:14 by ahsalem          ###   ########.fr       */
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

t_vec	vec_multiply_two_vectors(t_vec *vec1, t_vec *vec2)
{
	t_vec	result;

	result.x = vec1->x * vec2->x;
	result.y = vec1->y * vec2->y;
	result.z = vec1->z * vec2->z;
	return (result);
}

void	normalize(t_vec *v)
{
	float	inv;

	inv = 1 / sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
	v->x *= inv;
	v->y *= inv;
	v->z *= inv;
}
