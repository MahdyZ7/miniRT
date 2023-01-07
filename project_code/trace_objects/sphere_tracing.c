/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_tracing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 21:10:55 by ahsalem           #+#    #+#             */
/*   Updated: 2023/01/07 15:16:21 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

float	hit_sphere(t_sphere *sphere, t_vec *origin, t_vec *dir, float t_min)
{
	t_vec	oc;
	float	quad[3];

	oc = vec_sub(origin, &(sphere->center));
	quad[0] = vec_dot(dir, dir);
	quad[1] = 2.0 * vec_dot(&oc, dir);
	quad[2] = vec_dot(&oc, &oc) - pow(sphere->diameter / 2, 2);
	oc = qudratic_equation(quad[0], quad[1], quad[2]);
	if (oc.x < t_min && oc.y < t_min)
		return (INFINITY);
	if (oc.y < t_min || oc.x < oc.y)
		return (oc.x);
	return (oc.y);
}

t_vec	trace_sphere(t_vec *dir, float t_min, t_scene *scene)
{
	int			color;
	float		closest_t;
	float		temp_t;
	t_sphere	*closest_sphere;
	int			i;
	t_vec		result;

	closest_t = INFINITY;
	closest_sphere = NULL;
	i = 0;
	while (i < scene->n_spheres)
	{
		temp_t = hit_sphere
			(&(scene->spheres[i]), &scene->camera.view_point, dir, t_min);
		if (temp_t < closest_t)
		{
			closest_t = temp_t;
			closest_sphere = &(scene->spheres[i]);
		}
		++i;
	}
	color = 0x000000;
	if (closest_sphere != NULL)
	{
		t_vec m = compute_color_to_vec(dir, closest_sphere, scene, closest_t);
		color = vec_to_color(vec_multiply_two_vectors(&(closest_sphere->color), &m));
		// float m = compute_color(dir, closest_sphere, scene, closest_t);
		// vec_scalar_mult(&(closest_sphere->color), m);
		// color = vec_to_color(vec_scalar_mult(&(closest_sphere->color), m));
	}
	fill_single_vector(&result, closest_t, color, 0);
	return (result);
}
