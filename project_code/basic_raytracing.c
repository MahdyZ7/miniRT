/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_raytracing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 18:55:05 by ayassin           #+#    #+#             */
/*   Updated: 2023/01/03 18:56:38 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	vec_to_color(t_vec vec)
{
	int	color;

	color = 0;
	if (vec.x >= 255)
		color += 255 << 16;
	else
		color += (int)(vec.x) << 16 ;
	if (vec.y >= 255)
		color += 255 << 8;
	else
		color += (int)(vec.y) << 8;
	if (vec.z >= 255)
		color += 255;
	else
		color += (int)(vec.z);
	return (color);
}

float	compute_color(t_vec *dir, t_sphere *sphr, t_scene *scene, float close_t)
{
	float	i;
	t_vec	normal;
	t_vec	hit_point;
	t_vec	light_vec;

	i = 0;
	hit_point = vec_scalar_mult(dir, close_t);
	hit_point = vec_add(&(scene->camera.view_point), &hit_point);
	normal = vec_sub(&hit_point, &(sphr->center));
	// normalize(&normal);
	light_vec = vec_sub(&(scene->light.pos), &hit_point);
	// normalize(&light_vec);
	i += scene->amb_light.ratio;
	if (vec_dot(&normal, &light_vec) > 0)
		i += scene->light.brightness * vec_dot(&normal, &light_vec)
			/ (vector_magnitude(&normal) * vector_magnitude(&light_vec));
	return (i);
}

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

int	trace_ray(t_vec *dir, float t_min, t_scene *scene)
{
	int			color;
	float		closest_t;
	float		temp_t;
	t_sphere	*closest_sphere;
	int			i;

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
		float m = compute_color(dir, closest_sphere, scene, closest_t);
		vec_scalar_mult(&(closest_sphere->color), m);
		color = vec_to_color(vec_scalar_mult(&(closest_sphere->color), m));
	}
	return (color);
}

void	basic_raytracing(t_img *img)
{
	t_ray_trace_kit	r;

	init_ray_trace_kit(&r, img);
	while (r.x < WIN_WIDTH)
	{
		r.y = 0;
		while (r.y < WIN_HIGHT)
		{
			r.new_x = (2 * ((r.x + 0.5) * r.invWidth) - 1)
				* r.angle * r.aspectratio;
			r.new_y = (1 - 2 * ((r.y + 0.5) * r.invHeight)) * r.angle;
			vec_init(&r.dir, r.new_x, r. new_y,
				img->scene->camera.view_point.z + 1);
			// r.color = trace_ray(&r.dir, 1, img->scene);
			// r.color = trace_plane(&r.dir, 1, img->scene);
			r.color = trace_cylinder(&r.dir, 1, img->scene);
			pixel_put(img->scene->win->img, r.x, r.y, r.color);
			++r.y;
		}
		r.x++;
	}
}

void	init_ray_trace_kit(t_ray_trace_kit *r, t_img *img)
{
	r->x = 0;
	r->y = 0;
	r->invWidth = 1 / (float)WIN_WIDTH;
	r->invHeight = 1 / (float)WIN_HIGHT;
	r->aspectratio = (float)WIN_WIDTH / (float)WIN_HIGHT;
	r->angle = tan(M_PI * 0.5 * img->scene->camera.view_field / 180.);
	r->color = 0;
}
