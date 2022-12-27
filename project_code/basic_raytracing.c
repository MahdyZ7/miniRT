/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_raytracing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 18:55:05 by ayassin           #+#    #+#             */
/*   Updated: 2022/12/25 16:41:23 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

float	hit_sphere(t_sphere *sphere, t_vec *origin, t_vec *dir, float t_min, float t_max)
{
	t_vec	oc;
	float	a;
	float	b;
	float	c;
	float	discriminant;
	float	root[2];

	vec_init(&oc, origin->x - sphere->center.x, origin->y - sphere->center.y, origin->z - sphere->center.z);
	a = vec_dot(dir, dir);
	b = 2.0 * vec_dot(&oc, dir);
	c = vec_dot(&oc, &oc) - sphere->diameter * sphere->diameter / 4.0;
	discriminant = b * b - 4.0 * a * c;
	if (discriminant < 0)
		return (INFINITY);
	root[0] = (-b - sqrt(discriminant)) / (2.0 * a);
	root[1] = (-b + sqrt(discriminant)) / (2.0 * a);
	// if ((root[0] < t_min && (root[1] < t_min || root[1] >= t_max)) || (root[0] >= t_max &&  (root[1] < t_min || root[1] >= t_max)))
	// 	return (INFINITY);
	// if (root[0] < t_min || root[0] >= t_max)
	// 	return (root[1]);
	// if (root[1] < t_min || root[1] >= t_max)
	// 	return (root[0]);
	(void)t_max;
	(void)t_min;
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

float	simple_hit(t_sphere *sphere, t_vec *dir)
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
		return (INFINITY);
	root[0] = (-b - sqrt(discriminant)) / (2.0 * a);
	root[1] = (-b + sqrt(discriminant)) / (2.0 * a);
	return (root[1]);
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
	for (int y = img->hight; y > 0; --y)
	{
		for (int x = 0; x < img->width; ++x)
		{
			vec_init(&dir, x - img->width / 2 , y - img->hight / 2, 1);
			// printf("dir vector %f %f %f\n", dir.x, dir.y, dir.z);
			// color = trace_ray(&cam, &dir, 1, INFINITY, sphere);
			if (simple_hit(&sphere[0], &dir) < INFINITY)
			{
				// printf("(%d, %d, %d) ", (int)dir.x, (int)dir.y, (int)dir.z);
				color = 0x00FF00;
			}
			else
				color = 0x000000;
			// printf("(%d,%d,%d) ", (int)dir.x, (int)dir.y, (int)dir.z);
			pixel_put(img, x, y, color);
		}
		// printf("\n");
	}
	free(sphere);
}