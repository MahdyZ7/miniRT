/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   another_raytracing.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 14:13:26 by ayassin           #+#    #+#             */
/*   Updated: 2022/12/28 21:01:16 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	normalize(t_vec *v)
{
	float inv = 1 / sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
	v->x *= inv;
	v->y *= inv;
	v->z *= inv;
}

int sphear_intersect(t_vec *origin, t_vec *dir, t_sphere *sphere)
{
	t_vec	co;
	float	tca;
	float	d2;

	vec_init(&co, sphere->center.x - origin->x, sphere->center.y - origin->y, sphere->center.z - origin->z);
	tca = vec_dot(&co, dir);
	if (tca < 0)
		return (0);
	d2 = vec_dot(&co, &co) - tca * tca;
	if (d2 > sphere->diameter * sphere->diameter / 4.0)
		return (0);
	return (1);
}

float	simple_hit2(t_sphere *sphere, t_vec *dir)
{
	float	a;
	float	b;
	float	c;
	float	discriminant;
	float	root[2];

	a = dir->x * dir->x + dir->y * dir->y + dir->z * dir->z;
	b = -2.0 * (dir->x * sphere->center.x + dir->y * sphere->center.y + dir->z * sphere->center.z);
	c = sphere->center.x * sphere->center.x + sphere->center.y * sphere->center.y + sphere->center.z * sphere->center.z
		- (sphere->diameter * sphere->diameter / 4.0);
	discriminant = b * b - 4.0 * a * c;
	if (discriminant < 0)
		return (0);
	root[0] = (-b - sqrt(discriminant)) / (2.0 * a);
	root[1] = (-b + sqrt(discriminant)) / (2.0 * a);
	if (root[0] < 1 && root[1] < 1)
		return (0);
	if (root[0] < 1)
		return (root[1]);
	if (root[1] < 1)
		return (root[0]);
	return (root[0] < root[1] ? root[0] : root[1]);
}

void unknown_raytracing(t_img *img)
{ 
	t_vec		raydir;
	t_vec		cam;
	t_sphere	*sphere;
	int			color;
    unsigned width = img->width, height = img->hight; 
    float invWidth = 1 / (float)width, invHeight = 1 / (float)height; 
    float fov = 50, aspectratio = width / (float)height;
    float angle = tan(M_PI * 0.5 * fov / 180.);
	sphere = malloc((sizeof(t_sphere) * 3));
	vec_init(&cam, 0, 0, 0);
	sphere_init(&sphere[0], img->test.center.x, img->test.center.y,
		img->test.center.z, img->test.diameter, 0x00FF00);
	vis_single_sphere(sphere[0]);
    // Trace rays
    for (unsigned y = 0; y < height; ++y) { 
        for (unsigned x = 0; x < width; ++x) { 
            float xx = (2 * ((x + 0.5) * invWidth) - 1) * angle * aspectratio; 
            float yy = (1 - 2 * ((y + 0.5) * invHeight)) * angle;
			// xx = x - width / 2; 
            // yy = height / 2 - y;
			vec_init(&raydir, xx, yy, 1);
            // normaddlize(&raydir); 
            // if (sphear_intersect(&cam, &raydir, &sphere[0]))
			if (simple_hit2(&sphere[0], &raydir))
				color = 0x00FF00;
			else
				color = 0x000000;
			pixel_put(img, x, y, color);
        }
    }
	free(sphere);
} 