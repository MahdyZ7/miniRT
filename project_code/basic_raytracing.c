/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_raytracing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 18:55:05 by ayassin           #+#    #+#             */
/*   Updated: 2022/12/30 19:46:11 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int vec_to_color(t_vec vec)
{
	int color;

	color = 0;
	color += (int)(vec.x) << 16;
	color += (int)(vec.y) << 8;
	color += (int)(vec.z);
	return (color);
}

int		compute_color(t_vec *origin, t_vec *dir, t_sphere *sphere, t_scene *scene, float closest_t)
{
	float	i;
	t_vec	normal;
	t_vec	hit_point;
	t_vec	light_vec;

	i = 0;
	hit_point = vec_add(*origin, vec_scalar_mult(*dir, closest_t));
	normal = vec_sub(hit_point, sphere->center);
	normalize(&normal);
	light_vec = vec_sub(scene->light.pos, hit_point); 
	i += scene->amb_light.ratio;
	if (vec_dot(&normal, &light_vec) > 0)
		i += scene->light.brightness * vec_dot(&normal, &light_vec) /
			sqrt(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z)
				* sqrt(light_vec.x * light_vec.x + light_vec.y * light_vec.y + light_vec.z * light_vec.z); //change
	return (i);
}

float	hit_sphere(t_sphere *sphere, t_vec *origin, t_vec *dir, float t_min)
{
	t_vec	oc;
	float	a;
	float	b;
	float	c;
	float	discriminant;
	float	root[2];

	vec_init(&oc, origin->x - sphere->center.x,  origin->y - sphere->center.y,  origin->z - sphere->center.z);
	a = vec_dot(dir, dir);
	b = 2.0 * vec_dot(&oc, dir);
	c = vec_dot(&oc, &oc) - pow(sphere->diameter / 2, 2);
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (INFINITY);
	root[0] = (-b - sqrt(discriminant)) / (2.0 * a);
	root[1] = (-b + sqrt(discriminant)) / (2.0 * a);
	if (!(t_min < root[0] && t_min < root[1]))
			return (INFINITY);
	if (root[1] < t_min || root[0] < root[1])
		return (root[0]);
	return (root[1]);
}

int	trace_ray(t_vec *origin, t_vec *dir, float t_min, t_scene *scene)
{
	int			color;
	float		closest_t;
	float		temp_t;
	t_sphere	*closest_sphere;

	closest_t = INFINITY;
	closest_sphere = NULL;
	for (int i = 0; i < scene->spheres->n_spheres; i++)
	{
		temp_t = hit_sphere(&(scene->spheres[i]), origin, dir, t_min);
		if (temp_t < closest_t)
		{
			closest_t = temp_t;
			closest_sphere = &(scene->spheres[i]);
		}
	}
	color = 0x000000;
	if (closest_sphere != NULL)
	{
		float m = compute_color(origin, dir, closest_sphere, scene, closest_t);
		vec_scalar_mult(closest_sphere->color, m);
		color  = vec_to_color(vec_scalar_mult(closest_sphere->color, m));
	}
	return (color);
}

void	basic_raytracing(t_img *img)
{
	int			color;
	t_vec		dir;
	t_vec		cam;

    float invWidth = 1 / (float)img->width, invHeight = 1 / (float)img->hight; 
    float fov = 70, aspectratio = img->width / (float)img->hight;
    float angle = tan(M_PI * 0.5 * fov / 180.);
	color = 0;
	vec_init(&cam, 0, 0, 0);
	for (int x = 0; x < img->width; x++)
	{
		for (int y = 0; y < img->hight; y++)
		{
			float xx = (2 * ((x + 0.5) * invWidth) - 1) * angle * aspectratio; 
            float yy = (1 - 2 * ((y + 0.5) * invHeight)) * angle;
			vec_init(&dir, xx, yy, 1);
			color = trace_ray(&cam, &dir, 1, img->scene);
			pixel_put(img, x, y, color);
		}
	}
}
