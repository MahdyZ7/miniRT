/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_tracing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 07:36:53 by ahsalem           #+#    #+#             */
/*   Updated: 2023/01/03 18:39:48 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

float	plane_color(t_vec *dir, t_plane *pln, t_scene *scene, float close_t)
{
	float	i;
	t_vec	normal;
	t_vec	hit_point;
	t_vec	light_vec;

	i = 0;
	hit_point = vec_scalar_mult(dir, close_t);
	hit_point = vec_add(&(scene->camera.view_point), &hit_point);
	normal = pln->orientation;
	// normalize(&normal);
	light_vec = vec_sub(&(scene->light.pos), &hit_point);
	// normalize(&light_vec);
	i += scene->amb_light.ratio;
	if (vec_dot(&normal, &light_vec) > 0)
	{
		i += scene->light.brightness * vec_dot(&normal, &light_vec)
			/ (vector_magnitude(&normal) * vector_magnitude(&light_vec));
		// printf("The i is %f\n", i);
	}
	return (i);
}

int	trace_plane(t_vec *dir, float t_min, t_scene *scene)
{
	int			color;
	float		closest_t;
	float		temp_t;
	t_plane		*closest_plane;
	t_vec		vec_color;

	(void) t_min;
	closest_t = INFINITY;
	closest_plane = NULL;
	for (int i = 0; i < scene->plane->n_planes; i++)
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
		float m = plane_color(dir, closest_plane, scene, closest_t);
		// printf("the ")
		// float m = 1;
		// vec_scalar_mult(&(closest_plane->color), m);
		vec_color = vec_scalar_mult(&(closest_plane->color), m);
		color  = color_vec_to_int(&vec_color);
	}
	return (color);
}

// float	hit_plane(t_plane *plane, t_vec *origin, t_vec *dir, float t_min)
// {
// 	t_vec	oc;
// 	float	a;
// 	float	b;
// 	float	c;
// 	float	discriminant;
// 	float	root[2];

// 	vec_init(&oc, origin->x - plane->center.x,  origin->y - plane->center.y,  origin->z - plane->center.z);
// 	a = vec_dot(dir, dir);
// 	b = 2.0 * vec_dot(&oc, dir);
// 	c = vec_dot(&oc, &oc) - pow(plane->diameter / 2, 2);
// 	discriminant = b * b - 4 * a * c;
// 	if (discriminant < 0)
// 		return (INFINITY);
// 	if (!(t_min < root[0] && t_min < root[1]))
// 			return (INFINITY);
// 	if (root[1] < t_min || root[0] < root[1])
// 		return (root[0]);
// 	return (root[1]);
// }


// n = plane_orientation;
// p0 = plane coordinates
// l0 = camera view point
// l = fit_coordinate_to_screen(x, y, scene)
float	hit_plane(t_plane *plane, t_scene *scene, t_vec *dir)
{
	float	t;
	float	denominator;
	t_vec	p0l0;

	denominator = vec_dot(&plane->orientation, dir);
	
	if (denominator > 0.0000001)
	{
		p0l0 = vec_sub(&plane->pos, &scene->camera.view_point);
		// normalize(&p0l0);
		t = vec_dot(&p0l0, &plane->orientation) / denominator;;
		return (t);
	}
	return (INFINITY);
}

/*
	after reading again
l0 -> origin of the array ->camera.viewpoint
l ->  ray direction       -> dir
*/