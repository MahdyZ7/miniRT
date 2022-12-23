/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_raytracing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 18:55:05 by ayassin           #+#    #+#             */
/*   Updated: 2022/12/23 09:35:56 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	vec_init(t_vec *vec, float x, float y, float z)
{
	vec->x = x;
	vec->y = y;
	vec->z = z;
}

void	sphere_init(t_sphere *sphere, float x, float y, float z, float diameter, int color)
{
	vec_init(&(sphere->center), x, y, z);
	sphere->diameter = diameter;
	sphere->color = color;
}

float	vec_dot(t_vec *vec1, t_vec *vec2)
{
	return (vec1->x * vec2->x + vec1->y * vec2->y + vec1->z * vec2->z);
}

float	hit_sphere(t_sphere *sphere, t_vec *origin, t_vec *dir, float t_min, float t_max)
{
	t_vec	co;
	float	a;
	float	b;
	float	c;
	float	discriminant;
	float	root[2];

	vec_init(&co, origin->x - sphere->center.x , origin->y - sphere->center.y, origin->z - sphere->center.z);
	a = vec_dot(dir, dir);
	b = 2.0 * vec_dot(&co, dir);
	c = vec_dot(&co, &co) - pow(sphere->diameter / 2, 2);
	discriminant = b * b - 4.0 * a * c;
	// printf("First cheack points: %f %f %f with color %x\n", dir->x, dir->y, dir->z, sphere->color);
	// printf("The sphere has points: %f %f %f with color %x\n", co.x, co.y, co.z, sphere->color);
	if (discriminant < 0)
	{
		// printf("The new points: %f %f %f with color %x\n", dir->x, dir->y, dir->z, sphere->color);
		// exit(0);
		return (INFINITY);
	}
	root[0] = (-b - sqrt(discriminant)) / (2.0 * a);
	root[1] = (-b + sqrt(discriminant)) / (2.0 * a);
	if (!(t_min < root[0] && root[0] < t_max))
	{
		if (!(t_min < root[1] && root[1] < t_max))
			return (INFINITY);
	}
	// printf("The new points: %f %f %f with color %x\n", dir->x, dir->y, dir->z, sphere->color);
	if (root[1] < t_min || t_max < root[1])
		return (root[0]);
	else if (root[0] < root[1])
		return (root[0]);
	return (root[1]);
}

int	trace_ray(t_vec *origin, t_vec *dir, float t_min, float t_max, t_sphere *sphere)
{
	int			color;
	float		closest_t;
	float		temp_t;
	t_sphere	*closest_sphere;

	closest_t = t_max;
	closest_sphere = NULL;
	for (int i = 0; i < 3; i++)
	{
		temp_t = hit_sphere(&(sphere[i]), origin, dir, t_min, t_max);
		if (temp_t < closest_t)
		{
			closest_t = temp_t;
			closest_sphere = &(sphere[i]);
		}
	}
	color = 0x000000;
	if (closest_sphere != NULL)
	{
		color  = closest_sphere->color;
		// color = sphere_color(closest_sphere);
	}
	return (color);
}

void	basic_raytracing(t_img *img)
{
	int			color;
	t_vec		dir;
	t_vec		cam;
	t_sphere	*sphere;

	color = 0;
	sphere = malloc((sizeof(t_sphere) * 3));
	vec_init(&cam, 0, 0, 0);
	sphere_init(&sphere[0], 0, 0, 60, 100, 0x00FF00);
	sphere_init(&sphere[1], 200, 400, 60, 100, 0xFF0000);
	sphere_init(&sphere[2], -200, 400, 60, 100, 0x0000FF);
	for (int x = 0; x < img->width; x++)
	{
		for (int y = 0; y < img->hight; y++)
		{
			// vx = x - img->width / 2; // * 1 / 1 ;
			// vy = y - img->hight / 2; // * 1 / 1 ;
			// dz = 1;
			vec_init(&dir, x - img->width / 2, y - img->hight / 2, 1);
			// printf("x = %f, y = %f\n", dir.x, dir.y);
			color = trace_ray(&cam, &dir, 1, INFINITY, sphere);
			// ray = ray_at_pixel(x, y);
			// color = ray_color(ray);
			// write_pixel(x, y, color);
			pixel_put(img, x, y, color);
		}
	}
	free(sphere);
}