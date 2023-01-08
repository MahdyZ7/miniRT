/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_plane_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 19:13:24 by ahsalem           #+#    #+#             */
/*   Updated: 2023/01/08 14:46:13 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"
//do the same changes as sphere
/*
	// old_hit = vec_scalar_mult(dir, close_t);
	// old_hit = vec_add(&(scene->camera.view_point), &hit_point);
	subtraction other option
	// light_vec = vec_sub(&hit_point, &(scene->light.pos));
	float a other option
	// float a= vec_dot(&normal, &light_vec);
	// normalize(&light_vec);
*/
t_vec	compute_cylinder_color(t_scene *scene, t_vec *dir,t_cylinder *closest_cylinder)
{
	t_vec	i;
	t_vec	normal;
	t_vec	hit_point;
	t_vec	light_vec;

	fill_single_vector(&i, 0, 0, 0);
	hit_point = (hit_cylinder(closest_cylinder, &scene->camera.view_point, dir, 1)).child;
	normal = closest_cylinder->orientation;
	light_vec = vec_sub(&(scene->light.pos), &hit_point);
	i.x += scene->amb_light.ratio * scene->amb_light.color.x;
	i.y += scene->amb_light.ratio * scene->amb_light.color.y;
	i.z += scene->amb_light.ratio * scene->amb_light.color.z;
	return (i);
}

t_vec	plane_color(t_vec *dir, t_plane *pln, t_scene *scene)
{
	t_vec	i;
	t_vec	normal;
	t_vec	hit_point;
	t_vec	light_vec;
	float	a;

	fill_single_vector(&i, 0, 0, 0);
	hit_point = hit_actual_plane(pln, scene, dir);
	normal = pln->orientation;
	light_vec = vec_sub(&(scene->light.pos), &hit_point);
	i.x += scene->amb_light.ratio * scene->amb_light.color.x;
	i.y += scene->amb_light.ratio * scene->amb_light.color.y;
	i.z += scene->amb_light.ratio * scene->amb_light.color.z;
	if (hit_other_object(hit_point, light_vec, scene))
		return (i);
	a = fabsf(vec_dot(&normal, &light_vec));
	if (a > 0)
	{
		i = add_plane_spot_light(scene, &normal, &light_vec, &i);
	}
	return (i);
}
t_vec	add_plane_spot_light(
	t_scene *scene, t_vec *normal, t_vec *light_vec, t_vec *i)
{
	float	a;

	a = fabsf(vec_dot(normal, light_vec));
	i->x += scene->light.brightness * scene->light.color.x
		* a / (vector_magnitude(normal) * vector_magnitude(light_vec));
	i->y += scene->light.brightness * scene->light.color.y
		* a / (vector_magnitude(normal) * vector_magnitude(light_vec));
	i->z += scene->light.brightness * scene->light.color.z
		* a / (vector_magnitude(normal) * vector_magnitude(light_vec));
	return (*i);
}
