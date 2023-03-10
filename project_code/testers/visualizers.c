/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 15:22:02 by ahsalem           #+#    #+#             */
/*   Updated: 2023/01/16 14:33:00 by ayassin          ###   ########.fr       */
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
		printf("%s~", (char *)(tmp->content));
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
	if (scene->plane)
		vis_planes(scene);
	if (scene->cylinder)
		vis_cylinders(scene);
}

void	vis_spheres(t_scene *scene)
{
	int	i;

	i = 0;
	while (i < scene->spheres[i].n_spheres)
	{
		vis_single_sphere(scene->spheres[i]);
		i++;
	}
}

void	vis_cylinders(t_scene *scene)
{
	int	i;

	i = 0;
	while (i < scene->cylinder[i].n_cylinders)
	{
		vis_single_cylinder(scene->cylinder[i]);
		i++;
	}
}

void	vis_single_cylinder(t_cylinder cylinder)
{
	printf("cy %3.2f,%3.2f,%3.2f	%3.2f,%3.2f,%3.2f	",
		cylinder.pos.x, cylinder.pos.y, cylinder.pos.z,
		cylinder.orientation.x, cylinder.orientation.y, cylinder.orientation.z);
	printf("%3.2f	%3.2f	%3.2f,%3.2f,%3.2f\n",
		cylinder.diameter, cylinder.height,
		cylinder.color.x, cylinder.color.y, cylinder.color.z);
}
