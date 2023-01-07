/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orientation_calculation.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 21:20:49 by ahsalem           #+#    #+#             */
/*   Updated: 2023/01/07 21:26:15 by ahsalem          ###   ########.fr       */
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
/*
function find_angle(A, B):
    dot_product = A.x * B.x + A.y * B.y + A.z * B.z
    norm_A = sqrt(A.x^2 + A.y^2 + A.z^2)
    norm_B = sqrt(B.x^2 + B.y^2 + B.z^2)
    theta = acos(dot_product / (norm_A * norm_B))
    return theta
*/