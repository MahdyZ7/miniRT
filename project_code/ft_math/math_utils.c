/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 14:20:46 by ahsalem           #+#    #+#             */
/*   Updated: 2022/12/25 15:56:56 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	fill_single_vector(t_vec *vec, float x, float y, float z)
{
	vec->x = x;
	vec->y = y;
	vec->z = z;
}

int	color_vec_to_int(t_vec color)
{
	int	result;

	result = (((int)color.x & 0x0ff) << 16)
		| (((int)color.y & 0x0ff) << 8) | ((int)color.z & 0x0ff);
	return (result);
}