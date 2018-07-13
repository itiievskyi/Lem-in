/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itiievsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 09:50:55 by itiievsk          #+#    #+#             */
/*   Updated: 2018/06/07 09:50:59 by itiievsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void	mark_room(t_lemin *lem, char *str, t_slist *temp)
{
	t_slist		*t;

	t = lem->list;
	while (t && !temp->used)
	{
		if (ft_strcmp(temp->room, lem->end))
		{
			if (!ft_strcmp(t->room, str) && t->num == -1)
				t->num = temp->num + 1;
		}
		else if (!ft_strcmp(t->room, str) && temp->num > t->num + 1
			&& t->num > -1 && !t->used)
			temp->num = t->num + 1;
		t = t->next;
	}
	free(str);
}

char		*get_pair(char *str, char *find, int a)
{
	char	*pair;
	char	**arr;

	a = 1;
	pair = NULL;
	arr = ft_strsplit(str, '-');
	if (ft_strequ(arr[0], find))
		pair = ft_strdup(arr[1]);
	else if (ft_strequ(arr[1], find))
		pair = ft_strdup(arr[0]);
	clean_array(arr);
	return (pair);
}

void		bfs(t_lemin *lem, int i, int index)
{
	t_slist		*temp;
	char		*str;

	while (index < lem->rooms)
	{
		temp = lem->list;
		while (temp)
		{
			if (!temp->used && temp->num == index)
			{
				i = 0;
				while (lem->arr[lem->y + i])
					if ((str = get_pair(lem->arr[lem->y + i++], temp->room, 0)))
						mark_room(lem, str, temp);
			}
			temp = temp->next;
		}
		index++;
	}
	temp = lem->list;
	while (ft_strcmp(temp->room, lem->end))
		temp = temp->next;
	if (temp->num == lem->rooms - 1 && lem->iter > 0)
		lem->done = 1;
}

void		parse(t_lemin *lem, int i)
{
	char	*temp;

	while (lem->arr[i][0] == '#')
		i++;
	lem->ants = ft_atoi(lem->arr[i]);
	while (!ft_strncmp(lem->arr[++i], "##", 2) || ft_strchr(lem->arr[i], ' '))
	{
		if (!ft_strcmp(lem->arr[i], "##start"))
			lem->start = get_word(lem->arr[i + 1], 1);
		if (!ft_strcmp(lem->arr[i], "##end"))
			lem->end = get_word(lem->arr[i + 1], 1);
	}
	while (++(lem->y) < i && lem->start && lem->end)
	{
		if (ft_strchr(lem->arr[lem->y], ' '))
		{
			temp = get_word(lem->arr[lem->y], 1);
			if (ft_strcmp(temp, lem->start) && ft_strcmp(temp, lem->end))
				ft_slist_pushback(&lem->list, temp, -1);
			lem->rooms++;
			free(temp);
		}
	}
	lem->error = 0;
	check_parse(lem, 0, 0);
	ft_slist_pushfront(&lem->list, lem->start, 0);
	ft_slist_pushback(&lem->list, lem->end, lem->rooms - 1);
}
