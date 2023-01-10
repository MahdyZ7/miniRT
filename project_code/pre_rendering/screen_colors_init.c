/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen_colors_init.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 19:12:34 by ahsalem           #+#    #+#             */
/*   Updated: 2023/01/10 20:38:50 by ayassin          ###   ########.fr       */
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
	result = (float)vec_to_color(tmp);
	return (result);
}
