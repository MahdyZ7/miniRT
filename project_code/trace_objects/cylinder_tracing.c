/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_tracing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 11:37:30 by ayassin           #+#    #+#             */
/*   Updated: 2023/01/06 11:43:20 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"



// Define the cylinder using a center point (C) and a unit vector (D) 
// that represents the direction of the cylinder's axis.
// You will also need to specify the radius (r) and height (h) of the cylinder.

// Define the ray using a starting point (P) and a direction vector (d).

// Translate both the cylinder and the ray so that the cylinder's center point 
// is at the origin (0,0,0). 
// This will make the math simpler because you can now treat the cylinder as a
// centered cylinder with a height of 2h.

// Calculate the dot product of the direction vector d with the cylinder's 
// unit vector D. Let this value be denoted as tD.

// Calculate the projection of the vector P onto the cylinder's axis by 
// subtracting the component of P that is orthogonal to D from P.
// Let this projection be denoted as P'.

// Calculate the length of the vector P' using the Pythagorean theorem.
// Let this value be denoted as tP'.

// If tP' > r, then the ray does not intersect the cylinder.
// If tP' <= r, then the ray intersects the cylinder at one or two points.

// To find the intersection points, you can use the quadratic formula
// to solve for t in the equation P + t * d = P' + tD * D.
// This will give you the values of t that correspond to the intersection points.
// You can then use these values of t to find the intersection points by 
// plugging them back into the equation P + t * d.


// cylinder defined by extremes pa and pb, and radious ra
t_vec4	hit_cylinder(t_cylinder *cylinder, t_vec *origin, t_vec *dir, float t_min)
{
	(void)t_min;
	t_vec4	result;
	t_vec	child;
	t_vec	dir_by_t;
	t_vec	cylinder_end_by_y;
	t_vec	cylinder_end_by_y_by_height;
	t_vec	first_sub_part;
	t_vec	second_sub_part;
	t_vec	cylinder_end = get_cylinder_height(cylinder);
	t_vec	vec_cylinder_height = vec_sub(&cylinder_end, &(cylinder->pos));
	t_vec	origin_to_cylinder = vec_sub(origin, &(cylinder->pos));
	float	height_dot_product = vec_dot(&vec_cylinder_height, &vec_cylinder_height);
	float	height_by_direction = vec_dot(&vec_cylinder_height, dir);
	float	height_by_origin_to_cylinder = vec_dot(&vec_cylinder_height, &origin_to_cylinder);
	float	k2 = height_dot_product - height_by_direction * height_by_direction;
	float	k1 = height_dot_product * vec_dot(&origin_to_cylinder, dir) - height_by_origin_to_cylinder * height_by_direction;
	float	k0 = height_dot_product * vec_dot(&origin_to_cylinder, &origin_to_cylinder) - height_by_origin_to_cylinder * height_by_origin_to_cylinder - (cylinder->diameter / 2) * (cylinder->diameter / 2) * height_dot_product;
	float	h = k1 * k1 - k2 * k0;

	fill_single_vector(&child, INFINITY, INFINITY, INFINITY);
	fill_4vec(&result,INFINITY, child);
	if( h < 0.0 )
		return result;//no intersection
    h = sqrt(h);
    float t = (-k1 - h) / k2;
    // body
    float y = height_by_origin_to_cylinder + t * height_by_direction;
    if( y > 0.0 && y < height_dot_product)
	{
		cylinder_end_by_y = vec_scalar_mult(&cylinder_end, y);
		cylinder_end_by_y_by_height = vec_scalar_mult(&cylinder_end_by_y, 1 / height_dot_product);
		dir_by_t = vec_scalar_mult(dir, t);
		first_sub_part = vec_add(&dir_by_t, &origin_to_cylinder);
		second_sub_part = vec_scalar_mult(&cylinder_end_by_y_by_height, 1 / (cylinder->diameter / 2));
		fill_4vec(&result, t, vec_sub(&first_sub_part, &second_sub_part));
		return (result);
	}
	//handling caps
    t = (((y < 0.0) ? 0.0 : height_dot_product) - height_by_origin_to_cylinder) / height_by_direction;
    if(fabsf(k1 + k2 * t) < h)
    {
		t_vec	vec_cyl_height_by_sin_y = vec_scalar_mult(&vec_cylinder_height, sign(y));
		t_vec	total =vec_scalar_mult(&vec_cyl_height_by_sin_y,  1 / sqrt(height_dot_product));
		fill_4vec(&result, t, total);
		return (result);
	}
    return (result);//no intersection
}

float	check_capped_part(float t0, float t1,
	 t_vec *origin, t_vec *dir, t_cylinder *cylinder)
{
	t_vec	result;
	t_vec	scaled_dir;

  if (t0 > 0) 
  {
	scaled_dir = vec_scalar_mult(dir, t0);
    result = vec_add(origin, &scaled_dir);
    if (result.y >= 0 && result.y <= cylinder->height)
      return (t0);
  }
  if (t1 > 0) 
  {
    scaled_dir = vec_scalar_mult(dir, t1);
    result = vec_add(origin, &scaled_dir);
    if (result.y >= 0 && result.y <= cylinder->height)
	{
      return (t1);
    }
  }
	return (INFINITY);
}

int	trace_cylinder(t_vec *dir, float t_min, t_scene *scene)
{
	int			color;
	float		closest_t;
	float		temp_t;
	t_cylinder	*closest_cylinder;

	closest_t = INFINITY;
	closest_cylinder = NULL;
	for (int i = 0; i < scene->n_cylinders; i++)
	{
		temp_t = (hit_cylinder(&(scene->cylinder[i]), &scene->camera.view_point, dir, t_min)).t;
		if (temp_t < closest_t)
		{
			closest_t = temp_t;
			closest_cylinder = &(scene->cylinder[i]);
		}
	}
	color = 0x000000;
	if (closest_cylinder != NULL)
	{
		// float m = compute_color(&scene->camera.view_point, dir, closest_cylinder, scene, closest_t);
		float m = 1; // for now
		vec_scalar_mult(&(closest_cylinder->color), m);
		color  = color_vec_to_int(&(closest_cylinder->color));
	}
	return (color);
}

t_vec	get_cylinder_height(t_cylinder *cylinder)
{
	t_vec	result;

	result.x = cylinder->pos.x + cylinder->orientation.x * cylinder->height;
	result.y = cylinder->pos.y + cylinder->orientation.y * cylinder->height;
	result.z = cylinder->pos.z + cylinder->orientation.z * cylinder->height;
	return (result);
}
/* old code
float	hit_cylinder(t_cylinder *cylinder, t_vec *origin, t_vec *dir, float t_min)
 {
	t_vec	oc;

	oc = vec_sub(origin, &(cylinder->pos));
    float	a = (dir->x * dir->x) + (dir->y * dir->y);
    float	b = 2 * ((dir->x * oc.x) + (dir->y * oc.y));
    float	c = (oc.x * oc.x)+ (oc.y * oc.y)
		- ((cylinder->diameter / 2) * (cylinder->diameter /2));
    float	discriminant = (b * b) - (4 * a * c);
    
    if (discriminant < 0)
        return (INFINITY);
    float	t1 = (-b - sqrt(discriminant)) / (2 * a);
    float	t2 = (-b + sqrt(discriminant)) / (2 * a);
	if (!(t_min < t1 && t_min < t2))
	{
		// return (INFINITY);
		return (check_capped_part(t1, t2, origin, dir, cylinder));
	}
	float z1 = origin->z + t1 * dir->z;
	float z2 = origin->z + t2 * dir->z;
	if ((t2 < t_min || t1 < t2) && z1 > cylinder->pos.z && z1 < cylinder->pos.z + cylinder->height)
		return (t1);
	if (z2 > cylinder->pos.z && z2 < cylinder->pos.z + cylinder->height)
		return (t2);
	return (INFINITY);

}
*/