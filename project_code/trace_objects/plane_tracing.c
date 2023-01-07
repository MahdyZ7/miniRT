/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_tracing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 07:36:53 by ahsalem           #+#    #+#             */
/*   Updated: 2023/01/07 16:25:17 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

//do the same changes as sphere
t_vec	plane_color(t_vec *dir, t_plane *pln, t_scene *scene, float close_t)
{
	t_vec	i;
	t_vec	normal;
	t_vec	hit_point;
	t_vec	light_vec;
	// t_vec	old_hit;

	fill_single_vector(&i, 0, 0, 0);
	(void)close_t;
	// old_hit = vec_scalar_mult(dir, close_t);
	// old_hit = vec_add(&(scene->camera.view_point), &hit_point);
	hit_point = hit_actual_plane(pln, scene, dir);
	// hit_point = old_hit;
	// printf("old hit vs new hit ");
	// vis_vector(old_hit);
	// printf("     ");
	// vis_vector(hit_point);
	// printf("\n");
	normal = pln->orientation;
	light_vec = vec_sub(&(scene->light.pos), &hit_point);
	// light_vec = vec_sub(&hit_point, &(scene->light.pos));
	i.x += scene->amb_light.ratio * scene->amb_light.color.x;
	i.y += scene->amb_light.ratio * scene->amb_light.color.y;
	i.z += scene->amb_light.ratio * scene->amb_light.color.z;
	if (hit_other_object(hit_point, light_vec, scene))
		return (i);
	float a= fabsf(vec_dot(&normal, &light_vec));
	// float a= vec_dot(&normal, &light_vec);
	if (a > 0)
	{
		// normalize(&light_vec);
		i.x += scene->light.brightness * scene->light.color.x
				* a / (vector_magnitude(&normal)
				* vector_magnitude(&light_vec));
		i.y += scene->light.brightness * scene->light.color.y 
				* a / (vector_magnitude(&normal)
				* vector_magnitude(&light_vec));
		i.z += scene->light.brightness * scene->light.color.z
				* a / (vector_magnitude(&normal) 
				* vector_magnitude(&light_vec));
	}
	return (i);
}


int	hit_other_object(t_vec hit_point, t_vec light_vec, t_scene *scene)
{
	// float		closest_t;
	float		temp_t;
	// t_plane		*closest_plane;
	// t_vec		m;
	// t_vec		result;
	int			i;

	// closest_t = INFINITY;
	// closest_plane = NULL;
	i = 0;
	// normalize(&light_vec);
	for (int i = 0; i < scene->n_planes; i++)
	{
		temp_t = hit_plane(&(scene->plane[i]), scene, &light_vec);
		if (temp_t && temp_t > 0.00001 && temp_t < 1.0)
		{
			return (1);
			// closest_t = temp_t;
			// closest_plane = &(scene->plane[i]);
		}
	}
	while (i < scene->n_spheres)
	{
		temp_t = hit_sphere
			(&(scene->spheres[i]), &hit_point, &light_vec, 0.00001);
		if (temp_t && temp_t > 0.00001 && temp_t < 1.0)
		{
			return (1);
			// closest_t = temp_t;
			// closest_sphere = &(scene->spheres[i]);
		}
		++i;
	}
	return (0);
}




t_vec	hit_actual_plane(t_plane *pln, t_scene *scene, t_vec *dir)
{
	float	alpha;
	t_vec	hit_point;
	t_vec	tmp;

	alpha = ((-1 * pln->equation.D) - vec_dot(&pln->equation.abc, &scene->camera.view_point))
			/ vec_dot(&pln->equation.abc, dir);
	tmp = vec_scalar_mult(dir, alpha);
	hit_point = vec_add(&scene->camera.view_point, &tmp);
	return (hit_point);
}

t_vec	trace_plane(t_vec *dir, float t_min, t_scene *scene)
{
	int			color;
	float		closest_t;
	float		temp_t;
	t_plane		*closest_plane;
	t_vec		m;
	t_vec		result;

	(void) t_min;
	closest_t = INFINITY;
	closest_plane = NULL;
	for (int i = 0; i < scene->n_planes; i++)
	{
		temp_t = hit_plane(&(scene->plane[i]), scene, dir);
		if (temp_t < closest_t)
		{
			closest_t = temp_t;
			closest_plane = &(scene->plane[i]);
		}
	}
	color = 0x000000;
	if (closest_plane != NULL)
	{
		m = plane_color(dir, closest_plane, scene, closest_t);
		color  = vec_to_color(vec_multiply_two_vectors(&(closest_plane->color), &m));
	}
	fill_single_vector(&result, closest_t, color, 0);
	return (result);
}

float	hit_plane(t_plane *plane, t_scene *scene, t_vec *dir)
{
	float	t;
	float	denominator;
	t_vec	p0l0;

	denominator = vec_dot(&plane->orientation, dir);
	
	if (denominator != 0)
	{
		p0l0 = vec_sub(&plane->pos, &scene->camera.view_point);
		// normalize(&p0l0);
		// the t * dir = Where do I hit
		t = vec_dot(&p0l0, &plane->orientation) / denominator;
		if (t > 0.000001)
			return (t);
		else
			return (INFINITY);
	}
	return (INFINITY);
}
