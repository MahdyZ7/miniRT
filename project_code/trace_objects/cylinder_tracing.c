#include "../miniRT.h"



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
	for (int i = 0; i < scene->cylinder->n_cylinders; i++)
	{
		temp_t = hit_cylinder(&(scene->cylinder[i]), &scene->camera.view_point, dir, t_min);
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