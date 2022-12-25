/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 16:43:11 by ahsalem           #+#    #+#             */
/*   Updated: 2022/12/25 18:31:08 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

/*
	return value (min_soloution, max_soloution, 0);
*/
t_vec	qudratic_equation(float a, float b, float c)
{
	float	discremenant;
	float	solution_1;
	float	solution_2;
	t_vec	result;

	result.z = 0;
	discremenant = b * b - (4 * a * c);
	if (discremenant < 0 || a == 0)
	{
		fill_single_vector(&result, INFINITY, INFINITY, INFINITY);
		return (result);
	}
	solution_1 = ((-1 * b) + sqrt(discremenant)) / (2 * a);
	solution_2 = ((-1 * b) - sqrt(discremenant)) / (2 * a);
	if (solution_1 < solution_2)
	{
		result.x = solution_1;
		result.y = solution_2;
	}
	else
	{
		result.x = solution_2;
		result.y = solution_1;
	}
	return (result);
}

float	normalize_vec_to_float(t_vec vec)
{
	float	result;

	result = (vec.x + vec.y + vec.z) / sqrt(
			vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	return (result);
}

t_vec	normalize_vec_to_vec(t_vec vec)
{
	t_vec	result;

	result.x = (vec.x) / sqrt(
			vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	result.y = (vec.y) / sqrt(
			vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	result.z = (vec.z) / sqrt(
			vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	return (result);
}