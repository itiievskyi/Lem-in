/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itiievsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 09:50:55 by itiievsk          #+#    #+#             */
/*   Updated: 2018/06/07 09:50:59 by itiievsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int			move_ants(t_lemin *lem, int way, int res, int x)
{
	t_slist		*temp;

	while (lem->ways[++way])
	{
		temp = lem->ways[way];
		x = ft_slist_length(temp) - 1;
		while (x >= 0)
		{
			while (temp->num < x)
				temp = temp->next;
			if (temp->next)
			{
				temp->next->ant = temp->ant;
				temp->ant = 0;
			}
			x--;
			temp = lem->ways[way];
		}
		while (temp)
		{
			res += temp->ant;
			temp = temp->next;
		}
	}
	return (res);
}

void		set_turns(t_lemin *lem)
{
	int		turns[lem->iter];
	int		way;
	int		max;
	int		ants;

	ants = lem->ants;
	max = 1;
	ft_bzero(turns, sizeof(turns));
	while (ants)
	{
		way = 0;
		while (lem->ways[way] && ants)
		{
			if (ft_slist_length(lem->ways[way]) <= max)
			{
				ants -= 1;
				turns[way] += 1;
			}
			way++;
		}
		max++;
	}
	print_str(lem, 0);
	print_result(lem, turns);
}

static int	near(char *two, char *one, t_lemin *lem)
{
	char		*str;
	char		*rev;
	char		*temp;
	int			i;

	temp = ft_strjoin(one, "-");
	str = ft_strjoin(temp, two);
	free(temp);
	temp = ft_strjoin(two, "-");
	rev = ft_strjoin(temp, one);
	free(temp);
	i = -1;
	while (lem->arr[lem->y + ++i])
	{
		if (!ft_strcmp(lem->arr[lem->y + i], str) ||
			!ft_strcmp(lem->arr[lem->y + i], rev))
		{
			free(str);
			free(rev);
			return (1);
		}
	}
	free(str);
	free(rev);
	return (0);
}

void		find_way(t_lemin *lem)
{
	t_slist		*temp;
	int			a;

	temp = lem->list;
	while (temp && ft_strcmp(temp->room, lem->end))
		temp = temp->next;
	a = temp->num - 1;
	ft_slist_pushback(&lem->ways[lem->iter], temp->room, temp->num);
	while (a >= 0)
	{
		temp = lem->list;
		while (temp)
		{
			if (temp->num == a && a >= 0 && !temp->used)
				if (near(temp->room, (lem->ways[lem->iter])->room, lem))
					break ;
			temp = temp->next;
		}
		if (!temp)
			error_exit(lem, 0);
		ft_slist_pushfront(&lem->ways[lem->iter], temp->room, temp->num);
		a -= 1;
		if (ft_strcmp(temp->room, lem->start))
			temp->used = 1;
	}
}
