/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_all_elements_for_errors.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 22:42:56 by ahsalem           #+#    #+#             */
/*   Updated: 2022/12/23 16:06:34 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

//remember to double check other letters that make no sense in the map
int	check_all_elements_for_errors(t_list **all_map_items, t_scene *scene)
{
	(void)scene;
	if (check_camera_data(all_map_items, scene)
		|| check_light_data(all_map_items, scene)
		|| check_ambient_light_data(all_map_items, scene)
		|| check_sphere(all_map_items, scene)
		|| check_cylender(all_map_items, scene)
		|| check_plane(all_map_items, scene)
		|| scene->number_of_shapes == 0)
	{
		return (1);
	}
	return (0);
}

int	count_occurance_in_map(t_list **all_map_items, char *element)
{
	int		i;
	t_list	*tmp;

	if (!(*all_map_items))
		return (0);
	tmp = *all_map_items;
	i = 0;
	while (tmp)
	{
		if (!ft_the_strcmp((char *)tmp->content, element))
		{
			i++;
			// tmp = fetch_next_element(tmp);
			// if (!tmp)
			// 	return (i);
		}
		tmp = tmp->next;
	}
	return (i);
}

t_list	*fetch_next_element(t_list *tmp)
{
	while (tmp)
	{
		if (!ft_the_strcmp((char *)tmp, "\n"))
		{
			while (!ft_the_strcmp((char *)tmp, "\n") && tmp)
			{
				tmp = tmp->next;
			}
			return (tmp);
		}
		tmp = tmp->next;
	}
	return (NULL);
}