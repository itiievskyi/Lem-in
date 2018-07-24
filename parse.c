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
	if ((temp->num == lem->rooms - 1 && lem->iter > 0))
		lem->done = 1;
}

void		parse(t_lemin *lem, int i)
{
	char	*temp;
	char	*s;

	while ((s = lem->arr[i]) &&
		!(ft_words_count(s) == 1 && ft_strchr(s, '-')))
		i++;
	while (++(lem->y) < i && lem->start && lem->end)
	{
		if (ft_strchr(lem->arr[lem->y], ' ') && (lem->arr[lem->y])[0] != '#')
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

void		check_parse(t_lemin *lem, int i, int x)
{
	char		*s1;
	char		*s2;

	if (!lem->start || !lem->end || ft_count_in_array(lem->arr, "##start") != 1
		|| ft_count_in_array(lem->arr, "##end") != 1)
		error_exit(lem, 0);
	while (lem->arr[++i] && !lem->error)
	{
		x = 1;
		while (++x < i && !lem->error)
		{
			s1 = get_word(lem->arr[i], 1);
			s2 = get_word(lem->arr[x], 1);
			if (s1[0] != '#' && s2[0] != '#' && !ft_strcmp(s1, s2) &&
				ft_words_count(lem->arr[i]) != 1 &&
				ft_words_count(lem->arr[x]) != 1)
				lem->error = 1;
			free(s1);
			free(s2);
			if (lem->error)
				cut_array(lem, i);
		}
		if (lem->arr[i] && check_pipes(lem, lem->arr[i], 0, 0))
			cut_array(lem, i);
	}
}
