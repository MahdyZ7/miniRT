/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_tracing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 07:36:53 by ahsalem           #+#    #+#             */
/*   Updated: 2023/01/12 16:53:16 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	hit_other_object(t_vec hit_point, t_vec light_vec, t_scene *scene)
{
	float		temp_t;
	int			i;

	i = 0;
	while (i < scene->n_planes)
	{
		// hit_point = vec_scalar_mult(&hit_point, 7);
		temp_t = hit_plane(&(scene->plane[i]), &hit_point, &light_vec);
		if (temp_t && temp_t > 0.00001 && temp_t < 1)
			return (1);
		i++;
	}
	i = 0;
	while (i < scene->n_spheres)
	{
		temp_t = hit_sphere
			(&(scene->spheres[i]), &hit_point, &light_vec, 0.00001);
		if (temp_t && temp_t > 0.00001 && temp_t < 1.0)
			return (1);
		++i;
	}
	i = 0;
	while (i < scene->n_cylinders)
	{
		temp_t = hit_cylinder
			(&(scene->cylinder[i]), &hit_point, &light_vec, 0.00001);
		if (temp_t && temp_t > 0.00001 && temp_t < 1.0)
			return (1);
		++i;
	}
	return (0);
}

t_vec	hit_actual_plane(t_plane *pln, t_scene *scene, t_vec *dir)
{
	float	alpha;
	t_vec	hit_point;
	t_vec	tmp;

	alpha = ((-1 * pln->equation.d)
			- vec_dot(&pln->equation.abc, &scene->camera.view_point))
		/ vec_dot(&pln->equation.abc, dir);
	tmp = vec_scalar_mult(dir, alpha);
	hit_point = vec_add(&scene->camera.view_point, &tmp);
	return (hit_point);
}

t_vec	trace_plane(t_vec *dir, t_scene *scene)
{
	int			color;
	t_plane		*closest_plane;
	t_vec		m;
	t_vec		result;
	float		closest_t;

	closest_t = INFINITY;
	closest_plane = find_closest_plane(scene, dir, &closest_t);
	color = 0x000000;
	if (closest_plane != NULL)
	{
		m = plane_color(dir, closest_plane, scene, closest_t);
		color = vec_to_color(
				vec_multiply_two_vectors(&(closest_plane->color), &m));
	}
	fill_single_vector(&result, closest_t, color, 0);
	return (result);
}

t_plane	*find_closest_plane(t_scene *scene, t_vec *dir, float *closest_t)
{
	t_plane	*closest_plane;
	float	temp_t;
	int		i;

	i = 0;
	closest_plane = NULL;
	while (i < scene->n_planes)
	{
		temp_t = hit_plane(&(scene->plane[i]), &(scene->camera.view_point), dir);
		if (temp_t < *closest_t)
		{
			*closest_t = temp_t;
			closest_plane = &(scene->plane[i]);
		}
		i++;
	}
	return (closest_plane);
}

float	hit_plane(t_plane *plane, t_vec *origin, t_vec *dir)
{
	float	t;
	float	denominator;
	t_vec	p0l0;

	denominator = vec_dot(&plane->orientation, dir);
	if (denominator != 0)
	{
		p0l0 = vec_sub(&plane->pos, origin);
		t = vec_dot(&p0l0, &plane->orientation) / denominator;
		if (t > 0.000001)
			return (t);
		else
			return (INFINITY);
	}
	return (INFINITY);
}

// float	hit_plane_shadow(t_plane *plane, t_scene *scene, t_vec *dir)
// {
// 	float	t;
// 	float	denominator;
// 	t_vec	p0l0;

// 	denominator = vec_dot(&plane->orientation, dir);
// 	if (denominator > 0)
// 	{
// 		p0l0 = vec_sub(&plane->pos, &scene->camera.view_point);
// 		t = vec_dot(&p0l0, &plane->orientation) / denominator;
// 		if (t > 0.000001)
// 			return (t);
// 		else
// 			return (INFINITY);
// 	}
// 	return (INFINITY);
// }
