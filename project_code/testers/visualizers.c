/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 15:22:02 by ahsalem           #+#    #+#             */
/*   Updated: 2022/12/24 14:24:56 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	vis_list(t_list **head)
{
	t_list	*tmp;

	if (!head)
		return ;
	if (!*head)
		return ;
	tmp = *head;
	while (tmp)
	{
		ft_printf("%s~", tmp->content);
		tmp = tmp->next;
	}
}

void	vis_scene(t_scene *scene)
{

	printf("\n\n           #-----");
	printf("Visualizing scene");
	printf("-----#\n\n");
	if (!scene)
	{
		printf("Disaster!scene_is NULL !!!!!!!!!!!!!!!!!:(:(:(:(:(:(:\n");
		return ;
	}
	vis_elements(scene);
	if (scene->spheres)
		vis_spheres(scene);
}

void	vis_spheres(t_scene *scene)
{
	int	i;

	i = 0;
	while (i < scene->spheres[i].sphere_occurance)
	{
		vis_single_sphere(scene->spheres[i]);
		i++;
	}
}

void	vis_single_sphere(t_sphere sphere)
{
	printf("sp %3.2f,%3.2f,%3.2f   %3.2f   %3.2f,%3.2f,%3.2f\n", 
		sphere.center.x, sphere.center.y,
		sphere.center.z, sphere.diameter,
		sphere.color.x, sphere.color.y,
		sphere.color.z);
}

void	vis_elements(t_scene *scene)
{
	printf("A %3.2f	%3.2f,%3.2f,%3.2f\n", scene->amb_light.ratio,
		scene->amb_light.color.x, scene->amb_light.color.y,
		scene->amb_light.color.z);
	printf("L %3.2f,%3.2f,%3.2f   %3.2f   %3.2f,%3.2f,%3.2f\n", 
		scene->light.pos.x,
		scene->light.pos.y, scene->light.pos.z, scene->light.brightness,
		scene->light.color.x, scene->light.color.y, scene->light.color.z);
	printf("C %3.2f,%3.2f,%3.2f   %3.2f,%3.2f,%3.2f    %3.2f\n",
		scene->camera.view_point.x,
		scene->camera.view_point.y, scene->camera.view_point.z,
		scene->camera.orientation.x, scene->camera.orientation.y,
		scene->camera.orientation.z, scene->camera.view_field);
}