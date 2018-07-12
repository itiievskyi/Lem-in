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

static void	print_turn(t_lemin *lem)
{
	int			ant;
	t_slist		*temp;
	int			way;
	int			stop;
	int			count;

	ant = 1;
	count = 0;
	while (ant < lem->ants + 1)
	{
		stop = 0;
		way = 0;
		while (lem->ways[way] && !stop)
		{
			temp = lem->ways[way];
			while (temp && !stop)
			{
				if (temp->ant == ant && temp->num != 0)
				{
					if (++count > 1)
						ft_printf(" L%d-%s", ant, temp->room);
					else
						ft_printf("L%d-%s", ant, temp->room);
					stop = 1;
				}
				temp = temp->next;
			}
			way++;
		}
		ant++;
	}
}

static int	move_ants(t_lemin *lem)
{
	t_slist		*temp;
	int			way;
	int			x;
	int			res;

	way = 0;
	res = 0;
	while (lem->ways[way])
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
		while (temp->next)
		{
			res += temp->ant;
			temp = temp->next;
		}
		way++;
	}
	return(res);
}

static void	print_result(t_lemin *lem, int turns[])
{
	int			ant;
	int			on;
	int			way;

	ant = 1;
	on = 1;
	while (on)
	{
		way = 0;
		while (lem->ways[way])
		{
			if (turns[way])
			{
				lem->ways[way]->ant = ant;
				ant += 1;
				turns[way] -= 1;
			}
			way++;
		}
		if (move_ants(lem) > 0)
			on = 1;
		else
			on = 0;
		print_turn(lem);
		ft_printf("\n");
	}
}

static void print_str(t_lemin *lem, int i)
{
	char	**arr;

//	arr = ft_strsplit(lem->string, '\n');
	arr = lem->arr;
	while (arr[i])
	{
		if (!ft_strcmp(arr[i], "##start") || !ft_strcmp(arr[i], "##end") ||
			!(arr[i][0] == '#' && arr[i][1] == '#'))
			ft_printf("%s\n", arr[i]);
		i++;
	}
	i = 0;
//	while (arr[i])
//		free(arr[i++]);
//	free(arr);
	ft_printf("\n");
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
				return(1);
			}
	}
	free(str);
	free(rev);
	return(0);
}

static void	reinit_list(t_lemin *lem)
{
	t_slist		*temp;

	temp = lem->list;
	while (temp)
	{
		if (!ft_strcmp(temp->room, lem->end))
			temp->num = lem->rooms - 1;
		if (!ft_strcmp(temp->room, lem->start))
			temp->num = 0;
		if (!temp->used && temp->num != 0 && temp->num != lem->rooms - 1)
			temp->num = -1;
		temp = temp->next;
	}
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
	reinit_list(lem);
}
