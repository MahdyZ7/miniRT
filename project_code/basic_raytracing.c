/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_raytracing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 18:55:05 by ayassin           #+#    #+#             */
/*   Updated: 2022/12/28 21:26:57 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int vec_to_color(t_vec *vec)
{
	int color;

	color = 0;
	color += (int)(vec->x) << 16;
	color += (int)(vec->y) << 8;
	color += (int)(vec->z);
	return (color);
}

float	hit_sphere(t_sphere *sphere, t_vec *origin, t_vec *dir, float t_min, float t_max)
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
	if (!(t_min < root[0] && root[0] <= t_max))
		if (!(t_min < root[1] && root[1] <= t_max))
			return (INFINITY);
	if (root[1] < t_min || t_max <= root[1])
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
		color  = vec_to_color(&(closest_sphere->color));
	return (color);
}

void	basic_raytracing(t_img *img)
{
	int			color;
	t_vec		dir;
	t_vec		cam;
	t_sphere	*sphere;
    float invWidth = 1 / (float)img->width, invHeight = 1 / (float)img->hight; 
    float fov = 35, aspectratio = img->width / (float)img->hight;
    float angle = tan(M_PI * 0.5 * fov / 180.);
	color = 0;
	sphere = malloc((sizeof(t_sphere) * 3));
	vec_init(&cam, 0, 0, 0);
	sphere_init(&sphere[0], img->test.center.x, img->test.center.y,
		img->test.center.z, img->test.diameter, 0x00FF00);
	sphere_init(&sphere[1], 1.5, 1.5, 11, 3, 0xFF0000);
	sphere_init(&sphere[2], -1.5, 1.5, 11, 3, 0x0000FF);
	for (int x = 0; x < img->width; x++)
	{
		for (int y = 0; y < img->hight; y++)
		{
			float xx = (2 * ((x + 0.5) * invWidth) - 1) * angle * aspectratio; 
            float yy = (1 - 2 * ((y + 0.5) * invHeight)) * angle;
			vec_init(&dir, xx, yy, 1);
			color = trace_ray(&cam, &dir, 1, INFINITY, sphere);
			pixel_put(img, x, y, color);
		}
	}
	free(sphere);
}


//I missed up last parameter in line 95 please fix it witht new structure
// void	basic_raytracing(t_img *img)
// {
// 	int			color;
// 	t_vec		dir;
// 	t_vec		cam;
// 	t_sphere	*sphere;

// 	color = 0;
// 	(void) img;
// 	sphere = malloc((sizeof(t_sphere) * 3));
// 	vec_init(&cam, 0, 0, 0);
// 	sphere_init(&sphere[0], img->test.center.x, img->test.center.y,
// 		img->test.center.z, img->test.diameter, 0x00FF00);
// 	vis_single_sphere(sphere[0]);
// 	for (int y = img->hight; y > 0; --y)
// 	{
// 		for (int x = 0; x < img->width; ++x)
// 		{
// 			pixel_put(img, x, y, color);
// 		}
// 	}
// 	free(sphere);
// }