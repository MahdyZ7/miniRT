/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_equations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 16:44:35 by ahsalem           #+#    #+#             */
/*   Updated: 2023/01/07 18:36:14 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	test_quadratic(void)
{
	t_vec	result;
	int		i;

	i = 0;
	while (i < 10)
	{
		result = qudratic_equation(i, i * i, i);
		vis_vector(result);
		printf("\n");
		i++;
	}
}

void	test_normalized_float(void)
{
	float	result;
	t_vec	test_vec;
	int		i;

	i = 0;
	while (i < 10)
	{
		fill_single_vector(&test_vec, i, i * i, i);
		result = normalize_vec_to_float(&test_vec);
		printf("%3.2f\n", result);
		i++;
	}
}

void	test_normalized_vec(void)
{
	t_vec	result;
	t_vec	test_vec;
	int		i;

	i = 0;
	while (i < 10)
	{
		fill_single_vector(&test_vec, i, i * i, i);
		result = normalize_vec_to_vec(&test_vec);
		vis_vector(result);
		printf("\n");
		i++;
	}
}
