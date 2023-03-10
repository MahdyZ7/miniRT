/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 17:17:04 by ahsalem           #+#    #+#             */
/*   Updated: 2023/01/18 11:06:45 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	hit_other_object(
		t_vec hit_point, t_vec light_vec, t_scene *scene)
{
	if (is_plane_shadow(hit_point, light_vec, scene))
		return (1);
	if (is_sphere_shadow(hit_point, light_vec, scene))
		return (1);
	if (is_cylinder_shadow(hit_point, light_vec, scene))
		return (1);
	return (0);
}

int	is_plane_shadow(t_vec hit_point, t_vec light_vec, t_scene *scene)
{
	float		temp_t;
	int			i;

	i = 0;
	while (i < scene->n_planes)
	{
		temp_t = hit_plane(&(scene->plane[i]), &hit_point, &light_vec);
		if (temp_t && temp_t > 0.001 && temp_t < 1)
			return (1);
		i++;
	}
	return (0);
}

int	is_sphere_shadow(t_vec hit_point, t_vec light_vec, t_scene *scene)
{
	float		temp_t;
	int			i;

	i = 0;
	while (i < scene->n_spheres)
	{
		temp_t = hit_sphere
			(&(scene->spheres[i]), &hit_point, &light_vec, 0.001);
		if (temp_t && temp_t > 0.001 && temp_t < 1.0)
			return (1);
		++i;
	}
	return (0);
}

int	is_cylinder_shadow(t_vec hit_point, t_vec light_vec, t_scene *scene)
{
	float	temp_t;
	int		i;

	i = 0;
	while (i < scene->n_cylinders)
	{
		temp_t = hit_cylinder
			(&(scene->cylinder[i]), &hit_point, &light_vec, 0.001);
		if (temp_t && temp_t > 0.001 && temp_t < 1.0)
			return (1);
		++i;
	}
	return (0);
}
