/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_raytracing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 18:55:05 by ayassin           #+#    #+#             */
/*   Updated: 2022/12/25 21:11:44 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

float	vec_dot(t_vec *vec1, t_vec *vec2)
{
	return (vec1->x * vec2->x + vec1->y * vec2->y + vec1->z * vec2->z);
}

float	hit_sphere(t_sphere *sphere, t_vec *origin, t_vec *dir, float t_min, float t_max)
{
	float	a;
	float	b;
	float	c;
	float	discriminant;
	float	root[2];

	(void) origin;
	a = vec_dot(dir, dir);
	b = -2.0 * vec_dot(&(sphere->center), dir);
	c = vec_dot(&(sphere->center), &(sphere->center)) - sphere->diameter * sphere->diameter / 4.0;
	// printf("c = %f\n", c);
	discriminant = b * b - 4.0 * a * c;
	if (discriminant < 0)
		return (INFINITY);
	root[0] = (-b - sqrt(discriminant)) / (2.0 * a);
	root[1] = (-b + sqrt(discriminant)) / (2.0 * a);
	if ((root[0] < t_min && root[1] < t_min) || (root[0] >= t_max && root[1] >= t_max))
		return (INFINITY);
	if (root[0] < t_min || root[0] >= t_max)
		return (root[1]);
	if (root[1] < t_min || root[1] >= t_max)
		return (root[0]);
	if (root[0] < root[1])
		return (root[0]);
	return (root[1]);
}

//I missed up the return of this function please remember to fix it according to 
// the new structure
int	trace_ray(t_vec *origin, t_vec *dir, float t_min, float t_max, t_sphere *sphere)
{
	float		closest_t;
	float		temp_t;
	int			color;
	t_sphere	*closest_sphere;

	closest_t = t_max;
	closest_sphere = NULL;
	// vis_single_sphere(sphere[0]);
	temp_t = hit_sphere(&(sphere[0]), origin, dir, t_min, t_max);
	if (temp_t < closest_t && temp_t > t_min && temp_t < t_max)
	{
		closest_t = temp_t;
		closest_sphere = &(sphere[0]);
	}
	if (closest_sphere == NULL)
		return (0x000000);
	color = (((int)closest_sphere->color.x) << 16) + (((int)closest_sphere->color.y) << 8) + (((int)closest_sphere->color.z));
	return (color);
}

//I missed up last parameter in line 95 please fix it witht new structure
void	basic_raytracing(t_img *img)
{
	int			color;
	t_vec		dir;
	t_vec		cam;
	t_sphere	*sphere;

	color = 0;
	(void) img;
	sphere = malloc((sizeof(t_sphere) * 3));
	vec_init(&cam, 0, 0, 0);
	sphere_init(&sphere[0], img->test.center.x, img->test.center.y,
		img->test.center.z, img->test.diameter, 0x00FF00);
	vis_single_sphere(sphere[0]);
	for (int y = 0; y < img->hight; y++)
	{
		for (int x = 0; x < img->width; x++)
		{
			vec_init(&dir, x - img->width / 2 , y - img->hight / 2, 1);
			color = trace_ray(&cam, &dir, 1, INFINITY, sphere);
			if (hit_sphere(&sphere[0], &cam, &dir, 1, INFINITY) != INFINITY)
				printf("*");
			else
				printf(" ");
			pixel_put(img, x, y, color);
		}
		printf("\n");
	}
	free(sphere);
}