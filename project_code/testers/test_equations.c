/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_equations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 16:44:35 by ahsalem           #+#    #+#             */
/*   Updated: 2022/12/25 17:03:31 by ahsalem          ###   ########.fr       */
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