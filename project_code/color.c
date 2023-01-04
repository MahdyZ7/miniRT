/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 14:30:48 by ayassin           #+#    #+#             */
/*   Updated: 2023/01/04 14:37:31 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec	light_works(t_scene *scene, t_vec *normal, t_vec *hit_point)
{
	t_vec	i;
	t_vec	light_vec;

	vec_init(&i, 0 , 0, 0);
	light_vec = vec_sub(&(scene->light.pos), &hit_point);
	i = vec_scalar_mult(&i, scene->amb_light.ratio);
	if (vec_dot(&normal, &light_vec) > 0)
		i += scene->light.brightness * vec_dot(&normal, &light_vec)
			/ (vector_magnitude(&normal) * vector_magnitude(&light_vec));
	return (i);
}