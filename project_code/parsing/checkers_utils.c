/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 16:35:28 by ahsalem           #+#    #+#             */
/*   Updated: 2023/01/05 16:46:12 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	check_normalized_coord(t_vec	vec)
{
	if ((vec.x > 1.00001 || vec.y > 1.00001|| vec.z > 1.00001)
		|| (vec.x < -1.00001 || vec.y < -1.00001 || vec.z < -1.00001))
	{
		return (1);
	}
	else if (vector_magnitude(&vec) > 1.00001 || vector_magnitude(&vec) < 0.99999)
	{
		return (1);
	}
	return (0);
}