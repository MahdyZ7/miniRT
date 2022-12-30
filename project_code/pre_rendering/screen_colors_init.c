/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen_colors_init.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 19:12:34 by ahsalem           #+#    #+#             */
/*   Updated: 2022/12/30 19:20:11 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

float	color_by_intesity_to_float(t_vec *color, float intensity)
{
	float	result;
	t_vec	tmp;

	result = 0.0;
	tmp.x = color->x * intensity;
	tmp.y = color->y * intensity;
	tmp.z = color->z * intensity;
	result = (float)color_vec_to_int(&tmp);
	return (result);
}

int	color_vec_to_int(t_vec *color)
{
	int	result;

	result = (((int)color->x & 0x0ff) << 16)
		| (((int)color->y & 0x0ff) << 8) | ((int)color->z & 0x0ff);
	return (result);
}
