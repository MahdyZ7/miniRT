/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_smasher.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 08:07:36 by ahsalem           #+#    #+#             */
/*   Updated: 2022/12/18 14:46:09 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"
/*
	if there is parser error
	will fill the first flag with parser error code, 
	check if there is an error if the flag value less than 30
*/

t_list	*parsing_map(int fd)
{
	t_parsing_kit	s;
	char			*line;
	t_list			*head;

	head = NULL;
	line = NULL;
	line = get_next_line(fd);
	if (!line)
		return (NULL);
	init_parsing_kit(&s, &head, line);
	while (line)
	{
		filling_loop(&s, line, &head);
		free(line);
		line = get_next_line(fd);
		update_parsing_kit(&s, line);
	}
	return (head);
}

int	filling_loop(t_parsing_kit *s, char *line, t_list **head)
{
	while (s->i < s->line_len)
	{
		if (line_classifier(s, line) == 'n')
			fill_new_line(s, line, head, s->i);
		// else
		// 	spaces_smash(s, line, head);
		if (s->parse_error_code != 0)
			break ;
		s->i++;
	}
	return (s->parse_error_code);
}

char	line_classifier(t_parsing_kit *s, char *line)
{
	int	i;

	i = s->i;
	if (s->flag != 'i')
		return (s->flag);
	while (line[i])
	{
		if (line[i] == ' ')
		{
			i++;
			continue ;
		}
		else if (check_new_line(line, i))
			s->flag = 'n';
		else
			s->flag = 's';
		s->start = i;
		return (s->flag);
	}
	return (s->flag);
}

void	init_parsing_kit(t_parsing_kit *s, t_list **head, char *line)
{
	s->start = 0;
	s->end = 0;
	s->last_end = 0;
	s->i = 0;
	s->tmp = *head;
	s->flag = 'i';
	s->parse_error_code = 0;
	s->line_len = ft_strlen(line);
	s->line = line;
}

void	update_parsing_kit(t_parsing_kit *s,char *line)
{
	s->start = 0;
	s->end = 0;
	s->last_end = 0;
	s->i = 0;
	s->flag = 'i';
	s->parse_error_code = 0;
	s->line_len = ft_strlen(line);
	s->line = line;
}

t_list	*fill_line_node(char *arg, char type)
{
	t_list	*new_node;

	new_node = ft_lstnew(NULL);
	new_node->content = (void *)arg;
	new_node->type = type;
	return (new_node);
}
