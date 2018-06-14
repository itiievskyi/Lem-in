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

static void	mark_room(t_lemin *lem, char *str, int num)
{
	t_slist		*t;

	t = lem->list;
	while (t)
	{
		if (!ft_strcmp(t->room, str) && t->num == -1)
			t->num = num + 1;
		t = t->next;
	}
//	free(str);
}

static char	*get_pair(char *str, char *find, int a)
{
	char	*pair;
	int		len;

	len = ft_strlen(find);
	pair = NULL;
//	ft_printf("*compare # 1 = %d\t", ft_strncmp(str, find, len));
	if (!ft_strncmp(str, find, len) && str[len] == '-')
		pair = ft_strsub(str, len + 1, ft_strlen(str) - len - 1);
	else
	{
		while (str[a] != '\0' && str[a] != '-')
			a++;
//		ft_printf("*compare # 2 = %d\t", ft_strcmp(&str[a + 1], find));
		if (!ft_strcmp(&str[a + 1], find))
			pair = ft_strsub(str, 0, ft_strlen(str) - a - 1);
	}
//	if (pair)
//		ft_printf("*find = %s, *pair = %s\n", find, pair);
//	if (!pair)
//		ft_printf("*find = %s, *pair = (null)\n", find, pair);
	return(pair);
}

static void	bfs(t_lemin *lem, int i)
{
	t_slist		*t;
	char		*temp;

	t = lem->list;
	while (ft_strcmp(t->room, lem->end))
	{
		i = 0;
		while (lem->arr[lem->y + i])
		{
			if ((temp = get_pair(lem->arr[lem->y + i], t->room, 0)))
				mark_room(lem, temp, t->num);
			i++;
		}
		t = t->next;
	}
}

void		parse(t_lemin *lem, int i)
{
	char	*temp;

	lem->ants = ft_atoi(lem->arr[i]);
	while (!ft_strncmp(lem->arr[++i], "##", 2) || ft_strchr(lem->arr[i], ' '))
	{
		if (!ft_strcmp(lem->arr[i], "##start"))
			lem->start = get_word(lem->arr[i + 1], 1);
		if (!ft_strcmp(lem->arr[i], "##end"))
			lem->end = get_word(lem->arr[i + 1], 1);
	}
	while (++(lem->y) < i)
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
	ft_slist_pushfront(&lem->list, lem->start, 0);
	ft_slist_pushback(&lem->list, lem->end, lem->rooms - 1);
	bfs(lem, 0);

	t_slist *t;
	t = lem->list;
	while (t)
	{
		ft_printf("room = \'%s\', its index = %d\n", t->room, t->num);
		t = t->next;
	}
}

/*
	t_slist *t;
	t = lem->list;
	while (t)
	{
		ft_printf("room = \'%s\', its index = %d\n", t->room, t->num);
		t = t->next;
	}
*/
//	create_rooms_list(lem);
//	ft_printf("start = %s\n", lem->start);
//	ft_printf("end = %s\n", lem->end);
//	ft_printf("string = %s\n", lem->arr[4]);
//	ft_printf("word = %s\n", get_word(lem->arr[4], 3));
