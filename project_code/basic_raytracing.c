/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_raytracing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 18:55:05 by ayassin           #+#    #+#             */
/*   Updated: 2023/01/14 17:42:24 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "miniRT.h"

void	basic_raytracing(t_img *img)
{
	t_ray_trace_kit	r;

	img->scene->camera.xyz_angles.x = img->scene->camera.orientation.y * -1;
	img->scene->camera.xyz_angles.y = img->scene->camera.orientation.x;
	// img->scene->camera.xyz_angles.z = (float)((int)(img->scene->camera.orientation.z * 1000) % 350) / 1000;
	printf("\nOrientation = ");
	vis_vector(img->scene->camera.xyz_angles);
	printf("\n\n");
	init_ray_trace_kit(&r, img);
	if(img->scene->spheres > 0 && img->scene->n_cylinders == 0
		&& img->scene->n_planes == 0)
		trace_only_spheres(&r, img);
	else if(img->scene->spheres == 0 && img->scene->n_cylinders > 0
		&& img->scene->n_planes == 0)
		trace_only_cylinders(&r, img);
	else if(img->scene->spheres == 0 && img->scene->n_cylinders == 0
		&& img->scene->n_planes > 0)
		trace_only_planes(&r, img);
	else
		trace_all_shapes(&r, img);

}

void	trace_all_shapes(t_ray_trace_kit *r, t_img *img)
{
	while (r->x < WIN_WIDTH)
	{
		r->y = 0;
		while (r->y < WIN_HIGHT)
		{
			r->new_x = (2 * ((r->x + 0.5) * r->invwidth) - 1)
				* r->angle * r->aspectratio;
			r->new_y = (1 - 2 * ((r->y + 0.5) * r->invheight)) * r->angle;
			vec_init(&r->dir, r->new_x, r-> new_y, 1);
			r->dir = dir_with_camera_orientation(&r->dir, img->scene);
			r->plane_result = trace_plane(&r->dir, img->scene);
			r->sphere_result = trace_sphere(&r->dir, img->scene->camera.view_point.z + 1, img->scene);
			r->cylinder_result = trace_cylinder(&r->dir, img->scene->camera.view_point.z + 1, img->scene);
			if (r->plane_result.x < r->sphere_result.x && r->plane_result.x < r->cylinder_result.x)
				r->color = r->plane_result.y;
			else if (r->sphere_result.x < r->plane_result.x && r->sphere_result.x < r->cylinder_result.x)
				r->color = r->sphere_result.y;
			else
				r->color = r->cylinder_result.y;
			pixel_put(img->scene->win->img, r->x, r->y, r->color);
			++r->y;
		}
		r->x++;
	}
}

void	trace_only_planes(t_ray_trace_kit *r, t_img *img)
{
	printf("trace_only_planes\n");
	printf("x angle = %f, y angle = %f, z angle = %f\n"
		, img->scene->camera.xyz_angles.x, img->scene->camera.xyz_angles.y, img->scene->camera.xyz_angles.z);
	while (r->x < WIN_WIDTH)
	{
		r->y = 0;
		while (r->y < WIN_HIGHT)
		{
			r->new_x = (2 * ((r->x + 0.5) * r->invwidth) - 1)
				* r->angle * r->aspectratio;
			r->new_y = (1 - 2 * ((r->y + 0.5) * r->invheight)) * r->angle;
			vec_init(&r->dir, r->new_x, r-> new_y, 1);
			normalize(&r->dir);
			r->dir = dir_with_camera_orientation(&r->dir, img->scene);
			// img->scene->camera.view_point
			// 	= dir_with_camera_orientation(&img->scene->camera.view_point, img->scene);
			// r->dir = vec_sub(&r->dir, &img->scene->camera.view_point);
			normalize(&r->dir);
			r->plane_result = trace_plane(&r->dir, img->scene);
				r->color = r->plane_result.y;
			pixel_put(img->scene->win->img, r->x, r->y, r->color);
			++r->y;
		}
		r->x++;
	}
}

void	trace_only_cylinders(t_ray_trace_kit *r, t_img *img)
{
	while (r->x < WIN_WIDTH)
	{
		r->y = 0;
		while (r->y < WIN_HIGHT)
		{
			r->new_x = (2 * ((r->x + 0.5) * r->invwidth) - 1)
				* r->angle * r->aspectratio;
			r->new_y = (1 - 2 * ((r->y + 0.5) * r->invheight)) * r->angle;
			vec_init(&r->dir, r->new_x, r-> new_y, 1);
			r->dir = dir_with_camera_orientation(&r->dir, img->scene);
			r->cylinder_result = trace_cylinder(&r->dir, img->scene->camera.view_point.z + 1, img->scene);
			r->color = r->cylinder_result.y;
			pixel_put(img->scene->win->img, r->x, r->y, r->color);
			++r->y;
		}
		r->x++;
	}
}

void	trace_only_spheres(t_ray_trace_kit *r, t_img *img)
{
	while (r->x < WIN_WIDTH)
	{
		r->y = 0;
		while (r->y < WIN_HIGHT)
		{
			r->new_x = (2 * ((r->x + 0.5) * r->invwidth) - 1)
				* r->angle * r->aspectratio;
			r->new_y = (1 - 2 * ((r->y + 0.5) * r->invheight)) * r->angle;
			vec_init(&r->dir, r->new_x, r-> new_y, 1);
			normalize(&r->dir);
			r->dir = dir_with_camera_orientation(&r->dir, img->scene);
			r->dir = vec_sub(&r->dir, &img->scene->camera.view_point);
			normalize(&r->dir);
			r->plane_result = trace_plane(&r->dir, img->scene);
			r->sphere_result = trace_sphere(&r->dir, img->scene->camera.view_point.z + 1, img->scene);
			r->color = r->sphere_result.y;
			pixel_put(img->scene->win->img, r->x, r->y, r->color);
			++r->y;
		}
		r->x++;
	}
}

void	init_ray_trace_kit(t_ray_trace_kit *r, t_img *img)
{
	r->x = 0;
	r->y = 0;
	r->invwidth = 1 / (float)WIN_WIDTH;
	r->invheight = 1 / (float)WIN_HIGHT;
	r->aspectratio = (float)WIN_WIDTH / (float)WIN_HIGHT;
	r->angle = tan(M_PI * 0.5 * img->scene->camera.view_field / 180.);
	r->color = 0;
	fill_single_vector(&r->plane_result, 0, 0, 0);
	fill_single_vector(&r->sphere_result, 0, 0, 0);
	fill_single_vector(&r->cylinder_result, 0, 0, 0);
}


/*
1) add pos of camera to pos of each objects
2) apply rotation to every object except camera
3) remove pos of camera from each object
*/