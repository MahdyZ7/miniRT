/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 16:43:11 by ahsalem           #+#    #+#             */
/*   Updated: 2022/12/25 17:03:47 by ahsalem          ###   ########.fr       */
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
