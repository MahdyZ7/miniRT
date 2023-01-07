/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classify_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 23:22:05 by ahsalem           #+#    #+#             */
/*   Updated: 2023/01/07 18:21:55 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	spaces_smash(t_parsing_kit *s, char *line, t_list **head)
{
	char	*smashed_line;

	smashed_line = NULL;
	if (!line[s->i])
		return ;
	if (ft_isspace(line[s->i]) && line[s->i + 1] && !ft_isspace(line[s->i + 1]))
		s->start = s->i + 1;
	else if (ft_isspace(line[s->i]))
		;
	else if ((s->flag == 's' && (ft_isspace(line[s->i + 1])
				|| (check_new_line(line, s->i + 1))))
		|| ((s->i + 1) >= s->line_len))
	{
		filling_normal_spaced_word(
			s, smashed_line, head);
	}
}

void	filling_normal_spaced_word(
		t_parsing_kit *s, char *smashed_line, t_list **head)
{
	s->end = s->i;
	smashed_line = ft_substr(s->line, s->start, s->end - s->start + 1);
	if (!(!smashed_line[0] && s->line[0]))
	{
		s->tmp = fill_line_node(smashed_line, 'w');
		ft_lstadd_back(head, s->tmp);
	}
	else
		free(smashed_line);
	s->flag = 'i';
}

int	fill_new_line(t_parsing_kit *s, char *line, t_list **head, int i)
{
	s->end = i;
	if (line[i] == '\n')
	{
		s->tmp = fill_line_node(ft_strdup("\n"), 'n');
		ft_lstadd_back(head, s->tmp);
	}
	s->flag = 'i';
	return (0);
}

int	check_new_line(char *line, int i)
{
	if (line[i] == '\n')
		return (1);
	return (0);
}
