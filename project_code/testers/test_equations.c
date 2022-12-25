/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_equations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 16:44:35 by ahsalem           #+#    #+#             */
/*   Updated: 2022/12/25 18:33:03 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	test_quadratic(void)
{
	t_vec	result;

	for (float i = 0; i < 10; i++)
	{
		result = qudratic_equation(i, i * i , i );
		vis_vector(result);
		printf("\n");
	}
}

void	test_normalized_float(void)
{
	float	result;
	t_vec	test_vec;

	for (float i = 0; i < 10; i++)
	{
		fill_single_vector(&test_vec, i, i * i, i);
		result = normalize_vec_to_float(test_vec);
		printf("%3.2f\n", result);
	}
}

void	test_normalized_vec(void)
{
	t_vec	result;
	t_vec	test_vec;

	for (float i = 0; i < 10; i++)
	{
		fill_single_vector(&test_vec, i, i * i, i);
		result = normalize_vec_to_vec(test_vec);
		vis_vector(result);
		printf("\n");
	}
}